# Engineering Calculations & Thermodynamic Derivations

This document details the first-principles engineering calculations for the **SHEETAL** solar cold storage system.

Every calculation is strictly classified following engineering reporting standards:
- **Evidence-Based:** Empirical values sourced from standards, datasheets, or peer-reviewed literature.
- **Calculated:** Values obtained through mathematical derivation.
- **Engineering Assumption:** Assumed design boundary conditions.
- **Design Target:** Sizing objective (not yet experimentally validated).

---

## 1. Product Sensible Pull-Down Thermal Load

Calculates the thermal energy required to chill 200 kg of fresh tomatoes from daytime field harvest temperature to safe cold storage setpoint.

- **Given:**
  - Produce Mass ($m$): $200\text{ kg}$
  - Reference Crop: Fresh Market Tomato (*Solanum lycopersicum*)
  - Specific Heat Capacity of Tomato above freezing ($C_p$): $3.99\text{ kJ/(kg}\cdot\text{K)}$ *(Evidence-Based — ASHRAE Food Properties Handbook)*
  - Incoming Field Harvest Temperature ($T_{\text{in}}$): $30.0^\circ\text{C}$ ($303.15\text{ K}$) *(Engineering Assumption — typical peak afternoon harvest)*
  - Target Produce Temperature ($T_{\text{target}}$): $10.0^\circ\text{C}$ ($283.15\text{ K}$) *(Prototype Target — prevents chilling injury)*
  - Temperature Delta ($\Delta T$): $30.0^\circ\text{C} - 10.0^\circ\text{C} = 20.0\text{ K}$

- **Formula:**
  $$Q_{\text{product}} = m \times C_p \times \Delta T$$

- **Substitution:**
  $$Q_{\text{product}} = 200\text{ kg} \times 3.99\text{ kJ/(kg}\cdot\text{K)} \times 20\text{ K} = 15,960\text{ kJ}$$

- **Conversion to Thermal Energy (kWh_th):**
  $$Q_{\text{product}} = \frac{15,960\text{ kJ}}{3,600\text{ s/h}} \approx 4.433\text{ kWh}_{\text{thermal}}$$

- **Classification:** **[CALCULATED]**

> [!NOTE]
> **Source Discrepancy Note:** Early handwritten project notes contained an errant unit typo reading *"443 kW"*. The correct derivation is $15,960\text{ kJ} / 3,600\text{ s} = \mathbf{4.433\text{ kWh}_{\text{thermal}}}$.

---

## 2. Envelope Conduction (Wall Transmission) Load

Calculates the continuous 24-hour heat infiltration through the insulated polyurethane foam (PUF) chamber walls.

- **Given:**
  - Internal Chamber Dimensions: $1.2\text{ m} \times 1.2\text{ m} \times 1.0\text{ m}$ (Gross internal volume: $1.44\text{ m}^3$)
  - Insulation Material: Rigid Polyurethane Foam (PUF), thickness $d = 0.10\text{ m}$ ($100\text{ mm}$)
  - PUF Thermal Conductivity ($k$): $0.023\text{ W/(m}\cdot\text{K)}$ *(Evidence-Based — standard PUF datasheet)*
  - Mean Chamber Surface Area ($A$): $\approx 7.68\text{ m}^2$ (interior baseline) to $9.10\text{ m}^2$ (external mean)
  - Design Ambient Temperature ($T_{\text{amb}}$): $35.0^\circ\text{C}$ *(Engineering Assumption — peak NER summer)*
  - Internal Setpoint Temperature ($T_{\text{int}}$): $10.0^\circ\text{C}$
  - Temperature Delta ($\Delta T$): $35.0^\circ\text{C} - 10.0^\circ\text{C} = 25.0\text{ K}$

- **Formulas:**
  $$U = \frac{k}{d} = \frac{0.023\text{ W/(m}\cdot\text{K)}}{0.10\text{ m}} = 0.230\text{ W/(m}^2\cdot\text{K)}$$
  $$\dot{Q}_{\text{wall}} = U \times A \times \Delta T$$
  $$Q_{\text{wall, 24h}} = \frac{\dot{Q}_{\text{wall}} \times 24\text{ h}}{1000}$$

- **Substitution:**
  $$\dot{Q}_{\text{wall}} = 0.230\text{ W/(m}^2\cdot\text{K)} \times 7.68\text{ m}^2 \times 25.0\text{ K} = 44.16\text{ W}$$
  $$Q_{\text{wall, 24h}} = \frac{44.16\text{ W} \times 24\text{ h}}{1000} \approx 1.06\text{ kWh}_{\text{thermal}}/\text{day}$$

- Accounting for corner thermal bridging factor (+20%):
  $$Q_{\text{wall, total}} \approx 1.23 - 1.27\text{ kWh}_{\text{thermal}}/\text{day}$$

- **Classification:** **[CALCULATED]**

---

## 3. Total Daily Thermal Load & Refrigeration Sizing

Combines all thermal load components across a 24-hour cycle:

| Load Component | Energy Contribution | Derivation / Source |
| :--- | :---: | :--- |
| **Product Sensible Pull-down** | $4.43\text{ kWh}_{\text{th}}$ | Calculated (Section 1) |
| **Envelope Transmission (24 h)** | $1.23\text{ kWh}_{\text{th}}$ | Calculated (Section 2) |
| **Produce Respiration Heat** | $0.07\text{ kWh}_{\text{th}}$ | Evidence-Based ($15\text{ mW/kg}$ for tomato at 10°C) |
| **Infiltration & Door Openings** | $0.42\text{ kWh}_{\text{th}}$ | Engineering Assumption (6–10 brief accesses/day) |
| **Internal Fans & Auxiliary Loss**| $0.15\text{ kWh}_{\text{th}}$ | Engineering Assumption (Circulation fan motor dissipation) |
| **TOTAL DAILY THERMAL LOAD** | **$6.30\text{ kWh}_{\text{thermal}}/\text{day}$** | **Summation** |

