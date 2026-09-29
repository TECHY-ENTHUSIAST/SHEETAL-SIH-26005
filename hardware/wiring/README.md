# Wiring & Electrical Harness Specification

This document details the wiring topology, wire gauges, grounding practices, and noise isolation guidelines for the **SHEETAL** solar cold storage system.

---

## 1. Prototype Wiring Connections (Benchtop Sensor Rig)

The physical prototype wiring between the **ESP32 DevKit V1** and external instrumentation is configured as follows:

```
                      ┌──────────────────────┐
                      │    ESP32 DEVKIT V1   │
                      │                      │
(VCC 3.3V) ───────────┤ 3V3                  │
(GND Common) ─────────┤ GND                  │
(PowerBoost 5V) ──────┤ VIN                  │
                      │                      │
(4.7k Pull-up to 3V3) ─┤ GPIO 4 (D4)          │ ◄─── DS18B20 Data (Yellow)
(10k Pull-up to 3V3) ──┤ GPIO 27 (D27)        │ ◄─── DHT22 Data (Out)
                      │ GPIO 21 (D21)        │ ◄─── I2C SDA (OLED & INA219)
                      │ GPIO 22 (D22)        │ ◄─── I2C SCL (OLED & INA219)
                      │ GPIO 25 (D25)        │ ────► Piezo Buzzer (+)
(220Ω Resistor) ───────┤ GPIO 26 (D26)        │ ────► Alert LED (Anode +)
                      │ GPIO 16 (RX2)        │ ◄─── ESP32-CAM U0T (TX)
                      │ GPIO 17 (TX2)        │ ────► ESP32-CAM U0R (RX)
                      └──────────────────────┘
```

### Color Code Conventions:
- **Red:** DC Positive (+3.3V or +5V)
- **Black:** DC Ground (GND)
- **Yellow / Green:** DS18B20 1-Wire Data
- **Blue / White:** DHT22 Data Line
- **Green (I²C):** SDA Line (`GPIO 21`)
- **Yellow (I²C):** SCL Line (`GPIO 22`)

---

## 2. Wire Gauge & Current Capacity Specification (Full System)

For the field unit operating with the full 48 V solar power and vapor-compression system, wire gauges must adhere to the following standards:

| Circuit Domain | Voltage & Current | Recommended Wire Size | Insulation Rating | Notes |
| :--- | :---: | :---: | :---: | :--- |
| **Solar PV Array to MPPT** | ~125 V DC, ~14 A max | **4.0 mm² (12 AWG)** | Double-insulated, UV-resistant cross-linked polyolefin | Photovoltaic dedicated cable with MC4 connectors |
| **Battery Bank to Inverter** | 48 V DC, ~45 A continuous (100 A surge) | **16.0 mm² – 25.0 mm² (4–3 AWG)** | Heavy-duty flexible stranded copper | Fitted with tinned copper ring lugs, heat-shrink and Class-T fuse |
| **Inverter AC Output to AC Distribution** | 230 V AC, ~8.7 A max | **2.5 mm² (14 AWG)** | 3-Core PVC/XLPE (L, N, PE) | Routed via 16 A MCB + 30 mA RCBO |
| **AC Contactor to Compressor** | 230 V AC, ~2.5 A (LRA ~15 A) | **2.5 mm² (14 AWG)** | Flexible rubber/neoprene sheath | Mechanical vibration protection loop |
| **DC-DC Step-Down to Fans** | 12 V DC, ~2.0 A max | **1.0 mm² (18 AWG)** | Multi-strand copper | Automotive style spade/screw terminals |
| **Low-Voltage Sensors (DS18B20 / I²C)** | 3.3 V DC, < 20 mA | **0.2 mm² – 0.5 mm² (24–26 AWG)** | Shielded twisted pair | Drain wire bonded to DC ground at controller end only |

---

## 3. Electromagnetic Compatibility (EMC) & Noise Isolation

Vapor-compression compressors generate significant inductive back-EMF and electrical switching noise during start-up. To ensure the ESP32 microcontroller and 1-Wire / I²C sensor buses do not suffer transient resets or bus lockups:

1. **Galvanic Isolation:** The ESP32 logic never directly energizes inductive compressor windings. Control signals pass through an **optoisolated relay board** to switch a 230 V AC coil contactor.
2. **Physical Cable Separation:** Low-voltage DC sensor cables (1-Wire, I²C, UART) must be routed in a separate conduit with a minimum clearance of **150 mm** from 230 V AC power lines and inverter AC cables. Never run sensor lines parallel to compressor wiring.
3. **Shield Grounding:** Sensor shield braids must be grounded at one single point (the controller star-ground) to prevent ground loops.
4. **Snubber Protection:** RC snubbers or metal oxide varistors (MOV) should be installed across inductive contactor coils to clamp voltage spikes.

---

## 4. Status

- **Benchtop Prototype Wiring:** Validated on breadboard / prototype perfboard.
- **Field Wire Harness CAD:** `To be added after prototype testing.`
