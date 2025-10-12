
Smart Home package for Raspberry Pi (Raspbian) and Yocto-built Pi
================================================================

Contents:
- smart_home_pi.py       -> Python script (reads Arduino serial, publishes MQTT, controls LEDs)
- arduino_sensors.ino    -> Arduino UNO sketch (LM35 + LDR)
- node-red-flow.json     -> Node-RED importable flow (dashboard)
- README.txt             -> This file

SUMMARY QUICK START (Raspberry Pi OS)
------------------------------------
1) Update & install packages:
   sudo apt update && sudo apt upgrade -y
   sudo apt install python3-pip python3-serial python3-rpi.gpio mosquitto mosquitto-clients nodejs npm -y
   sudo npm install -g --unsafe-perm node-red
   pip3 install paho-mqtt pyserial RPi.GPIO

2) Connect Arduino UNO to Raspberry Pi via USB. Verify serial port:
   ls /dev/ttyACM*    # typically /dev/ttyACM0

3) Flash Arduino using Arduino IDE with arduino_sensors.ino

4) Copy files to Pi and run:
   python3 smart_home_pi.py &
   node-red-start &
   sudo systemctl start mosquitto

5) Open Node-RED on your laptop or Pi browser:
   http://<pi-ip>:1880
   Import node-red-flow.json into Node-RED (menu -> Import -> Clipboard)

6) Start mjpg-streamer (or raspivid->ffmpeg) if you want camera stream:
   sudo apt install mjpg-streamer -y
   # or use raspivid + ffmpeg

7) Make smart_home_pi.py start at boot (systemd) - example services in README.

YOCTO QUICK NOTES
-----------------
- Yocto images are minimal. You can avoid adding layers by installing Node.js and Node-RED manually.
- Copy the files to the device via scp or USB.
- Install Node.js manually (download binary), install npm, then npm install -g node-red
- Install mosquitto (if package manager available) or run mosquitto from a binary.
- Ensure /dev/ttyACM0 serial device is accessible and Python has pip3 (may need to install pip manually).

SYSTEMD SERVICE EXAMPLE (to auto start Python & Node-RED & mjpg-streamer)
-------------------------------------------------------------------------
Create /etc/systemd/system/smart_home.service:
[Unit]
Description=Smart Home Python Service
After=network.target mosquitto.service

[Service]
ExecStart=/usr/bin/python3 /home/pi/smart_home_pi.py
Restart=always
User=pi
Group=pi
Environment=PYTHONUNBUFFERED=1

[Install]
WantedBy=multi-user.target

# enable:
sudo systemctl daemon-reload
sudo systemctl enable smart_home.service
sudo systemctl start smart_home.service

TROUBLESHOOTING
-------------
- If serial fails, check dmesg and permissions. Add pi user to dialout group:
  sudo usermod -a -G dialout pi
- If GPIO permission issues: run script as root or use sudo for systemd service.
- If Node-RED can't connect to MQTT, verify mosquitto is running: sudo systemctl status mosquitto
