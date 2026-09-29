# Research References & Engineering Evidence

This document catalogues the formal research papers, governmental data sources, technical handbooks, and commercial datasheets underpinning the engineering design choices in **SHEETAL**.

---

## 1. Primary Evidence-Based Sources

### Reference 1: Horticultural Post-Harvest Loss Assessment
- **Title:** Assessment of Post-Harvest Losses of Perishable Agricultural Produce in India
- **Organization / Authors:** ICAR-Central Institute of Post-Harvest Engineering and Technology (CIPHET) & Ministry of Food Processing Industries (MoFPI)
- **Year:** 2022 Pan-India Assessment
- **Project Support:** Establishes the empirical baseline of 10%–50% post-harvest decay in Indian vegetable chains, specifically documenting a 21.51% cumulative supply-chain loss for tomato.
- **Design Impact:** Validates the urgent requirement for decentralized farm-gate cold storage to halt immediate respiration and fungal rot.

### Reference 2: North Eastern Region Operational Landholdings
- **Title:** Agriculture Census of India 2015–2016: Operational Landholdings in North Eastern States
- **Organization:** Ministry of Agriculture & Farmers Welfare, Government of India
- **Year:** 2016
- **Project Support:** Documents that marginal and small farmers dominate NER agriculture, with an average operational landholding of approximately 0.36 ha in states like Assam.
- **Design Impact:** Explains why centralized 5,000+ metric ton cold stores are economically and logistically inaccessible to smallholders, driving our 200 kg modular farm-gate capacity.

### Reference 3: Postharvest Physiology & Chilling Injury Thresholds
- **Title:** Produce Fact Sheets: Commercial Storage Conditions and Chilling Injury in Fresh Vegetables
- **Organization:** Postharvest Technology Center, University of California, Davis (UC Davis)
- **Project Support:**
  - Tomato (*Solanum lycopersicum*): Light red tomatoes require 10.0°C–12.5°C at 90%–95% RH. Chilling injury (tissue pitting, failure to ripen, fungal susceptibility) occurs below 10.0°C.
  - Cucumber (*Cucumis sativus*): Requires 10.0°C–12.5°C at 90%–95% RH. Rapid chilling injury occurs below 10.0°C.
- **Design Impact:** Directly drives our nominal chamber setpoint of **10.0°C** and the supervisory cooling protection threshold at `< 6°C` to safeguard against irreversible cellular chilling damage.

### Reference 4: Thermal & Thermophysical Food Properties
- **Title:** ASHRAE Handbook — Refrigeration: Chapter 19 (Thermal Properties of Foods)
- **Organization:** American Society of Heating, Refrigerating and Air-Conditioning Engineers (ASHRAE)
- **Project Support:**
  - Specific heat capacity of fresh tomato above freezing: $C_p = 3.99\text{ kJ/(kg}\cdot\text{K)}$.
  - Post-harvest metabolic respiration rate at 10°C: $\approx 15\text{ mW/kg}$ ($\approx 10-15\text{ mg } CO_2/\text{kg}\cdot\text{h}$).
- **Design Impact:** Used directly in the heat load calculations ([`documentation/calculations.md`](../documentation/calculations.md)) for the 4.43 kWh sensible pull-down load and respiration loads.

### Reference 5: Phase Change Material Thermophysical Datasheet
- **Title:** Technical Datasheet: savE® HS10 / IP08 Phase Change Material
- **Organization:** Pluss Advanced Technologies Ltd.
- **Project Support:**
  - Chemistry: Inorganic salt hydrate.
  - Phase transition temperature: Centered at 10.0°C (range 8°C–12°C).
  - Latent heat of fusion: $\approx 180\text{ kJ/kg}$.
  - Non-flammable, non-hazardous formulation.
- **Local Copy:** [`research/IP08_PCM_Datasheet.pdf`](IP08_PCM_Datasheet.pdf)
- **Design Impact:** Establishes the 25 kg PCM sizing delivering 1.25 kWh of latent cold storage to buffer compressor off-cycles without battery depletion.

### Reference 6: Zero-Energy Cool Chamber (ZECC) Field Trials in NER
- **Title:** Evaporative Cooling and Low-Cost Storage Trials for Fresh Vegetables in Mountainous North Eastern States
- **Organization / Authors:** ICAR Research Complex for NEH Region (Nagaland, Manipur, Meghalaya Centres)
- **Project Support:** Documents vegetable shelf-life extension under high-humidity storage in NER field trials:
  - Cucumber (Wokha, Nagaland): 18 days vs 13 days ambient.
  - Tomato (Churachandpur, Manipur): 15 days vs 7 days ambient.
  - Cabbage (Imphal West, Manipur): 10 days vs 4 days ambient.
- **Design Impact:** Confirms that holding high relative humidity (90%–95% RH) alongside moderate temperature depression more than doubles fresh produce marketability.

---

## 2. Design Traceability Flow

Every critical design choice traces directly through research evidence, calculations, and prototype implementation:

```
┌───────────────────────────────┐
│     RESEARCH EVIDENCE         │
│  UC Davis Postharvest Studies │
│  Chilling injury below 10°C   │
└──────────────┬────────────────┘
               │
               ▼
┌───────────────────────────────┐
│    ENGINEERING DECISION       │
│  Moderate Crop Group Baseline │
│  Nominal Setpoint: 10.0°C     │
└──────────────┬────────────────┘
               │
               ▼
┌───────────────────────────────┐
│    THERMAL CALCULATION        │
│  Q = m × Cp × ΔT              │
│  200 kg @ ΔT 20K = 4.43 kWh   │
└──────────────┬────────────────┘
               │
               ▼
┌───────────────────────────────┐
│   PROTOTYPE IMPLEMENTATION    │
│  ESP32 Firm Control Logic:    │
│  Target 6–10°C, Protect <6°C  │
└───────────────────────────────┘
```
