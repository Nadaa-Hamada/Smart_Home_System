# Smart_Home_System
# Smart_Home_Dashboard
Smart home dashboard for real-time monitoring and control of devices using IoT and embedded systems, integrating GPIO hardware and an interactive dashboard interface.

#  Qt Smart Home System

A **Smart Home Dashboard** built using **Qt and Arduino**, designed to monitor environmental data and control home devices in real time.  
This project demonstrates seamless integration between **software (Qt GUI and yocto image)** and **hardware (Arduino sensors and actuators)**, providing a complete IoT-based home automation solution.

---

## Features

- 🌡️ **Temperature Monitoring** – Displays live temperature readings.  
- 💡 **Light Detection** – Shows current light intensity using an LDR sensor.  
- 🚶 **Motion Detection** – Detects human movement using a PIR sensor.  
- 🔘 **LED Control** – Turn LEDs on/off directly from the Qt interface.  
- 📷 **Live Camera Stream** – Real-time video feed using MJPEG streaming.  
- 🔁 **Real-Time Serial Communication** – Continuous data exchange between Qt and Arduino.

---

## System Structure

### 🔹 Data Flow
1. **User** launches the Qt application.  
2. **Qt App** requests sensor readings from Arduino via serial communication.  
3. **Arduino** sends temperature, light, and motion data back.  
4. **Qt UI** updates labels in real time.  
5. When the **user toggles LED**, Qt sends a control command to Arduino.  
6. **Arduino** activates or deactivates the LED.  
7. **Camera** sends MJPEG video frames to Qt through a custom `MjpegReceiver` class.  

---

### 🔹 Class Structure Overview

#### 🧩 MainWindow
- Manages the overall UI and communication.
- **Attributes:**  
  `MjpegReceiver*`, `QSerialPort*`, `QLabel*` for sensors and camera, `QPushButton*` for LED controls.  
- **Methods:**  
  - `onSerialData()` → handles data from Arduino  
  - `updateUI()` → refreshes displayed readings  
  - `toggleLed(int)` → sends LED control commands  
  - `onCameraFrame()` → updates the live video feed  

####  MjpegReceiver
- Handles camera connection and frame updates.
- Uses `QNetworkAccessManager` and `QTimer`.
- Emits `newFrame()` signal to update the GUI.

####  ArduinoDevice
- Reads sensor data and controls actuators.
- Communicates with the Qt app via **Serial**.
- **Sensors:** Temperature, LDR, PIR  
- **Actuators:** LED1, LED2  
- Functions: `readSensors()`, `sendData()`

---

## 🛠️ Hardware Components

- Arduino Uno  
- DHT11 Temperature Sensor  
- LDR Sensor  
- PIR Motion Sensor  
- LEDs  
- USB Camera or Raspberry Pi Camera  

---

##  Software Stack

- **Qt (C++)** – GUI and application logic  
- **Arduino IDE (C/C++)** – Firmware and sensor control  
- **Serial Communication** – Data exchange between Arduino and Qt  
- **MJPEG Stream** – Real-time camera streaming  

---

## 📸 System Preview

| Component | Description |
|------------|-------------|
| **Dashboard** | Displays sensor data and camera feed |
| **Control Buttons** | Turn on/off LEDs |
| **Live Stream** | Updates via MJPEG receiver |

---

## ⚙️ How to Run

### 1. Arduino Setup
- Upload the Arduino code that reads sensors and listens for serial commands.
- Connect sensors and LEDs as per the circuit diagram.

### 2. Qt Setup
- Open the Qt project in **Qt Creator**.
- Configure the **serial port name** to match your Arduino connection.
- Run the project — the dashboard should appear with live data and camera stream.

---

## 📂 Folder Structure

```

Qt_Smart_Home/
│
├── arduino/
│   ├── smart_home.ino
│   └── sensors/
│
├── qt_app/
│   ├── mainwindow.cpp
│   ├── mjpegreceiver.cpp
│   ├── arduino_device.cpp
│   └── ui/
│
└── README.md

```
Installation
# Clone the repository
git clone https://github.com/your-username/Smart_Home_Dashboard.git

# Navigate into the project
cd Smart_Home_Dashboard

# Install dependencies (if using Node-RED)
npm install node-red-dashboard

Example GPIO Setup (Linux)

# Export GPIO pin
echo 17 > /sys/class/gpio/export

# Set direction (in/out)
echo out > /sys/class/gpio/gpio17/direction

# Turn ON device
echo 1 > /sys/class/gpio/gpio17/value

# Turn OFF device
echo 0 > /sys/class/gpio/gpio17/value

---

**📸 Dashboard Preview**

**------------------------------------------------------QT dashboard:-----------------------------------------------------------------------------**

<img width="1366" height="768" alt="splash" src="https://github.com/user-attachments/assets/32c1877f-d686-46ae-9d96-546cc8d8ce75" />



<img width="1366" height="768" alt="QT_dashboard" src="https://github.com/user-attachments/assets/f85efeaf-17c3-49ae-bf4b-8a2ecda17b42" />

**----------------------------------------------------Node-red dashboard:------------------------------------------------------------------------**


<img width="719" height="516" alt="ldr+temp" src="https://github.com/user-attachments/assets/ead42014-b2c3-4bc5-880f-aacceecb071f" />


<img width="719" height="516" alt="image" src="https://github.com/user-attachments/assets/f587856f-61d4-4fc6-8d00-3136cada30c1" />

**----------------------------------------------------Twillio Whatsapp Alerts------------------------------------------------------------------**

Twillio msgs to send Alerts to whatsapp about any emergency Alerts in system and integrate with Node-red:

<img width="716" height="607" alt="twillio-msgs" src="https://github.com/user-attachments/assets/e537db84-cfa0-4b0d-bd10-da4d6c5c671d" />

<img width="716" height="607" alt="twillio-msgs2" src="https://github.com/user-attachments/assets/dc0ff5bd-8895-4111-b61c-105ee9891bef" />




**Final Project : include(QT Dashboard & HW & yocto)**

 **---------------------------------HW Integration--------------------------------------**
 
![Hw integration](https://github.com/user-attachments/assets/93407c60-274f-4555-8048-6577a40df335)


 **----------------------------QT Dashboard with HW---------------------------------------**

 
 ![QTREal1](https://github.com/user-attachments/assets/3f2aff1b-ea14-4555-84c5-b478b4cc6cb3)


 ![QTREal2](https://github.com/user-attachments/assets/dc0dd1e6-8648-4559-842c-ecd38db1b58b)



## ✨ Future Improvements
- Add cloud connectivity (Firebase / MQTT).  
- Implement mobile app control using Flutter.  
- Integrate voice commands (e.g., Google Assistant).  
- Store sensor data in a database for analytics.

---

## 👩‍💻 Authors
**Nada Hamada** -
**Nedaa Ahmed** -
**Fatma Waleed** .
---

## 📜 License
This project is licensed under the **MIT License** – feel free to use and modify for educational purposes.

