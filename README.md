# Intelligent-CNG-Safety-Monitoring-System
Intelligent CNG Monitoring System using ESP32, BME280, MPU6050, MQ Gas Sensor, GPS, and OLED Display for real-time gas leak detection, temperature monitoring, vibration analysis, and safety status indication.
# Intelligent CNG Monitoring System

## Overview

The Intelligent CNG Monitoring System is an ESP32-based safety monitoring solution designed for CNG-powered vehicles and industrial environments. The system continuously monitors gas leakage, temperature, and vibration levels to detect potential hazards and provide real-time safety alerts.

The project uses multiple sensors and displays the system status on an OLED screen while indicating safety conditions through LED indicators.

## Features

* Real-time CNG gas leak detection
* Temperature monitoring using BME280
* Vibration and impact detection using MPU6050
* GPS data acquisition for location tracking
* OLED display for live system status
* Multi-level safety indication using LEDs
* Serial monitoring for debugging and data logging

## Hardware Components

* ESP32 Development Board
* MQ Gas Sensor
* BME280 Temperature Sensor
* MPU6050 Accelerometer/Gyroscope
* NEO-6M GPS Module
* SSD1306 OLED Display (128x64)
* Red LED (Fault Indicator)
* White LED (Warning Indicator)
* Green LED (Safe Indicator)

## Working Principle

The system continuously collects data from:

### Gas Sensor

Detects the presence of CNG leakage.

### Temperature Sensor (BME280)

Monitors ambient temperature and identifies overheating conditions.

### Vibration Sensor (MPU6050)

Measures sudden vibrations and impacts by comparing current and previous acceleration values.

### GPS Module

Provides real-time location data for tracking and emergency response.

## Safety Levels

### SAFE

* No gas leakage detected
* Temperature within normal range
* No abnormal vibration

**Indicator:** Green LED ON

### WARNING

* Moderate temperature rise or vibration detected

**Indicator:** White LED ON

### FAULT

* Gas leakage detected
* Excessive temperature
* Severe vibration

**Indicator:** Red LED ON

## OLED Display Information

The OLED screen displays:

* System Status
* Temperature Value
* Gas Sensor Status
* Temperature Alert Status
* Vibration Alert Status

## Pin Connections

| Component     | ESP32 Pin |
| ------------- | --------- |
| MQ Gas Sensor | GPIO 34   |
| Red LED       | GPIO 27   |
| White LED     | GPIO 26   |
| Green LED     | GPIO 25   |
| GPS RX        | GPIO 16   |
| GPS TX        | GPIO 17   |
| SDA           | GPIO 21   |
| SCL           | GPIO 22   |

## Software Requirements

* Arduino IDE
* ESP32 Board Package

### Required Libraries

* Wire
* Adafruit BME280
* MPU6050
* Adafruit GFX
* Adafruit SSD1306

## Applications

* CNG Vehicle Safety Monitoring
* Smart Transportation Systems
* Industrial Gas Leakage Detection
* Fleet Safety Management
* Smart Vehicle Health Monitoring

## Future Enhancements

* GSM-based emergency alert system
* Cloud-based IoT monitoring dashboard
* Mobile application integration
* Real-time GPS tracking on maps
* Data logging and analytics

## Author

Sam

### Project Title

**Intelligent CNG Monitoring and Safety Alert System**
