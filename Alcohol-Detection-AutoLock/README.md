# Alcohol Detection & Auto-Lock System 🚗🔒

This project is designed to prevent drunk driving accidents by detecting alcohol presence and automatically locking the vehicle's ignition system.

## 💡 Overview
Using an MQ-3 gas sensor, this system continuously monitors the driver's breath for alcohol. If alcohol is detected above the safe threshold, the ignition system is disabled and an alert is displayed on the LCD, accompanied by a buzzer.

## 🛠️ Components Used
- Arduino Uno
- MQ-3 Alcohol Sensor
- DC Motor (acts as ignition)
- 5V Relay Module
- 16x2 LCD Display (I2C)
- Buzzer
- Switch (for manual reset)
- Breadboard & Jumper Wires

## ⚙️ Working Principle
1. The MQ-3 sensor detects alcohol vapor concentration.
2. If the level crosses the safety limit, the microcontroller:
   - Activates a buzzer.
   - Displays "Alcohol Detected" on the LCD.
   - Triggers the relay to cut off the ignition (represented by a motor in this project).
3. Once alcohol is no longer detected and the system is manually reset, the ignition is re-enabled.

## 🎥 Demo Video
[Click here to view the demo](#)  
(*Replace this link with your real video link!*)  

## 🖼️ Circuit Diagram
![Circuit Diagram](./Circuit_Diagram.png)

## 📸 Real Setup
You can check the `Images/` folder for actual hardware photos.

---

✅ **Note:**  
This is a prototype for educational purposes and can be extended to real vehicles with appropriate safety compliance and certification.

