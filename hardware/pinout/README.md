# ESP32 Pinout & Interfacing Guide

This document defines the physical pin mapping for the **SHEETAL** controller on the **ESP32 DevKit V1 (ESP32-WROOM-32, 30-Pin)**.

All pin assignments below match the constants defined in [`firmware/cold_store_controller.ino`](../../firmware/cold_store_controller.ino) and the hardware schematic in [`hardware/schematic/`](../schematic/).

---

## 1. Controller Pin Assignment Table

| ESP32 Pin | GPIO | Function / Signal Name | Connected Hardware | Electrical Interface & Passive Requirements | Status |
| :--- | :---: | :--- | :--- | :--- | :--- |
| **D4** | **GPIO 4** | `DS18B20_PIN` | DS18B20 Digital Temp Probe | 1-Wire Digital Bus with **4.7 kΩ pull-up resistor** to 3.3V | Verified (Active) |
| **D27** | **GPIO 27** | `DHT_PIN` | DHT22 / AM2302 Sensor | Single-Bus Digital with **10 kΩ pull-up resistor** to 3.3V | Verified (Active) |
| **D21** | **GPIO 21** | `I2C_SDA_PIN` | SSD1306 OLED & INA219 | Shared I²C Serial Data (Hardware I2C0) | Verified (Active) |
| **D22** | **GPIO 22** | `I2C_SCL_PIN` | SSD1306 OLED & INA219 | Shared I²C Serial Clock (Hardware I2C0) | Verified (Active) |
| **D25** | **GPIO 25** | `BUZZER_PIN` | Active/Passive Piezo Buzzer | Digital Output driven by `tone()` at 2200 Hz | Verified (Active) |
| **D26** | **GPIO 26** | `ALERT_LED_PIN` | Red Status Indicator LED | Digital Output with **220 Ω current-limiting resistor** | Verified (Active) |
| **RX2 / D16**| **GPIO 16** | `CAM_RX_PIN` | ESP32-CAM Node | Hardware Serial 2 (UART2 RX) ← ESP32-CAM `U0T` (115200 baud) | Verified (Active) |
| **TX2 / D17**| **GPIO 17** | `CAM_TX_PIN` | ESP32-CAM Node | Hardware Serial 2 (UART2 TX) → ESP32-CAM `U0R` (115200 baud) | Verified (Active) |
| **VIN** | — | System 5V Power Input | PowerBoost 1000C (5V Out) | Regulated 5.0 V DC power input | Verified (Active) |
| **3V3** | — | 3.3V Logic Supply | Sensor VCC (DS18B20, DHT22) | Regulated 3.3 V output from onboard LDO | Verified (Active) |
| **GND** | — | System Ground | Common Ground Bus | Connected to all sensor GNDs and peripheral returns | Verified (Active) |

---

## 2. Shared I²C Bus Architecture

Both the OLED display and the INA219 power monitor share the ESP32 hardware I²C bus on `GPIO 21` (SDA) and `GPIO 22` (SCL):

| Device | Model | Default I²C Address | Role in System |
| :--- | :--- | :---: | :--- |
| **Local Display** | SSD1306 (128×64 Monochrome) | `0x3C` | Local temperature, humidity, power, and alarm display |
| **Power Monitor** | Adafruit INA219 High-Side Shunt | `0x40` | Bus voltage, current (mA), and power (mW) monitoring |

*Note: Both breakout boards contain internal 4.7 kΩ or 10 kΩ pull-up resistors on the I²C lines to 3.3V.*

---

## 3. Hardware / Firmware Verification Matrix

| Item | Schematic Verification | Firmware Definition | Functional Test Status |
| :--- | :---: | :---: | :---: |
| DS18B20 on GPIO 4 | Yes | `constexpr uint8_t DS18B20_PIN = 4;` | Validated in code |
| DHT22 on GPIO 27 | Yes | `constexpr uint8_t DHT_PIN = 27;` | Validated in code |
| Shared I²C on GPIO 21 & 22 | Yes | `I2C_SDA_PIN = 21`, `I2C_SCL_PIN = 22` | Validated in code |
| Buzzer on GPIO 25 | Yes | `constexpr uint8_t BUZZER_PIN = 25;` | Validated in code |
| Alert LED on GPIO 26 | Yes | `constexpr uint8_t ALERT_LED_PIN = 26;` | Validated in code |
| ESP32-CAM on UART2 (16/17) | Yes | `CAM_RX_PIN = 16`, `CAM_TX_PIN = 17` | Validated in code |

---

## 4. Planned Actuation Pins (Next Revision)

The following pins are designated in the engineering design report for future closed-loop actuation and safety interlocks:

| Signal | Planned GPIO | Target Interface | Purpose |
| :--- | :---: | :--- | :--- |
| **Door Reed Switch** | `GPIO 13` | Digital Input (Internal Pull-Up) | Detects door open; triggers alarm if ajar > 30 s |
| **Compressor Relay** | `GPIO 23` | Optoisolated Output to Contactor | Switched AC contactor control (with 3-min dwell protection) |
| **Circulation Fan PWM**| `GPIO 14` | Logic-Level N-MOSFET (Gate PWM) | Variable speed modulation for evaporator fans |
