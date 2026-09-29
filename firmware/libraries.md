# Firmware Libraries & Setup Guide

This document lists the required software libraries, dependencies, and environment setup for compiling and flashing the **SHEETAL** cold store supervisory controller (`cold_store_controller.ino`) onto the ESP32 DevKit V1.

---

## 1. Development Environment

- **IDE:** Arduino IDE 2.x or Arduino IDE 1.8.19+ (PlatformIO also supported)
- **Board Package:** `esp32` by Espressif Systems (tested with version 2.0.11 / 2.0.14)
- **Target Microcontroller:** ESP32 DevKit V1 (ESP32-WROOM-32, 30-pin)
- **Clock Frequency:** 240 MHz
- **Flash Frequency:** 80 MHz
- **Partition Scheme:** Default 4MB with SPIFFS (1.2MB APP / 1.5MB SPIFFS)

---

## 2. Library Dependencies

The firmware uses the following standard and open-source libraries:

| Library Name | Author / Maintainer | Installation Source | Purpose |
| :--- | :--- | :--- | :--- |
| **WiFi** | Espressif Systems | Built-in (ESP32 Board Core) | SoftAP mode and Wi-Fi client management |
| **WebServer** | Espressif Systems | Built-in (ESP32 Board Core) | Serves HTML UI and REST API endpoints |
| **Wire** | Espressif Systems | Built-in (ESP32 Board Core) | I²C hardware master communication |
| **OneWire** | Paul Stoffregen, Jim Studt | Arduino Library Manager (`OneWire`) | 1-Wire communication protocol for DS18B20 |
| **DallasTemperature** | Miles Burton | Arduino Library Manager (`DallasTemperature`) | DS18B20 temperature sensor interface & conversions |
| **DHT sensor library** | Adafruit | Arduino Library Manager (`DHT sensor library`) | DHT22 relative humidity and secondary temperature reading |
| **Adafruit Unified Sensor** | Adafruit | Arduino Library Manager (`Adafruit Unified Sensor`) | Underlying dependency for Adafruit DHT sensor |
| **Adafruit INA219** | Adafruit | Arduino Library Manager (`Adafruit INA219`) | High-side DC voltage, current, and power monitoring via I²C |
| **Adafruit GFX Library** | Adafruit | Arduino Library Manager (`Adafruit GFX Library`) | Core graphics primitives for display rendering |
| **Adafruit SSD1306** | Adafruit | Arduino Library Manager (`Adafruit SSD1306`) | 128×64 monochrome OLED hardware driver (I²C address `0x3C`) |

---

## 3. Installation via Arduino Library Manager

1. Open **Arduino IDE**.
2. Navigate to **Tools → Manage Libraries...** (or press `Ctrl + Shift + I`).
3. Search for and install the following libraries one by one:
   - Type `DallasTemperature` → Click **Install** (select latest 3.9.x).
   - Type `OneWire` → Click **Install** (select latest 2.3.x).
   - Type `DHT sensor library` → Click **Install** (if prompted to install `Adafruit Unified Sensor`, click **Install All**).
   - Type `Adafruit INA219` → Click **Install**.
   - Type `Adafruit SSD1306` → Click **Install** (if prompted to install `Adafruit GFX Library`, click **Install All**).

---

## 4. Hardware Pin Configuration in Firmware

The pin definitions in `cold_store_controller.ino` map directly to the ESP32 DevKit V1:

```cpp
constexpr uint8_t DS18B20_PIN      = 4;   // 1-Wire Bus (requires 4.7 kΩ pull-up to 3.3V)
constexpr uint8_t DHT_PIN          = 27;  // DHT22 Data (requires 10 kΩ pull-up to 3.3V)
constexpr uint8_t BUZZER_PIN       = 25;  // Piezo Buzzer Signal (driven via tone())
constexpr uint8_t ALERT_LED_PIN    = 26;  // Alert Indicator LED (via 220 Ω resistor)
constexpr uint8_t CAM_RX_PIN       = 16;  // ESP32-CAM UART2 RX (Connect to CAM U0T)
constexpr uint8_t CAM_TX_PIN       = 17;  // ESP32-CAM UART2 TX (Connect to CAM U0R)
constexpr uint8_t I2C_SDA_PIN      = 21;  // Shared I2C Data (SSD1306 OLED + INA219)
constexpr uint8_t I2C_SCL_PIN      = 22;  // Shared I2C Clock (SSD1306 OLED + INA219)
```

---

## 5. Compilation & Upload Settings

1. Connect the ESP32 DevKit V1 board to your computer via micro-USB.
2. Under **Tools → Board → esp32**, select:
   - **DOIT ESP32 DEVKIT V1** (or **ESP32 Dev Module**)
3. Under **Tools → Port**, select the active COM port assigned to the CP2102 / CH340 USB-UART bridge.
4. Set **Upload Speed** to `921600` (or `115200` if flashing fails).
5. Click **Upload** (`Ctrl + U`). If the upload stalls at `Connecting........_____.....`, press and hold the **BOOT** button on the ESP32 until the flashing progress percentage begins.
6. Open **Tools → Serial Monitor** at **115200 baud** to view boot logs and IP assignment.
