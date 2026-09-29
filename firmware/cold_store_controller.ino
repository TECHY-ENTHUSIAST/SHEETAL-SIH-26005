#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>
#include <Adafruit_INA219.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// SIH 2026 PS 26005: PCM cold-store monitoring controller.
// PCM is a passive thermal buffer; this firmware only measures, reports, and alerts.

// Hoisted type definitions
struct Reading {
  float primaryC = NAN;
  float dhtC = NAN;
  float humidity = NAN;
  float volts = NAN;
  float currentMa = NAN;
  float powerMw = NAN;
  bool dsOk = false;
  bool dhtOk = false;
  bool inaOk = false;
  bool cameraSeen = false;
  String status = "STARTING";
  String alert = "NONE";
  uint32_t sampledAtMs = 0;
};


// Forward declarations
bool plausibleTemperature(float c);
bool plausibleHumidity(float h);
String nowLabel();
void addHistory();
void deriveStatus();
bool alertActive();
void updateAlerts();
void readSensors();
void checkCameraHeartbeat();
String valueOrError(bool valid, float value, uint8_t decimals);
String jsonPayload();
void setupWebServer();
void startNetwork();
void maintainNetwork();
void drawDisplay();

constexpr uint8_t DS18B20_PIN = 4;
constexpr uint8_t DHT_PIN = 27;
constexpr uint8_t BUZZER_PIN = 25;
constexpr uint8_t ALERT_LED_PIN = 26;
constexpr uint8_t CAM_RX_PIN = 16; // ESP32-CAM U0T -> controller RX
constexpr uint8_t CAM_TX_PIN = 17; // ESP32-CAM U0R <- controller TX
constexpr uint8_t I2C_SDA_PIN = 21;
constexpr uint8_t I2C_SCL_PIN = 22;
constexpr uint32_t SAMPLE_INTERVAL_MS = 10000;
constexpr uint32_t DISPLAY_INTERVAL_MS = 1000;
constexpr uint32_t WIFI_RETRY_INTERVAL_MS = 15000;
constexpr float LOW_TEMP_C = 6.0f;
constexpr float TARGET_HIGH_C = 10.0f;
constexpr float UPPER_HIGH_C = 12.0f;
constexpr float HIGH_TEMP_C = 13.0f;
constexpr float LOW_SYSTEM_VOLTAGE = 4.75f;

// Leave blank to demonstrate with the protected fallback access point.
// Set these before deployment only when an existing Wi-Fi network is available.
const char* WIFI_SSID = "";
const char* WIFI_PASSWORD = "";
const char* AP_SSID = "ColdStore-Setup";
const char* AP_PASSWORD = "coldstore26005";

OneWire oneWire(DS18B20_PIN);
DallasTemperature ds18b20(&oneWire);
DHT dht(DHT_PIN, DHT22);
Adafruit_INA219 ina219;
Adafruit_SSD1306 display(128, 64, &Wire, -1);
WebServer server(80);
HardwareSerial cameraSerial(2);



Reading reading;
String history[24];
uint8_t historyHead = 0;
uint8_t historyCount = 0;
bool oledOk = false;
bool inaOkAtBoot = false;
bool apMode = false;
uint32_t lastSample = 0;
uint32_t lastDisplay = 0;
uint32_t lastWifiRetry = 0;
uint32_t lastCameraMessage = 0;

bool plausibleTemperature(float c) { return !isnan(c) && c > -40.0f && c < 85.0f; }
bool plausibleHumidity(float h) { return !isnan(h) && h >= 0.0f && h <= 100.0f; }

String nowLabel() {
  uint32_t seconds = millis() / 1000;
  char text[16];
  snprintf(text, sizeof(text), "%02lu:%02lu:%02lu", seconds / 3600, (seconds / 60) % 60, seconds % 60);
  return String(text);
}

void addHistory() {
  String line = nowLabel() + ",";
  line += reading.dsOk ? String(reading.primaryC, 2) : "ERR";
  line += "," + (reading.dhtOk ? String(reading.humidity, 1) : "ERR");
  line += "," + (reading.inaOk ? String(reading.volts, 2) : "ERR");
  line += "," + (reading.inaOk ? String(reading.currentMa, 0) : "ERR");
  line += "," + reading.alert;
  history[historyHead] = line;
  historyHead = (historyHead + 1) % 24;
  if (historyCount < 24) historyCount++;
}