- **Required Cooling Capacity Sizing:**
  Targeting an 8 to 10.5 hour daytime operating window ($t_{\text{run}} = 10.5\text{ h}$):
  $$\dot{Q}_{\text{refrig}} = \frac{6.30\text{ kWh}_{\text{th}}}{10.5\text{ h}} = 0.600\text{ kW}_{\text{th}} = \mathbf{600\text{ W}_{\text{thermal}}}$$

- **Classification:** **[CALCULATED / DESIGN TARGET]**

---

## 4. Phase Change Material (PCM) Thermal Battery Mechanics

Quantifies the latent thermal energy capacity stored by the PCM thermal accumulator.

- **Given:**
  - PCM Chemistry: Inorganic Salt Hydrate (Pluss savE® HS10 / IP08)
  - Phase Change Temperature: $8.0^\circ\text{C} - 12.0^\circ\text{C}$ (Nominal setpoint: $10.0^\circ\text{C}$)
  - Latent Heat of Fusion ($L$): $\approx 180\text{ kJ/kg}$ *(Evidence-Based — manufacturer datasheet)*
  - Sizing Mass ($m_{\text{PCM}}$): $25.0\text{ kg}$ (Encapsulated in 10 × 2.5 kg modular HDPE cassettes)

- **Formula:**
  $$Q_{\text{PCM}} = m_{\text{PCM}} \times L$$

- **Substitution:**
  $$Q_{\text{PCM}} = 25\text{ kg} \times 180\text{ kJ/kg} = 4,500\text{ kJ}$$
  $$Q_{\text{PCM, kWh}} = \frac{4,500\text{ kJ}}{3,600\text{ s/h}} = \mathbf{1.25\text{ kWh}_{\text{thermal}}}$$

- **Theoretical Passive Holdover Duration:**
  Assuming static holding conditions where only transmission heat ($44.16\text{ W}$) acts on the chamber:
  $$t_{\text{holdover}} = \frac{1,250\text{ Wh}_{\text{th}}}{44.16\text{ W}} \approx 28.3\text{ Hours}$$
  *Real-world holding is reduced by door openings, respiration, and cassette air-convective resistance.*

- **Classification:** **[CALCULATED — Physical backup duration is a DESIGN TARGET requiring experimental validation]**

---

## 5. Electrical Energy Budget & Battery Autonomy

- **Daily Electrical Demand:**
  - Total thermal load: $6.30\text{ kWh}_{\text{th}}$
  - Expected Coefficient of Performance ($\text{COP}$): $2.0$ *(Engineering Assumption for R290 small hermetic cycle)*
  - Compressor electrical energy:
    $$E_{\text{comp}} = \frac{6.30\text{ kWh}_{\text{th}}}{2.0} = 3.15\text{ kWh}_{\text{elec}}$$
  - Continuous auxiliary load (ESP32, sensors, 12V fans, display ~15 W continuous):
    $$E_{\text{aux}} = 15\text{ W} \times 24\text{ h} = 0.36\text{ kWh}_{\text{elec}}$$
  - Inverter standby and conversion losses (~10%): $0.49\text{ kWh}_{\text{elec}}$
  - Total Daily Electrical Demand: **$4.00\text{ kWh}_{\text{electrical}}/\text{day}$**

- **Battery Sizing & Autonomous Runtime:**
  - Battery Bank: $48\text{ V}, 100\text{ Ah}$ Lithium Iron Phosphate ($\text{LiFePO}_4$)
  - Nominal Capacity: $48\text{ V} \times 100\text{ Ah} = 4,800\text{ Wh} = 4.80\text{ kWh}$
  - Recommended Maximum Depth of Discharge (DoD): $80\%$ *(Evidence-Based — preserves cycle life)*
  - Usable DC Energy: $4.80\text{ kWh} \times 0.80 = 3.84\text{ kWh}$
  - Usable AC Energy after Inverter ($\eta = 90\%$): $3.84\text{ kWh} \times 0.90 = 3.456\text{ kWh}_{\text{AC}}$
  - Electrical Autonomy Runtime at ~300 W equivalent average load:
    $$t_{\text{autonomy}} = \frac{3,456\text{ Wh}_{\text{AC}}}{300\text{ W}} \approx \mathbf{11.52\text{ Hours}}$$

- **Classification:** **[CALCULATED]**

---

## 6. Solar Photovoltaic (PV) Array Sizing

- **Given:**
  - Daily Electrical Demand ($E_{\text{daily}}$): $4.00\text{ kWh}_{\text{elec}}/\text{day}$
  - Peak Sun Hours in NER ($PSH$): $4.5\text{ Hours/day}$ *(Engineering Assumption — regional average)*
  - Balance of System (BOS) Efficiency ($\eta_{\text{sys}}$): $75\%$ ($0.75$) *(Engineering Assumption — covers dust, cabling, thermal derating)*

- **Theoretical Minimum Solar PV Array:**
  $$P_{\text{PV, min}} = \frac{E_{\text{daily}}}{PSH \times \eta_{\text{sys}}} = \frac{4.0\text{ kWh}}{4.5\text{ h} \times 0.75} \approx 1.185\text{ kWp}$$

- **Selected Practical Array Sizing:**
  - Sized with **+38.7% safety margin** to counter monsoonal overcast and winter fog in the North Eastern Region:
    $$P_{\text{PV, selected}} = 3 \times 550\text{ Wp (Monocrystalline Half-Cut PERC)} = \mathbf{1.65\text{ kWp}}$$

- **Classification:** **[CALCULATED / PROTOTYPE TARGET]**
