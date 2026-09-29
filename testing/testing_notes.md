# Testing & Experimental Validation Notes

This document establishes the empirical verification framework for the **SHEETAL** prototype, cataloguing planned test protocols, first-principles calculations, design targets, and claims pending physical laboratory validation.

---

## 1. Prototype Measurements

> [!IMPORTANT]
> **Current Status: No Physical Chamber Measurements Recorded Yet.**  
> The physical benchtop monitoring electronics (ESP32, DS18B20, DHT22, INA219, OLED) have undergone initial bench bring-up and firmware validation. However, physical thermal pull-down data inside the 1.44 m³ cold chamber with full refrigeration and PCM has **not yet been recorded**.  
> [`testing/test_results.csv`](test_results.csv) holds only schema headers and will be populated solely with real measured data during Stage 9 trials.

---

## 2. Planned Experimental Test Matrix (Stage 9 Commissioning)

The following eight standardized tests are scheduled for physical validation:

| Test ID | Test Protocol | Objective | Pass / Acceptance Criteria | Status |
| :---: | :--- | :--- | :--- | :---: |
| **TEST-01** | Empty Chamber Thermal Pull-Down | Verify base refrigeration power without thermal product load ($T_{\text{amb}} = 30^\circ\text{C}$). | Chamber reaches $10.0^\circ\text{C}$ in $\le 60\text{ minutes}$; compressor cycling stable. | **Planned** |
| **TEST-02** | Spatial Temperature Uniformity | Quantify thermal air stratification across top, middle, and bottom crate tiers. | Temperature spread $|T_{\text{max}} - T_{\text{min}}| \le \pm 1.0\text{ K}$ across all points. | **Planned** |
| **TEST-03** | Step-Load Transient Response | Evaluate thermal recovery under partial loading (50 kg and 100 kg warm produce). | Chamber returns to $\le 11.0^\circ\text{C}$ within 90 minutes of crate loading. | **Planned** |
| **TEST-04** | Full 200 kg Design Pull-Down | Benchmark full-load cooling transient with 200 kg tomatoes ($30^\circ\text{C} \rightarrow 10^\circ\text{C}$). | Produce core temperature reaches $10.0^\circ\text{C}$ within 8 to 10 hours. | **Planned** |
| **TEST-05** | Door Infiltration Dynamics | Measure chamber temperature rise and recovery after user access (30 s and 60 s door open). | Full recovery to $10.0^\circ\text{C}$ in $\le 15\text{ minutes}$; reed switch alert operates. | **Planned** |
| **TEST-06** | PCM Latent Charge Cycle | Measure freezing dynamics of the 25 kg inorganic salt hydrate cassettes. | PCM probe (T4) records solid phase transition plateau ($8^\circ\text{C}-10^\circ\text{C}$) in $\le 6\text{ h}$. | **Planned** |
| **TEST-07** | Thermal Power-Failure Holdover | Measure passive temperature holding duration with AC compressor power disconnected. | Chamber air holds $< 13.0^\circ\text{C}$ for $\ge 6 - 12\text{ hours}$ purely via PCM melting. | **Planned** |
| **TEST-08** | Solar & Battery Autonomous Run | Verify continuous 24-hour off-grid stability through day solar and night battery power. | Zero grid reliance; Battery SOC remains $> 30\%$ throughout overnight run. | **Planned** |

---

## 3. Classification of System Performance Claims

To maintain absolute technical integrity, all project claims are classified into their exact evidentiary category:

### 3.1 Prototype Measurements
- ESP32 boot cycle, sensor communication on 1-Wire (`GPIO 4`), DHT22 single-bus (`GPIO 27`), and shared I²C (`GPIO 21/22`) verified on test bench.
- Local SoftAP network creation (`ColdStore-Setup`) and HTTP API response verified on local network.

### 3.2 Engineering Calculations
- **Product Pull-Down Sensible Heat:** $4.43\text{ kWh}_{\text{th}}$ ($200\text{ kg} \times 3.99\text{ kJ/kg}\cdot\text{K} \times 20\text{ K}$).
- **Daily Envelope Transmission Loss:** $1.23\text{ kWh}_{\text{th}}$ ($100\text{ mm PUF}, U \approx 0.23\text{ W/m}^2\text{K}, \Delta T = 25\text{ K}$).
- **Total Working Daily Thermal Load:** $\approx 6.30\text{ kWh}_{\text{th}}/\text{day}$.
- **PCM Latent Thermal Energy Stored:** $1.25\text{ kWh}_{\text{th}}$ ($25\text{ kg} \times 180\text{ kJ/kg}$).
- **Battery Electrical Autonomy:** $\approx 11.5\text{ Hours}$ ($48\text{ V } 100\text{ Ah LiFePO}_4 @ 80\%\text{ DoD}, 300\text{ W load}$).
- **Theoretical Minimum Solar PV Array:** $1.19\text{ kWp}$ ($4.0\text{ kWh} / (4.5\text{ PSH} \times 0.75)$).

### 3.3 Design Targets
- **Produce Storage Capacity:** 200 kg fresh produce (~10 standard 20 kg crates).
- **Nominal Chamber Setpoint:** $10.0^\circ\text{C}$ ($\pm 1.0^\circ\text{C}$ band).
- **Chamber Air Relative Humidity:** $90\% - 95\%\text{ RH}$.
- **Refrigeration Cooling Power:** $600\text{ W}_{\text{thermal}}$ at $2^\circ\text{C} - 5^\circ\text{C}$ evaporating temperature.
- **Combined Thermal Buffering Window:** **24 to 48 Hours** *(Design Target — not yet experimentally validated)*.

---

## 4. Not Yet Validated: Claims Requiring Physical Chamber Testing

The following claims require physical empirical data before they can be considered validated engineering facts:

1. **24–48 Hours of Thermal Buffering:** While first-principles calculations indicate theoretical holdover capability, actual holdover depends on cassette surface thermal conductivity, fan convection, door opening cycles, and produce respiration. **This claim requires physical execution of TEST-07.**
2. **Refrigeration System Working COP of 2.0:** Requires simultaneous thermal heat extraction calorimetry and electrical input power logging on the physical test bench.
3. **Internal Air Temperature Uniformity Within ±1.0 K:** Requires multi-point logging across 3-tier crate stacks under full airflow in TEST-02.
4. **Autonomous Solar Operation During Extended Monsoon Overcast:** Requires continuous 72-hour field trial under heavy cloud cover in TEST-08.
