# Master Bill of Materials (BOM)

This document provides the complete engineering Bill of Materials for the **SHEETAL** solar cold storage system, distinguishing the active **monitoring prototype electronics** from the **full-scale field system components**.

---

## 1. Electronics & Instrumentation BOM (Active Hardware Prototype)

Components implemented in the benchtop monitoring and supervisory control unit:

| Item | Component | Purpose | Interface / Pin | Qty | Engineering Status |
| :---: | :--- | :--- | :---: | :---: | :--- |
| **E-01** | ESP32 DevKit V1 (ESP32-WROOM-32D) | Main supervisory microcontroller | USB / GPIO | 1 | Verified in schematic & firmware |
| **E-02** | DS18B20 Digital Temperature Probe | Primary chamber/produce temperature | GPIO 4 (1-Wire) | 1 | Verified in schematic & firmware |
| **E-03** | DHT22 / AM2302 Sensor Module | Relative humidity & secondary air temp | GPIO 27 (Digital) | 1 | Verified in schematic & firmware |
| **E-04** | Adafruit INA219 Breakout Board | Bus voltage, current, and power monitoring | GPIO 21/22 (I²C) | 1 | Verified in schematic & firmware |
| **E-05** | SSD1306 0.96" OLED Display (128×64) | Local operator dashboard display | GPIO 21/22 (I²C) | 1 | Verified in schematic & firmware |
| **E-06** | AI-Thinker ESP32-CAM Node | Visual produce monitoring & crate fill level | GPIO 16/17 (UART2)| 1 | Schematic verified; CAM firmware: To be added |
| **E-07** | Alert LED Indicator (Red, 5 mm) | Visual threshold violation warning | GPIO 26 | 1 | Verified in schematic & firmware |
| **E-08** | Piezo Buzzer (Active / Passive) | Audible threshold violation warning | GPIO 25 | 1 | Verified in schematic & firmware |
| **E-09** | Metal Film Resistors (4.7k, 10k, 220Ω) | Pull-up & LED current limiting | Discrete | 1 lot | Verified in schematic |
| **E-10** | Adafruit PowerBoost 1000C | 5V DC step-up regulator & Li-ion charger | Discrete | 1 | Prototype supply (To be confirmed vs 48V buck) |
| **E-11** | Li-ion 3.7V 2000 mAh Cell (JST-PH) | Portable benchtop battery power | Discrete | 1 | Prototype supply (To be confirmed vs 48V buck) |
| **E-12** | Magnetic Reed Switch | Cold room door position detection | GPIO 13 (Planned) | 1 | Planned; to be added to PCB revision |
| **E-13** | Optocoupled Relay Module (4-Channel) | Galvanic isolation for compressor switching| GPIO 23 (Planned) | 1 | Planned; to be added to PCB revision |

---

## 2. Complete Field System Engineering BOM (200 kg Off-Grid Cold Store)

The table below details the subsystem components sized in the engineering design report (`SIH_26005_Engineering_Design_Document.md`):

