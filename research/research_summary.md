# Regional Research & Technical Summary

This document synthesizes the regional agricultural context, crop physiological constraints, and thermal storage research supporting Problem Statement **PS 26005** for the **Smart India Hackathon 2026**.

---

## 1. Problem Context: The North Eastern Region (NER) Horticultural Crisis

### 1.1 Post-Harvest Losses in NER Supply Chains
Horticulture is a primary driver of rural livelihood across the eight North Eastern states (Arunachal Pradesh, Assam, Manipur, Meghalaya, Mizoram, Nagaland, Sikkim, and Tripura). However, post-harvest losses remain severe:
- Pan-India post-harvest vegetable losses range between **10% and 50%**. For tomato, cumulative supply-chain losses average **21.51%** (ICAR-CIPHET 2022).
- Subtropical ambient temperatures (28°C–35°C during harvest) combined with high ambient humidity cause rapid enzymatic breakdown, water loss (wilting), and fungal decay within 24 to 48 hours of harvest.

### 1.2 The Smallholder Farm-Gate Reality
- **Marginal Landholdings:** According to the Agriculture Census (2015-16), marginal and small farmers represent over 85% of cultivators in the NER, with average landholdings of just **0.36 ha** in Assam.
- **Marketable Daily Surplus:** A single smallholder typically harvests a daily marketable surplus of **10 kg to 25 kg** of vegetables. Centralized 5,000-metric-ton commercial cold storages are physically inaccessible, prohibitively expensive, and located near major urban consumption centers rather than remote farm gates.
- **Aggregation Bottleneck:** Farmers are forced to sell their harvest immediately to local intermediaries at distressed farm-gate rates before evening to prevent total spoilage.

### 1.3 Terrain, Monsoon, and Road Friction
- Mountainous topography and unpaved arterial roads create severe transportation delays. While straight-line distances may be short, transit to district aggregation centers takes **12 to 36 hours**.
- During the heavy monsoon season (June to September), frequent landslides, washed-out bridges, and road blockages regularly extend transit delays to **48 to 72 hours**.
- **Grid Power Deficit:** Rural NER suffers from intermittent power, frequent load shedding, and voltage brownouts, rendering conventional grid-dependent cooling machinery completely non-viable at the village level.

---

## 2. Crop Storage Compatibility & Physiology

A foundational engineering insight from the team's research is that **no single universal cold storage temperature exists for all crops**:

| Crop Category | Example Vegetables | Safe Storage Temperature | Safe Storage RH | Physiological Chilling Sensitivity |
| :--- | :--- | :---: | :---: | :--- |
| **Moderate-Temperature Group (Selected Design Baseline)** | **Tomato, Cucumber, French Beans, Green Chillies** | **8.0°C – 12.0°C** *(Nominal: 10.0°C)* | **90% – 95%** | **Highly Chilling-Sensitive below 8°C–10°C.** Storing at 0°C–4°C causes cell wall collapse, surface pitting, uneven ripening, and watery rot. |
| Low-Temperature Group | Cabbage, Cauliflower, Carrot, Radish | 0.0°C – 2.0°C | 95% – 98% | Non-chilling sensitive. |
| Sub-Tropical Root Group | Ginger, Turmeric, Yam | 12.0°C – 15.0°C | 85% – 90% | Chilling-sensitive below 12°C. |

### Why Tomato was Selected as the Reference Crop:
1. **High Commercial Value:** Widely cultivated across NER valleys and terraces.
2. **Extreme Perishability:** High moisture content (>93%) and high initial respiration rate.
3. **Chilling Sensitivity:** Serves as the critical design boundary: the cooling system must never drop produce below 6°C–8°C while preventing rise above 12°C–13°C.

---

## 3. NER Field Trials on Low-Cost Cold Preservation

Trials conducted by ICAR research centers across the NEH Region utilizing Zero-Energy Cool Chambers (ZECC) demonstrated that maintaining high relative humidity (90%–95% RH) and modest temperature depression significantly extends shelf life:
- **Cucumber (Wokha, Nagaland):** Extended shelf life from 13 days (ambient) to 18 days (cool chamber).
- **Tomato (Churachandpur, Manipur):** Extended shelf life from 7 days (ambient) to 15 days (cool chamber).
- **Cabbage (Imphal West, Manipur):** Extended shelf life from 4 days (ambient) to 10 days (cool chamber).

*Limitation of Evaporative Cooling:* ZECC systems rely on water evaporation, which fails during humid monsoon months when ambient wet-bulb depression approaches zero. This proves that an **active solar-powered refrigeration loop paired with a latent PCM buffer** is required for reliable year-round preservation in the NER.

---

## 4. Phase Change Material (PCM) Thermal Buffering Mechanics

1. **Latent Heat Sponge:** Utilizing 25 kg of inorganic salt hydrate (HS10 / IP08) provides 1.25 kWh of thermal storage at its 10.0°C phase change plateau ($180\text{ kJ/kg}$).
2. **Decoupling Solar Generation from Cooling Demand:** During midday sun, surplus solar PV power drives the compressor to concurrently chill the vegetables and freeze (charge) the PCM.
3. **Nocturnal & Monsoon Holdover:** When solar power drops or the compressor switches off, the PCM melts slowly, absorbing envelope heat leakage and maintaining chamber temperatures between 8°C and 12°C without cycling the compressor or draining the LiFePO4 battery bank.

---

## 5. Explicit Limitations: What Research Does NOT Establish

While published literature and datasheets validate our design methodology:
- They **do not prove** the empirical holding duration of the SHEETAL prototype chamber.
- Physical holdover duration, spatial airflow uniformity, actual COP, and solar autonomous runtime must be verified through physical test protocols ([`testing/testing_notes.md`](../testing/testing_notes.md)).
- These parameters remain classified as **Engineering Calculations** and **Design Targets** until physical test logs are populated.