void deriveStatus() {
  if (!reading.dsOk) {
    reading.status = "SENSOR FAULT";
    reading.alert = "DS18B20 FAULT";
  } else if (reading.primaryC < LOW_TEMP_C) {
    reading.status = "COOLING PROTECT";
    reading.alert = "LOW TEMPERATURE";
  } else if (reading.primaryC <= TARGET_HIGH_C) {
    reading.status = "TARGET RANGE";
    reading.alert = "NONE";
  } else if (reading.primaryC <= UPPER_HIGH_C) {
    reading.status = "UPPER RANGE";
    reading.alert = "NONE";
  } else if (reading.primaryC >= HIGH_TEMP_C) {
    reading.status = "HIGH TEMP ALERT";
    reading.alert = "HIGH TEMPERATURE";
  } else {
    reading.status = "TRANSITION"; // 12.0 to below 13.0 C
    reading.alert = "WATCH TEMPERATURE";
  }
  if (!reading.dhtOk && reading.alert == "NONE") reading.alert = "DHT22 FAULT";
  if (!reading.inaOk && reading.alert == "NONE") reading.alert = "INA219 FAULT";
  if (reading.inaOk && reading.volts < LOW_SYSTEM_VOLTAGE && reading.alert == "NONE") reading.alert = "LOW SYSTEM VOLTAGE";
}

bool alertActive() { return reading.alert != "NONE"; }

void updateAlerts() {
  bool active = alertActive();
  digitalWrite(ALERT_LED_PIN, active ? HIGH : LOW);
  // A short non-blocking beep pattern. No relay or cooling load is driven here.
  static uint32_t previousTone = 0;
  if (active && millis() - previousTone > 5000) {
    tone(BUZZER_PIN, 2200, 180);
    previousTone = millis();
  }
}

void readSensors() {
  ds18b20.requestTemperatures();
  float primary = ds18b20.getTempCByIndex(0);
  reading.dsOk = primary != DEVICE_DISCONNECTED_C && plausibleTemperature(primary);
  reading.primaryC = reading.dsOk ? primary : NAN;

  float dhtHumidity = dht.readHumidity();
  float dhtTemp = dht.readTemperature();
  reading.dhtOk = plausibleTemperature(dhtTemp) && plausibleHumidity(dhtHumidity);
  reading.dhtC = reading.dhtOk ? dhtTemp : NAN;
  reading.humidity = reading.dhtOk ? dhtHumidity : NAN;

  reading.inaOk = inaOkAtBoot;
  if (reading.inaOk) {
    reading.volts = ina219.getBusVoltage_V();
    reading.currentMa = ina219.getCurrent_mA();
    reading.powerMw = ina219.getPower_mW();
    if (isnan(reading.volts) || isnan(reading.currentMa) || isnan(reading.powerMw) || reading.volts < 0.0f || reading.volts > 26.0f) reading.inaOk = false;
  }
  deriveStatus();
  updateAlerts();
  reading.sampledAtMs = millis();
  addHistory();
  Serial.printf("[%s] DS18B20=%s DHT22=%s INA219=%s status=%s alert=%s\n", nowLabel().c_str(), reading.dsOk ? String(reading.primaryC, 2).c_str() : "ERR", reading.dhtOk ? String(reading.humidity, 1).c_str() : "ERR", reading.inaOk ? String(reading.volts, 2).c_str() : "ERR", reading.status.c_str(), reading.alert.c_str());
}

void checkCameraHeartbeat() {
  while (cameraSerial.available()) {
    String message = cameraSerial.readStringUntil('\n');
    message.trim();
    if (message == "CAM_OK") {
      reading.cameraSeen = true;
      lastCameraMessage = millis();
    }
  }
  if (lastCameraMessage && millis() - lastCameraMessage > 60000) reading.cameraSeen = false;
}

String valueOrError(bool valid, float value, uint8_t decimals) { return valid ? String(value, decimals) : "ERR"; }

String jsonPayload() {
  String json = "{";
  json += "\"uptime_s\":" + String(millis() / 1000);
  json += ",\"storage_temp_c\":" + (reading.dsOk ? String(reading.primaryC, 2) : "null");
  json += ",\"dht_temp_c\":" + (reading.dhtOk ? String(reading.dhtC, 2) : "null");
  json += ",\"humidity_pct\":" + (reading.dhtOk ? String(reading.humidity, 1) : "null");
  json += ",\"system_voltage_v\":" + (reading.inaOk ? String(reading.volts, 2) : "null");
  json += ",\"current_ma\":" + (reading.inaOk ? String(reading.currentMa, 1) : "null");
  json += ",\"power_mw\":" + (reading.inaOk ? String(reading.powerMw, 1) : "null");
  json += ",\"status\":\"" + reading.status + "\"";
  json += ",\"alert\":\"" + reading.alert + "\"";
  json += ",\"camera_heartbeat\":" + String(reading.cameraSeen ? "true" : "false");
  json += ",\"wifi_mode\":\"" + String(apMode ? "AP" : "STA") + "\"";
  json += "}";
  return json;
}