| Subsystem | Component Description | Detailed Specification | Qty | Engineering Classification | Estimated Cost (INR) |
| :--- | :--- | :--- | :---: | :--- | :---: |
| **Cold Chamber** | Modular Cam-Lock PUF Panels | 100 mm rigid PUF ($k \approx 0.023\text{ W/mK}$), PPGI skin | 6 panels | Selected Baseline | ₹32,000 |
| **Cold Chamber** | Insulated Hinged Cold Room Door | 700 × 900 mm, 100 mm PUF, magnetic gasket, safety latch | 1 set | Selected Baseline | ₹12,500 |
| **Cold Chamber** | Agricultural Stacking Crates | Food-grade HDPE ventilated crates (20 kg capacity) | 10 pcs | Selected Baseline | ₹4,500 |
| **Refrigeration** | R290 Hermetic Condensing Unit | Embraco EMT6165U / MTH class (600 W thermal output) | 1 set | **Provisional / TBD** *(see note below)* | ₹28,000 |
| **Refrigeration** | Finned Evaporator Coil | Copper tube, aluminum fins, 700–800 W heat transfer | 1 unit | Selected Baseline | ₹7,500 |
| **Refrigeration** | Evaporator Circulation Fans | 12 V DC / IP55 rated brushless fans | 2 units | Selected Baseline | ₹2,800 |
| **Refrigeration** | Matched Capillary Tube | Throttling expansion device sized for R290 mass flow | 1 set | Selected Baseline (Length TBD) | ₹800 |
| **Refrigeration** | Filter Drier & Sight Glass | Hermetic molecular sieve filter drier | 1 unit | Selected Baseline | ₹1,200 |
| **Refrigeration** | Certified R290 Refrigerant Charge | High-purity refrigerant-grade propane | 1 can | Selected Baseline | ₹1,500 |
| **PCM Buffer** | Inorganic Salt Hydrate PCM | Pluss savE® HS10 / IP08 (10°C melting, $180\text{ kJ/kg}$) | 25 kg | **Prototype Target** | ₹15,000 |
| **PCM Buffer** | Sealed HDPE PCM Cassettes | Slim-profile blow-molded containers ($10 \times 2.5\text{ kg}$) | 10 pcs | **Prototype Target** | ₹3,500 |
| **Solar PV** | Monocrystalline PERC PV Panels | 550 Wp Half-Cut Monocrystalline Panels (Tier 1) | 3 panels | Selected Baseline (1.65 kWp) | ₹42,000 |
| **Solar PV** | Module Mounting Structure (MMS) | Galvanized iron ground / shed roof mount | 1 set | Selected Baseline | ₹6,500 |
| **Solar PV** | MPPT Solar Charge Controller | 48 V / 50 A Maximum Power Point Tracking Controller | 1 unit | Selected Baseline | ₹14,000 |
| **Battery Bank** | LiFePO4 Battery Pack | 48 V, 100 Ah (4.80 kWh nominal) with integrated BMS | 1 unit | Selected Baseline | ₹65,000 |
| **Power Inversion**| Pure Sine Wave Inverter | 2.0 kVA / 48 V DC to 230 V AC (High Motor Surge Capable) | 1 unit | Selected Baseline | ₹18,000 |
| **Protection** | DC Isolator & Surge Protection (SPD)| 1000 V DC 32 A 2-Pole Isolator + Type II SPD | 1 set | Selected Baseline | ₹4,200 |
| **Protection** | Battery Fuse & DC Circuit Breaker | 125 A 2-Pole DC Breaker + Class-T Fuse | 1 set | Selected Baseline | ₹3,500 |
| **Protection** | AC Distribution Board | 16 A DP MCB + 30 mA RCBO Earth Leakage Breaker | 1 set | Selected Baseline | ₹2,800 |
| **Protection** | Emergency Stop Switch | Red mushroom latching safety stop button | 1 unit | Selected Baseline | ₹950 |
| **Electronics** | Supervisory Controller Enclosure | IP65 Polycarbonate Weatherproof Enclosure | 1 unit | Selected Baseline | ₹2,800 |
| **Electronics** | DC-DC Step-Down Buck Converter | 48 V to 12 V / 5 V Synchronous Buck (5 A continuous) | 1 unit | Selected Baseline | ₹1,400 |
| **Electronics** | Industrial AC Power Contactor | 230 V AC Coil, 20 A inductive rated contactor | 1 unit | Selected Baseline | ₹1,650 |
| **Cabling** | Solar & Battery Cable Harness | 4 mm² Solar DC + 25 mm² Battery Cable + PG Glands | 1 lot | Selected Baseline | ₹6,500 |
| **Labor** | Certified Refrigeration Technician | Nitrogen pressure test, vacuum evacuation & brazing | 1 job | Selected Baseline | ₹8,500 |
| **TOTAL** | **Full-Scale Field System Estimate**| **200 kg Off-Grid Cold Storage Solution** | — | — | **₹2,92,850 (~$3,500 USD)** |

---

## 3. Important Open Engineering Items & Discrepancy Notice

> [!WARNING]
> **Open Engineering Items Requiring Resolution:**
> 1. **Compressor Rating:** Notebook records contain conflicting entries between 1/4 HP (initial calculation) and 0.5–0.75 HP (commercial condensing search). Sizing must be resolved by verified compressor displacement curves matching 600 W cooling output at 2°C / 45°C evaporating/condensing temperatures.
> 2. **PCM Product Identification:** Denoted as "IP08" and "HS10" in project records. Datasheet for Pluss savE® HS10 / IP08 is recorded in [`research/`](../../research/); exact commercial supplier procurement is provisional.
> 3. **R290 Refrigerant Safety:** R290 (propane) is an ASHRAE A3 flammable refrigerant. Mechanical charging and brazing must strictly follow safety protocols and be conducted by a certified refrigeration technician in a well-ventilated space.
