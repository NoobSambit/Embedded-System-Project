# Embedded System Projects 🚗🔧

This repository contains two Arduino-based embedded system projects focused on safety and automation.

---

## 📌 Project 1: Alcohol Detection & Auto-Locking System

### 🎯 Objective  
Prevent drunk driving by detecting alcohol concentration and automatically locking the vehicle’s ignition system.

### ⚡ Components
- Arduino Uno  
- MQ-3 Alcohol Sensor  
- DC Motor + Relay Module (Engine Lock)  
- Buzzer  
- LCD Display  

### 💡 Working  
- The MQ-3 sensor detects alcohol in the driver’s breath.
- If the alcohol level exceeds a predefined limit, the system:
  - Locks the engine using a relay.
  - Sounds an alert via a buzzer.
  - Displays the status on the LCD.

---

## 📌 Project 2: Accident Detection & Alert System

### 🎯 Objective  
Detect vehicle accidents and send the real-time GPS coordinates via SMS to emergency contacts.

### ⚡ Components
- Arduino Nano  
- ADXL335 Accelerometer  
- SIM800L GSM Module  
- NEO-6M GPS Module  
- LCD Display  
- Buzzer  

### 💡 Working  
- The accelerometer continuously monitors motion and detects sudden shocks.
- On accident detection:
  - The system fetches GPS coordinates.
  - Sends an SMS with the Google Maps location using the SIM800L module.
  - Displays the accident status and coordinates on the LCD.

---

## 📋 Note  
These projects were created for academic learning and classroom demonstration purposes, tested using real hardware components with Arduino IDE.

