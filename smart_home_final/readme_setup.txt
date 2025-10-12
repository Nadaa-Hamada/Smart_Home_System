Smart Home Final Package - Quick Setup Guide
============================================

Files included:
- smart_home_pi.py
- mqtt_simulator_arduino.ino
- node-red-flow.json
- start_all.sh
- smart_home.service
- mjpg-streamer.service
- node-red.service

1) Copy files to Raspberry Pi (Raspbian) or Yocto device (scp or USB).

2) Raspberry Pi OS installation (recommended):
   sudo apt update && sudo apt upgrade -y
   sudo apt install -y python3-pip python3-serial python3-rpi.gpio mosquitto mosquitto-clients nodejs npm
   sudo npm install -g --unsafe-perm node-red
   pip3 install paho-mqtt pyserial RPi.GPIO
   # optional for camera:
   sudo apt install -y mjpg-streamer

3) Flash Uno with mqtt_simulator_arduino.ino using Arduino IDE (LM35 -> A1, LDR -> A0).

4) Make start_all.sh executable:
   chmod +x start_all.sh
   ./start_all.sh

5) Import Node-RED flow:
   - Open Node-RED at http://<pi-ip>:1880
   - Menu -> Import -> Clipboard -> paste contents of node-red-flow.json

6) To enable services at boot (Raspbian):
   sudo cp smart_home.service /etc/systemd/system/
   sudo cp mjpg-streamer.service /etc/systemd/system/
   sudo cp node-red.service /etc/systemd/system/
   sudo systemctl daemon-reload
   sudo systemctl enable smart_home.service mjpg-streamer.service node-red.service
   sudo systemctl start smart_home.service mjpg-streamer.service node-red.service

7) Yocto notes:
   - If pip3 or package manager missing, install Python packages manually or bundle.
   - To install Node.js on Yocto without layers, download prebuilt binary and copy to /usr/local.
   - Ensure /dev/ttyACM0 is available and user has dialout group permission: sudo usermod -a -G dialout pi

8) Troubleshooting:
   - If Arduino serial not found: run dmesg | tail after plugging in.
   - If MQTT connection fails, verify mosquitto status: sudo systemctl status mosquitto
   - If camera not streaming, test mjpg_streamer manually and check device listing (v4l2).

9) Motion Notification feature:
   - When motion MQTT topic publishes a truthy value (1 or 'ON'), the Node-RED dashboard will show a toast notification: "Motion detected!" at top-right for 4s.
