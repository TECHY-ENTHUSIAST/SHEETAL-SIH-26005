# Prototype 3D Concept & Engineering Architecture

This directory contains visual prototype designs, isometric cutaways, and engineering callouts representing the physical architecture of **SHEETAL** (SIH 2026 Problem Statement PS 26005).

---

## 1. Perimeter Wall-Distributed PCM Thermal Jacket Architecture (Enhanced Design)

![SHEETAL Wall-Distributed PCM Render](sheetal_wall_pcm_render.jpg)

### Why Distribute PCM Around the Inner Chamber Walls?
In this enhanced engineering architecture, the Phase Change Material (PCM) is mounted as modular slim-profile cassettes distributed across the **interior perimeter walls (side and rear walls)** rather than being solely concentrated near the ceiling fan plenum:

1. **Boundary Interception of Transmission Heat:**  
   External ambient heat conducting through the 100 mm PUF envelope ($U \cdot A \cdot \Delta T$) encounters the perimeter PCM jacket *first* before reaching the internal storage air or vegetable crates. The melting PCM absorbs this ingress heat at its flat 10.0°C plateau, forming a protective thermal shield.
2. **Massive Heat Transfer Surface Area Expansion ($A$):**  
   Inorganic salt hydrates possess relatively low thermal conductivity ($k \approx 0.5 - 1.0\text{ W/m}\cdot\text{K}$). Distributing the mass into thin, high-aspect-ratio panels along the perimeter walls dramatically increases the effective convective and conductive surface area ($Q = h \cdot A \cdot \Delta T$), increasing both charging and discharging heat transfer rates.
3. **Passive Natural Convection During Power Failure:**  
   When forced circulation fans are off during overnight periods or power outages, the cold perimeter PCM walls induce natural buoyancy-driven convection (cold air sinks along the cooled walls, sweeps across the floor grating, and rises gently through the produce core), eliminating localized hotspots and air stratification.

---

## 2. Overhead Plenum Baseline Architecture (Alternative Configuration)

![SHEETAL Overhead Plenum Render](sheetal_prototype_render.jpg)

*Baseline configuration showing compact horizontal cassette racking directly below the evaporator discharge plenum.*

---

## 3. Subsystem Visual Callouts & Specifications

| Subsystem | Specification | Purpose |
| :--- | :--- | :--- |
| **Heavy-Duty PUF Insulation** | 100 mm rigid Polyurethane Foam ($k \approx 0.023\text{ W/mK}, U \approx 0.23\text{ W/m}^2\text{K}$) | Minimizes parasitic ambient thermal conduction |
| **Heavy-Duty Insulated Door** | Cam-lock compression hinges + dual magnetic rubber gasket | Airtight seal with safety internal emergency release latch |
| **Perimeter PCM Thermal Battery**| Inorganic Salt Hydrate (HS10 / IP08, 10.0°C nominal transition) | Latent cold accumulator buffering off-cycles & night holdover |
| **Produce Storage Crates** | Ventilated food-grade HDPE crates (200 kg batch capacity) | Reference crop: Fresh tomatoes & moderate-temperature vegetables |
| **Evaporator & Twin Fans** | Finned copper coil with twin 12 V DC brushless axial fans | Active heat pumping & forced downward air distribution |
| **ESP32 Controller & OLED** | ESP32-WROOM-32D in IP65 enclosure with 0.96" I²C OLED | Closed-loop temperature tracking, anti-short-cycle & web server |
| **Emergency Stop Switch** | Latching red mushroom safety button | Instant physical disconnect for high-voltage and DC circuits |
| **ESP32-CAM Sensor Node** | OV2640 optical node with UART2 heartbeat link | Crate fill-level and visual inventory monitoring |
| **48V LiFePO4 Battery Pack** | 48 V, 100 Ah (4.80 kWh nominal capacity) | Electrochemical energy buffer for nocturnal & low-irradiance autonomy |
| **MPPT Solar Controller** | 48 V / 50 A Maximum Power Point Tracking | Maximizes PV harvesting efficiency into the 48 V battery bank |
| **Solar PV Array** | 1.65 kWp (3 × 550 W Monocrystalline Half-Cut PERC) | 100% off-grid primary daytime power generation |