const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!doctype html><html><head><meta name="viewport" content="width=device-width,initial-scale=1"><title>Cold Store Monitor</title><style>body{font-family:Arial;margin:20px;background:#f2f6f4;color:#16251d}.grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(150px,1fr));gap:10px}.card{background:white;padding:14px;border-radius:10px;box-shadow:0 1px 4px #aaa}.bad{color:#b00020;font-weight:bold}small{color:#445}</style></head><body><h2>PCM Cold-Store Monitor</h2><p><b id="status">Loading</b> &mdash; <span id="alert"></span></p><div class="grid"><div class="card">Storage temperature<br><b id="t">--</b> °C</div><div class="card">Humidity<br><b id="h">--</b> %</div><div class="card">System voltage<br><b id="v">--</b> V</div><div class="card">Current<br><b id="i">--</b> mA</div><div class="card">Power<br><b id="p">--</b> mW</div><div class="card">Camera node<br><b id="cam">--</b></div></div><p><small>DS18B20 is the control reference. Target 6–10 °C; upper range 10–12 °C; warning below 6 °C; high-temperature alert at or above 13 °C. PCM buffering is a design target, not a measured result.</small></p><p><a href="/api/history">Download recent CSV history</a></p><script>async function poll(){try{let d=await (await fetch('/api/readings')).json();for(let [id,k] of [['t','storage_temp_c'],['h','humidity_pct'],['v','system_voltage_v'],['i','current_ma'],['p','power_mw']])document.getElementById(id).textContent=d[k]??'ERR';document.getElementById('status').textContent=d.status;document.getElementById('alert').textContent=d.alert;document.getElementById('alert').className=d.alert==='NONE'?'':'bad';document.getElementById('cam').textContent=d.camera_heartbeat?'heartbeat received':'not reporting';}catch(e){document.getElementById('status').textContent='Dashboard connection lost';}}setInterval(poll,3000);poll();</script></body></html>
)rawliteral";

void setupWebServer() {
  server.on("/", []() { server.send_P(200, "text/html", INDEX_HTML); });
  server.on("/api/readings", []() { server.send(200, "application/json", jsonPayload()); });
  server.on("/api/history", []() {
    String csv = "uptime,storage_temp_c,humidity_pct,system_voltage_v,current_ma,alert\n";
    uint8_t start = (historyHead + 24 - historyCount) % 24;
    for (uint8_t i = 0; i < historyCount; ++i) csv += history[(start + i) % 24] + "\n";
    server.sendHeader("Content-Disposition", "attachment; filename=cold_store_history.csv");
    server.send(200, "text/csv", csv);
  });
  server.onNotFound([]() { server.send(404, "text/plain", "Not found"); });
  server.begin();
}

void startNetwork() {
  WiFi.mode(WIFI_AP_STA);
  if (strlen(WIFI_SSID) > 0) {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    uint32_t start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 10000) delay(250);
  }
  if (WiFi.status() == WL_CONNECTED) {
    apMode = false;
    Serial.print("Wi-Fi connected. Dashboard: http://");
    Serial.println(WiFi.localIP());
  } else {
    WiFi.softAP(AP_SSID, AP_PASSWORD);
    apMode = true;
    Serial.print("Fallback dashboard AP ");
    Serial.print(AP_SSID);
    Serial.print(" at http://");
    Serial.println(WiFi.softAPIP());
  }
}

void maintainNetwork() {
  if (!apMode && WiFi.status() != WL_CONNECTED && millis() - lastWifiRetry > WIFI_RETRY_INTERVAL_MS) {
    WiFi.reconnect();
    lastWifiRetry = millis();
  }
}

void drawDisplay() {
  if (!oledOk) return;
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0); display.print("PCM COLD STORE MONITOR");
  display.setCursor(0, 14); display.print("Store: "); display.print(valueOrError(reading.dsOk, reading.primaryC, 1)); display.print(" C");
  display.setCursor(0, 25); display.print("Hum:   "); display.print(valueOrError(reading.dhtOk, reading.humidity, 0)); display.print(" %");
  display.setCursor(0, 36); display.print("Sys: "); display.print(valueOrError(reading.inaOk, reading.volts, 2)); display.print("V "); display.print(valueOrError(reading.inaOk, reading.currentMa, 0)); display.print("mA");
  display.setCursor(0, 48); display.print(reading.status);
  display.setCursor(0, 57); display.print(reading.alert);
  display.display();
}

void setup() {
  Serial.begin(115200);
  pinMode(ALERT_LED_PIN, OUTPUT);
  digitalWrite(ALERT_LED_PIN, LOW);
  cameraSerial.begin(115200, SERIAL_8N1, CAM_RX_PIN, CAM_TX_PIN);
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  oledOk = display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  if (oledOk) { display.clearDisplay(); display.setTextColor(SSD1306_WHITE); display.setCursor(0,0); display.println("Cold-store booting"); display.display(); }
  inaOkAtBoot = ina219.begin();
  ds18b20.begin();
  dht.begin();
  startNetwork();
  setupWebServer();
  readSensors();
}

void loop() {
  server.handleClient();
  checkCameraHeartbeat();
  maintainNetwork();
  if (millis() - lastSample >= SAMPLE_INTERVAL_MS) { lastSample = millis(); readSensors(); }
  if (millis() - lastDisplay >= DISPLAY_INTERVAL_MS) { lastDisplay = millis(); drawDisplay(); }
}