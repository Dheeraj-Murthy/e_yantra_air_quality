# Air Quality Monitoring System Using ESP32

## Overview

This project introduces a scalable air quality monitoring system designed for real-time data collection and user-friendly visualization. The system integrates an **ESP32 microcontroller** with various sensors to monitor environmental parameters such as temperature, humidity, particulate matter, and harmful gases. The collected data is processed and visualized via a web application, providing accessible insights for users to make informed decisions regarding their health and surroundings.

---

## Features

- **Real-Time Monitoring**: Continuous tracking of air quality parameters.
- **Cloud Integration**: Sensor data is uploaded to the ThingSpeak cloud platform.
- **User-Friendly Visualization**: Data is displayed in an intuitive web application with charts and gauges.
- **Low-Cost & Scalable**: Affordable hardware and modular design for scalability.

---

## Hardware Components

### 1. **ESP32 Microcontroller**
- Integrated Wi-Fi and Bluetooth for seamless communication.
- Processes data from connected sensors and transmits it to the cloud.

### 2. **Sensors**
- **DHT11**: Measures temperature and humidity.
- **MQ131**: Detects ozone (O3) and other gases.
- **MQ135**: Measures harmful gases like ammonia, NOx, benzene, smoke, and CO2.
- **GP2Y1010AU0F**: Tracks particulate matter (PM) concentration.

---

## Software Stack

1. **C/C++**: For programming the ESP32 and interfacing with sensors.
2. **ThingSpeak**: Cloud platform for storing and visualizing sensor data.
3. **React.js**: For developing a responsive web application to display air quality metrics.
4. **REST API**: Fetches data from ThingSpeak for visualization.

---

## Data Flow

1. **Data Collection**:
   - Sensors connected to the ESP32 microcontroller capture environmental parameters.
2. **Data Transmission**:
   - ESP32 sends data to the ThingSpeak cloud using the HTTP protocol.
3. **Data Storage**:
   - ThingSpeak stores and visualizes data in real-time.
4. **Web Application**:
   - React-based web application fetches data from ThingSpeak's REST API and displays it in an accessible format.

---

## Setup Instructions

### Hardware Setup
1. Connect the **DHT11**, **MQ131**, **MQ135**, and **GP2Y1010AU0F** sensors to the ESP32 microcontroller.
2. Ensure proper power supply and secure connections for stable operation.

### Software Setup
1. **Arduino IDE**:
   - Install the ESP32 board manager and necessary libraries for the sensors.
   - Upload the firmware to the ESP32.
2. **ThingSpeak**:
   - Create a channel and obtain an API key for data transmission.
3. **Web Application**:
   - Clone the repository and configure the API endpoint to fetch data from ThingSpeak.
   - Run the web application using `npm start`.

---

## Future Enhancements

- **Threshold-Based Alerts**: Notifications for pollutant levels exceeding safe limits.
- **Additional Sensors**: Integration of more sensors for comprehensive monitoring.
- **AI Analytics**: Advanced analysis of trends and predictions using machine learning.

---

## References

1. **ESP32 Documentation**  
   - [ESP32 Technical Reference](https://www.espressif.com/)
2. **DHT11 Sensor**  
   - [DHT11 Datasheet](https://components101.com/)
3. **MQ Sensors**  
   - [MQ135 and MQ131 Specifications](https://components101.com/)

---

