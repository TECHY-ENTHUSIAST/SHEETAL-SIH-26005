# Monitoring Dashboard

This folder documents the real-time monitoring interfaces for the **SHEETAL** cold storage system.

> [!IMPORTANT]
> **Deployment Status:**  
> The dashboard operates strictly as an **ESP32-hosted Live Monitoring Dashboard** served over a local Wi-Fi connection or local SoftAP hotspot directly from the microcontroller.  
> It is **NOT** an online cloud dashboard or externally hosted website. No external cloud server is required for full local operation.

---

## 1. Primary Interface: ESP32-Hosted Live Monitoring Dashboard

The primary monitoring interface is served directly from the ESP32's flash memory (`INDEX_HTML` in [`firmware/cold_store_controller.ino`](../firmware/cold_store_controller.ino)) via its built-in HTTP server on port 80.

### Features:
- **Zero Internet Requirement:** Functions completely off-grid. When no existing router is available, the ESP32 generates its own fallback Wi-Fi Access Point (`SSID: ColdStore-Setup`, `IP: 192.168.4.1`).
- **Telemetry Monitored:**
  - Storage Temperature (`°C`) via DS18B20 reference probe
  - Chamber Ambient Temperature (`°C`) & Relative Humidity (`%`) via DHT22
  - DC System Voltage (`V`), Bus Current (`mA`), and Power (`mW`) via INA219
  - Supervisory System State (`TARGET RANGE`, `UPPER RANGE`, `COOLING PROTECT`, `HIGH TEMP ALERT`, `TRANSITION`, `SENSOR FAULT`)
  - Active Alert Diagnostics (`NONE`, `HIGH TEMPERATURE`, `LOW TEMPERATURE`, `LOW SYSTEM VOLTAGE`, sensor faults)
  - Visual Node Heartbeat (`CAM_OK` message via UART2 within last 60 seconds)
  - CSV Data Export via download button (`/api/history`)

### REST API Endpoints:

| Endpoint | HTTP Method | Response Content | Description |
| :--- | :---: | :--- | :--- |
| `/` | `GET` | HTML / CSS / JS | Built-in responsive dashboard interface |
| `/api/readings` | `GET` | `application/json` | Current sensor telemetry and system health state |
| `/api/history` | `GET` | `text/csv` | Downloadable CSV stream of the last 24 sampled sensor records |

#### Sample `/api/readings` JSON Payload:
```json
{
  "uptime_s": 4218,
  "storage_temp_c": 9.42,
  "dht_temp_c": 9.80,
  "humidity_pct": 91.5,
  "system_voltage_v": 5.08,
  "current_ma": 182.4,
  "power_mw": 926.6,
  "status": "TARGET RANGE",
  "alert": "NONE",
  "camera_heartbeat": true,
  "wifi_mode": "STA"
}
```

---

## 2. Extended Companion Interface: `dashboard.html`

In addition to the lightweight embedded page, a rich client-side dashboard is provided in [`dashboard/dashboard.html`](dashboard.html).

### Capabilities:
- Modern dark-mode user interface designed for tablets and laptops.
- Live animated temperature range gauge with zone markers:
  - `< 6°C` (Cooling Protect / Blue)
  - `6–10°C` (Target Range / Green)
  - `10–12°C` (Upper Range / Yellow)
  - `12–13°C` (Transition / Orange)
  - `≥ 13°C` (High Temperature Alert / Red)
- Real-time rolling graphical trend charts rendered with Chart.js:
  - Dual-curve temperature trend (DS18B20 vs DHT22)
  - Chamber relative humidity (%)
  - Multi-axis electrical monitoring (Voltage, Current, Power)
- Formatted tabular view of recent readings with direct CSV download link.

### How to Run `dashboard.html`:
1. Connect your laptop, tablet, or smartphone to the same Wi-Fi network as the ESP32 (or connect to the `ColdStore-Setup` SoftAP).
2. Open `dashboard.html` directly in any standard web browser (Chrome, Firefox, Edge, Safari).
3. Enter the ESP32's assigned IP address (e.g. `192.168.1.150` or `192.168.4.1`) in the top navigation bar and click **Connect**.
4. The dashboard will automatically begin polling `/api/readings` every 3 seconds and `/api/history` every 15 seconds.

---

## 3. Screenshots

*Dashboard UI screenshots:* `To be added after prototype testing (images/dashboard/).`
