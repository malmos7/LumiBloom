# LumiBloom: Motion-Sensing Decorative Blooming Light

## Overview
**LumiBloom** is an interactive decorative lighting system that **blooms and illuminates** in response to **motion** and **ambient light conditions**. Designed to merge aesthetics and embedded control, it uses a mechanical flower mechanism driven by a servo motor and ambient LED lighting that activates only when motion is detected **in low-light environments**.

When the room is dark and movement is detected, the flower gracefully blooms and its LEDs emit a soft glow. After a set period without motion, LumiBloom closes its petals (“unblooms”) and the lights fade off — creating a balance of **beauty, efficiency, and responsiveness**.

---

##  Key Features
-  **Ambient Light Detection** – Uses an LDR sensor to measure light intensity and only activates in dark conditions.
-  **Motion Sensing** – Detects nearby movement using a PIR sensor to trigger the blooming sequence.
-  **Mechanical Blooming** – A servo-controlled mechanism smoothly opens and closes the petals.
-  **Decorative LED Lighting** – Soft lighting controlled by the microcontroller adds aesthetic ambiance.
-  **FSM Control Logic** – Finite State Machine (FSM) design ensures stable transitions between states: *Idle → Bloomed → Dim → Closed*.
-  **Custom PCB** – Designed in **Altium Designer** for compact, reliable hardware integration.
-  **Microcontroller-Based** – Built around the **ATmega328** platform for easy prototyping and embedded control.

---

##  Hardware Components

 - ATmega328 Microcontroller:  Main control unit 
 - PIR Motion Sensor: Detects nearby movement 
 - LDR Module: Measures ambient light 
 - Servo Motor: Controls blooming mechanism
 - Decorative LEDs (fairy lights): Provide ambient lighting 
 - 9V battarey connected to  5V voltagr regulator: Drives servo and logic
 - PDN Resistors for fairy lights and reset buttons
 - Decoupling Capacitor
 - Custom PCB for Compact circuit layout and interconnection 

---

## System Design

### 1. Control Logic
Implemented using a finite state machine (FSM) that transitions between states based on light and motion sensor readings.

### 2. Circuit Design
The schematic and PCB layout were designed in **Altium Designer**, with separate control and power sections for reliability.

### 3. Firmware
Developed in **C** and programmed using **Atmel Studio / Arduino IDE**, leveraging timers and interrupts for precise servo control and timing sequences.

---

## How It Works
1. **Idle Mode:** When no motion is detected or ambient light is sufficient, the flower remains closed and LEDs stay off.
2. **Activation:** When motion is detected and ambient light is below a threshold, the microcontroller triggers the servo to rotate and open the petals.
3. **Lighting:** LEDs turn on with a gradual fade effect for soft illumination.
4. **Timeout:** After a preset duration of inactivity, the system closes the petals and turns off LEDs to save power.

---

## Project Structure

```
LumiBloom/
│
├── /lumiBloom.ino/                         # Arduino source code for ATmega328
├── /Project Outputs for lumiBloom/         # Altium schematic and PCB layout files
├── /Images/                                # Photos, renders, or demonstration GIFs
└── README.md            # Project documentation (this file)
```

---

##  Lessons & Design Insights
- Integrated **FSM design** ensures robust and predictable behavior.
- Considerations for **low-power operation** and **sensor hysteresis** improve performance.
- Combining **aesthetic mechanics** with **embedded logic** demonstrates interdisciplinary design between EE and product design.

---

## Potential Future Improvements
- Add **Bluetooth / IoT connectivity** for remote control.
- Design a **3D-printed enclosure** for compact assembly and aesthetic presentation.
- Explore **multi-flower configurations** with synchronized blooming.

---

##  Author
**Mal Mostafa**  
Department of Electrical & Computer Engineering  
University of Pittsburgh  

> Designed, implemented, and documented as part of *Junior Design Fundamentals (ECE 1895)*
