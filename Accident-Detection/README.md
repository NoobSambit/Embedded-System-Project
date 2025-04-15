# Accident Detection and Alert System

🚨 An embedded system project that detects vehicle accidents using an ADXL335 accelerometer and sends the GPS location via GSM module to a predefined number.

---

## 🧠 Overview
This system helps automate emergency alerts by sending the real-time location when an accident-like shock is detected.

---

## 💡 Components Used:
- Arduino Nano
- ADXL335 Accelerometer
- SIM800L GSM Module
- NEO-6M GPS Module
- LCD 16x2 with I2C
- Buzzer
- Push Button
- Power Supply

---

## ⚙️ Working Principle:
1. The accelerometer continuously monitors vibration and motion.
2. When an abnormal jerk (above threshold) is detected, the system:
   - Triggers a buzzer.
   - Reads GPS coordinates.
   - Sends an SMS with a Google Maps link via the GSM module.
3. Manual reset is possible via the push button.

---

## 💾 Files Included:
- `accident_detection.ino` — Arduino source code.
- `circuit_diagram.png` — Schematic diagram.
- `components_list.txt` — List of required hardware.

---

## 📌 Note:
The GPS and GSM modules must be configured properly, and the SIM card should be active and capable of sending SMS.

