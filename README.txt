First:
1-for node-red :-
run node-red on your pc
, then open https//localhost:1880
to see UI (https//localhost:1880/ui)

this is locally.


to see whatsapp Alerts

1- open ngrok http 1880
take URL ------->but it in browser to give you a public IP .
then in twillio whatsapp when motion detect it will send to you an alerts 
and give you menu about things he can help you in it ...


2- to open camera stream 

cd mjpg-streamer/mjpg-streamer-experimental
Run the camera stream:
./mjpg_streamer -i "input_uvc.so -d /dev/video0 -r 640x480 -f 10" \
                -o "output_http.so -p 8081 -w ./www"


Now open your browser at:

http://localhost:8081/?action=stream


3- open code in vscode  --->python3 simulate_sensors.py  
then you can see value in node-red UI and see also camera stream after you run it.


--------to make twillio whatsapp alerts ----------------
watch this video:
(https://youtu.be/2ikC7a-I41I?si=u2pq8SqCuBNf8yzL)

and take codes from github on this link:
(Code Snippets:-

Send twilio alerts - Function(Function10) node code - http://gist.github.com/Hariharnath-Pa...

Receive and respond function(function11) node code - https://gist.github.com/Hariharnath-P...

Respond to messages function(Function 12 to 16) - https://gist.github.com/Hariharnath-P...

Enrol in IoT Course: https://www.udemy.com/course/iot-for-... )


-----------------------------------------------------

code you can import it in node-red to make smart home dashboard:

from menu-->import-->copy and paste -->then deploy


[
    {
        "id": "flow-smart-home",
        "type": "tab",
        "label": "Panther Smart Home",
        "disabled": false,
        "info": ""
    },
    {
        "id": "mqtt-local",
        "type": "mqtt-broker",
        "name": "Local MQTT",
        "broker": "localhost",
        "port": "1883",
        "clientid": "nodered",
        "usetls": false,
        "keepalive": "60",
        "cleansession": true
    },
    {
        "id": "ui_tab_smart",
        "type": "ui_tab",
        "name": "Smart Home",
        "icon": "dashboard",
        "disabled": false,
        "hidden": false
    },
    {
        "id": "ui_group_home",
        "type": "ui_group",
        "name": "Home Dashboard",
        "tab": "ui_tab_smart",
        "order": 1,
        "disp": true,
        "width": 12,
        "collapse": false
    },
    {
        "id": "status_bar",
        "type": "ui_template",
        "group": "ui_group_home",
        "name": "Status Bar",
        "order": 0,
        "width": 12,
        "height": 1,
        "format": "<style>#status-bar{position:fixed;top:0;left:0;width:100%;background:#121212;color:#00ffff;text-align:center;padding:5px;font-family:Arial;font-size:14px;z-index:9999;border-radius:0 0 10px 10px;}</style><div id=\"status-bar\"><span id=\"date-time\"></span> | Motion: <span id='motion-status'>No</span></div><script>function updateTime(){var now=new Date();var day=now.toLocaleString('ar-EG',{weekday:'long'});var date=now.getDate();var month=now.toLocaleString('ar-EG',{month:'long'});var year=now.getFullYear();var hours=now.getHours().toString().padStart(2,'0');var minutes=now.getMinutes().toString().padStart(2,'0');var seconds=now.getSeconds().toString().padStart(2,'0');document.getElementById('date-time').textContent=`${day}، ${date} ${month} ${year} | ${hours}:${minutes}:${seconds}`;} setInterval(updateTime,1000);updateTime();</script>"
    },
    {
        "id": "mqtt-temp",
        "type": "mqtt in",
        "z": "flow-smart-home",
        "name": "Temperature Sensor",
        "topic": "home/sensors/temperature",
        "broker": "mqtt-local",
        "x": 160,
        "y": 100,
        "wires": [["ui_temp","ui_chart_temp","function-auto-temp"]]
    },
    {
        "id": "mqtt-motion",
        "type": "mqtt in",
        "z": "flow-smart-home",
        "name": "Motion Sensor",
        "topic": "home/sensors/motion",
        "broker": "mqtt-local",
        "x": 160,
        "y": 160,
        "wires": [["function-motion","function-auto-light"]]
    },
    {
        "id": "mqtt-ldr",
        "type": "mqtt in",
        "z": "flow-smart-home",
        "name": "LDR Sensor",
        "topic": "home/sensors/ldr",
        "broker": "mqtt-local",
        "x": 160,
        "y": 220,
        "wires": [["ui_chart_ldr","function-auto-light"]]
    },
    {
        "id": "ui_temp",
        "type": "ui_gauge",
        "z": "flow-smart-home",
        "name": "Temperature",
        "group": "ui_group_home",
        "order": 1,
        "title": "Temperature (°C)",
        "label": "°C",
        "format": "{{value}}",
        "min": 0,
        "max": "50",
        "colors":["#2196F3","#00BCD4","#03A9F4"],
        "width": 4,
        "height": 4,
        "x": 430,
        "y": 100,
        "wires": []
    },
    {
        "id": "ui_chart_temp",
        "type": "ui_chart",
        "z": "flow-smart-home",
        "name": "Temperature Chart",
        "group": "ui_group_home",
        "order": 2,
        "label": "Temperature",
        "chartType": "line",
        "legend": "true",
        "xformat": "HH:mm:ss",
        "interpolate": "linear",
        "nodata": "",
        "dot": false,
        "ymin": "0",
        "ymax": "50",
        "removeOlder": "1",
        "removeOlderPoints": "100",
        "removeOlderUnit": "3600",
        "useOneColor": false,
        "colors": ["#00BCD4"],
        "outputs": 1,
        "width": 6,
        "height": 3,
        "x": 430,
        "y": 160,
        "wires": []
    },
    {
        "id": "ui_chart_ldr",
        "type": "ui_chart",
        "z": "flow-smart-home",
        "name": "LDR Chart",
        "group": "ui_group_home",
        "order": 3,
        "label": "Light Intensity",
        "chartType": "line",
        "legend": "true",
        "xformat": "HH:mm:ss",
        "interpolate": "linear",
        "nodata": "",
        "dot": false,
        "ymin": "0",
        "ymax": "100",
        "removeOlder": "1",
        "removeOlderPoints": "100",
        "removeOlderUnit": "3600",
        "useOneColor": false,
        "colors": ["#FFEB3B"],
        "outputs": 1,
        "width": 6,
        "height": 3,
        "x": 430,
        "y": 240,
        "wires": []
    },
    {
        "id": "function-motion",
        "type": "function",
        "z": "flow-smart-home",
        "name": "Motion Logic",
        "func": "let motion = (msg.payload == 1 || msg.payload == 'ON') ? 1 : 0;\nflow.set('motion', motion);\nlet statusText = motion ? 'Yes' : 'No';\ndocument.getElementById('motion-status') && (document.getElementById('motion-status').textContent = statusText);\nif(motion){node.status({fill:'red',shape:'dot',text:'Motion detected'});return [{payload:'ON'}];}else{node.status({fill:'green',shape:'ring',text:'No motion'});return [{payload:'OFF'}];}",
        "outputs": 1,
        "x": 430,
        "y": 200,
        "wires": [["mqtt-led1"]]
    },
    {
        "id": "function-auto-light",
        "type": "function",
        "z": "flow-smart-home",
        "name": "Auto Light Logic (LDR + Motion)",
        "func": "let ldr=Number(msg.payload);\nlet threshold=40;\nflow.set('ldr',ldr);\nlet motion=flow.get('motion')||0;\nif(ldr<threshold && motion===1){node.status({fill:'yellow',shape:'dot',text:'Dark + Motion: Lights ON'});return [{payload:'ON'}];}else if(ldr>threshold){node.status({fill:'green',shape:'ring',text:'Bright: Lights OFF'});return [{payload:'OFF'}];}else{return [null];}",
        "outputs": 1,
        "x": 460,
        "y": 280,
        "wires": [["mqtt-led2"]]
    },
    {
        "id": "function-auto-temp",
        "type": "function",
        "z": "flow-smart-home",
        "name": "Auto Temp Logic (Cooling)",
        "func": "let temp=Number(msg.payload);\nif(temp>30){node.status({fill:'red',shape:'dot',text:'High Temp: Fan ON'});return [{payload:'ON'}];}else if(temp<25){node.status({fill:'blue',shape:'ring',text:'Normal Temp: Fan OFF'});return [{payload:'OFF'}];}else{return [null];}",
        "outputs": 1,
        "x": 460,
        "y": 340,
        "wires": [["mqtt-led3"]]
    },
    {
        "id": "ui_camera",
        "type": "ui_template",
        "z": "flow-smart-home",
        "group": "ui_group_home",
        "name": "Camera Stream",
        "order": 4,
        "width": 12,
        "height": 4,
        "format": "<div style='background:#222;border-radius:10px;padding:10px;text-align:center;'>\n  <iframe src='http://localhost:8081/?action=stream' width='100%' height='300px' style='border-radius:10px;'></iframe>\n</div>"
    },
    {
        "id": "ui_led_panel",
        "type": "ui_template",
        "group": "ui_group_home",
        "name": "LED Buttons",
        "order": 5,
        "width": 12,
        "height": 3,
        "format": "<div style='display:flex;justify-content:space-around;flex-wrap:wrap;background:#222;padding:15px;border-radius:10px;'>\n  <div style='text-align:center;margin:5px;'>\n    <button ng-click='send({payload:\"LED1_ON\"})' style='padding:10px 20px;background:#00bfa5;color:white;border:none;border-radius:8px;margin-bottom:5px;'>LED 1 ON</button><br>\n    <button ng-click='send({payload:\"LED1_OFF\"})' style='padding:10px 20px;background:#B0B0B0;color:black;border:none;border-radius:8px;'>LED 1 OFF</button>\n  </div>\n  <div style='text-align:center;margin:5px;'>\n    <button ng-click='send({payload:\"LED2_ON\"})' style='padding:10px 20px;background:#00bfa5;color:white;border:none;border-radius:8px;margin-bottom:5px;'>LED 2 ON</button><br>\n    <button ng-click='send({payload:\"LED2_OFF\"})' style='padding:10px 20px;background:#B0B0B0;color:black;border:none;border-radius:8px;'>LED 2 OFF</button>\n  </div>\n  <div style='text-align:center;margin:5px;'>\n    <button ng-click='send({payload:\"LED3_ON\"})' style='padding:10px 20px;background:#00bfa5;color:white;border:none;border-radius:8px;margin-bottom:5px;'>LED 3 ON</button><br>\n    <button ng-click='send({payload:\"LED3_OFF\"})' style='padding:10px 20px;background:#B0B0B0;color:black;border:none;border-radius:8px;'>LED 3 OFF</button>\n  </div>\n  <div style='text-align:center;margin:5px;'>\n    <button ng-click='send({payload:\"LED4_ON\"})' style='padding:10px 20px;background:#00bfa5;color:white;border:none;border-radius:8px;margin-bottom:5px;'>LED 4 ON</button><br>\n    <button ng-click='send({payload:\"LED4_OFF\"})' style='padding:10px 20px;background:#B0B0B0;color:black;border:none;border-radius:8px;'>LED 4 OFF</button>\n  </div>\n</div>",
        "x": 460,
        "y": 500,
        "wires": [["mqtt-led1","mqtt-led2","mqtt-led3","mqtt-led4"]]
    },
    {
        "id": "mqtt-led1",
        "type": "mqtt out",
        "z": "flow-smart-home",
        "name": "LED 1 (Motion)",
        "topic": "home/lights/led1",
        "broker": "mqtt-local"
    },
    {
        "id": "mqtt-led2",
        "type": "mqtt out",
        "z": "flow-smart-home",
        "name": "LED 2 (LDR)",
        "topic": "home/lights/led2",
        "broker": "mqtt-local"
    },
    {
        "id": "mqtt-led3",
        "type": "mqtt out",
        "z": "flow-smart-home",
        "name": "LED 3 (Temp)",
        "topic": "home/lights/led3",
        "broker": "mqtt-local"
    },
    {
        "id": "mqtt-led4",
        "type": "mqtt out",
        "z": "flow-smart-home",
        "name": "LED 4 (Manual)",
        "topic": "home/lights/led4",
        "broker": "mqtt-local"
    }
]

.......................................................................

تمام يا ندى 😍، هعدل لك **الـJSON كامل** على الأساس اللي بعته، مع إضافة **Gauge للـLDR** بجانب الـChart، وربط كل حاجة مع الـMQTT بشكل مباشر. إليك النسخة النهائية الجاهزة للاستيراد في Node-RED:

```json
[
    {
        "id": "flow-smart-home",
        "type": "tab",
        "label": "Panther Smart Home",
        "disabled": false,
        "info": ""
    },
    {
        "id": "mqtt-local",
        "type": "mqtt-broker",
        "name": "Local MQTT",
        "broker": "localhost",
        "port": "1883",
        "clientid": "nodered",
        "usetls": false,
        "keepalive": "60",
        "cleansession": true
    },
    {
        "id": "ui_tab_smart",
        "type": "ui_tab",
        "name": "Smart Home",
        "icon": "dashboard",
        "disabled": false,
        "hidden": false
    },
    {
        "id": "ui_group_home",
        "type": "ui_group",
        "name": "Home Dashboard",
        "tab": "ui_tab_smart",
        "order": 1,
        "disp": true,
        "width": 12,
        "collapse": false
    },
    {
        "id": "status_bar",
        "type": "ui_template",
        "group": "ui_group_home",
        "name": "Status Bar",
        "order": 0,
        "width": 12,
        "height": 1,
        "format": "<style>#status-bar{position:fixed;top:0;left:0;width:100%;background:#121212;color:#00ffff;text-align:center;padding:5px;font-family:Arial;font-size:14px;z-index:9999;border-radius:0 0 10px 10px;}</style><div id=\"status-bar\"><span id=\"date-time\"></span> | Motion: <span id='motion-status'>No</span></div><script>function updateTime(){var now=new Date();var day=now.toLocaleString('ar-EG',{weekday:'long'});var date=now.getDate();var month=now.toLocaleString('ar-EG',{month:'long'});var year=now.getFullYear();var hours=now.getHours().toString().padStart(2,'0');var minutes=now.getMinutes().toString().padStart(2,'0');var seconds=now.getSeconds().toString().padStart(2,'0');document.getElementById('date-time').textContent=`${day}، ${date} ${month} ${year} | ${hours}:${minutes}:${seconds}`;} setInterval(updateTime,1000);updateTime();</script>"
    },
    {
        "id": "mqtt-temp",
        "type": "mqtt in",
        "z": "flow-smart-home",
        "name": "Temperature Sensor",
        "topic": "home/sensors/temperature",
        "broker": "mqtt-local",
        "x": 160,
        "y": 100,
        "wires": [["ui_temp","ui_chart_temp","function-auto-temp"]]
    },
    {
        "id": "mqtt-motion",
        "type": "mqtt in",
        "z": "flow-smart-home",
        "name": "Motion Sensor",
        "topic": "home/sensors/motion",
        "broker": "mqtt-local",
        "x": 160,
        "y": 160,
        "wires": [["function-motion","function-auto-light"]]
    },
    {
        "id": "mqtt-ldr",
        "type": "mqtt in",
        "z": "flow-smart-home",
        "name": "LDR Sensor",
        "topic": "home/sensors/ldr",
        "broker": "mqtt-local",
        "x": 160,
        "y": 220,
        "wires": [["ui_chart_ldr","ui_ldr_gauge","function-auto-light"]]
    },
    {
        "id": "ui_temp",
        "type": "ui_gauge",
        "z": "flow-smart-home",
        "name": "Temperature",
        "group": "ui_group_home",
        "order": 1,
        "title": "Temperature (°C)",
        "label": "°C",
        "format": "{{value}}",
        "min": 0,
        "max": "50",
        "colors":["#2196F3","#00BCD4","#03A9F4"],
        "width": 4,
        "height": 4,
        "x": 430,
        "y": 100,
        "wires": []
    },
    {
        "id": "ui_chart_temp",
        "type": "ui_chart",
        "z": "flow-smart-home",
        "name": "Temperature Chart",
        "group": "ui_group_home",
        "order": 2,
        "label": "Temperature",
        "chartType": "line",
        "legend": "true",
        "xformat": "HH:mm:ss",
        "interpolate": "linear",
        "nodata": "",
        "dot": false,
        "ymin": "0",
        "ymax": "50",
        "removeOlder": "1",
        "removeOlderPoints": "100",
        "removeOlderUnit": "3600",
        "useOneColor": false,
        "colors": ["#00BCD4"],
        "outputs": 1,
        "width": 6,
        "height": 3,
        "x": 430,
        "y": 160,
        "wires": []
    },
    {
        "id": "ui_chart_ldr",
        "type": "ui_chart",
        "z": "flow-smart-home",
        "name": "LDR Chart",
        "group": "ui_group_home",
        "order": 3,
        "label": "Light Intensity",
        "chartType": "line",
        "legend": "true",
        "xformat": "HH:mm:ss",
        "interpolate": "linear",
        "nodata": "",
        "dot": false,
        "ymin": "0",
        "ymax": "100",
        "removeOlder": "1",
        "removeOlderPoints": "100",
        "removeOlderUnit": "3600",
        "useOneColor": false,
        "colors": ["#FFEB3B"],
        "outputs": 1,
        "width": 6,
        "height": 3,
        "x": 430,
        "y": 240,
        "wires": []
    },
    {
        "id": "ui_ldr_gauge",
        "type": "ui_gauge",
        "z": "flow-smart-home",
        "name": "LDR Gauge",
        "group": "ui_group_home",
        "order": 4,
        "width": 4,
        "height": 4,
        "gtype": "gage",
        "title": "Light Intensity",
        "label": "%",
        "format": "{{value}}",
        "min": 0,
        "max": 100,
        "colors":["#FFEB3B","#FFC107","#FF9800"],
        "seg1": 30,
        "seg2": 70,
        "x": 430,
        "y": 300,
        "wires": []
    },
    {
        "id": "function-motion",
        "type": "function",
        "z": "flow-smart-home",
        "name": "Motion Logic",
        "func": "let motion = (msg.payload == 1 || msg.payload == 'ON') ? 1 : 0;\nflow.set('motion', motion);\nreturn [{payload: motion ? 'ON' : 'OFF'}];",
        "outputs": 1,
        "x": 430,
        "y": 200,
        "wires": [["mqtt-led1"]]
    },
    {
        "id": "function-auto-light",
        "type": "function",
        "z": "flow-smart-home",
        "name": "Auto Light Logic (LDR + Motion)",
        "func": "let ldr=Number(msg.payload);\nlet threshold=40;\nflow.set('ldr',ldr);\nlet motion=flow.get('motion')||0;\nif(ldr<threshold && motion===1){node.status({fill:'yellow',shape:'dot',text:'Dark + Motion: Lights ON'});return [{payload:'ON'}];}else if(ldr>threshold){node.status({fill:'green',shape:'ring',text:'Bright: Lights OFF'});return [{payload:'OFF'}];}else{return [null];}",
        "outputs": 1,
        "x": 460,
        "y": 280,
        "wires": [["mqtt-led2"]]
    },
    {
        "id": "function-auto-temp",
        "type": "function",
        "z": "flow-smart-home",
        "name": "Auto Temp Logic (Cooling)",
        "func": "let temp=Number(msg.payload);\nif(temp>30){node.status({fill:'red',shape:'dot',text:'High Temp: Fan ON'});return [{payload:'ON'}];}else if(temp<25){node.status({fill:'blue',shape:'ring',text:'Normal Temp: Fan OFF'});return [{payload:'OFF'}];}else{return [null];}",
        "outputs": 1,
        "x": 460,
        "y": 340,
        "wires": [["mqtt-led3"]]
    },
    {
        "id": "ui_camera",
        "type": "ui_template",
        "z": "flow-smart-home",
        "group": "ui_group_home",
        "name": "Camera Stream",
        "order": 5,
        "width": 12,
        "height": 4,
        "format": "<div style='background:#222;border-radius:10px;padding:10px;text-align:center;'>\n  <iframe src='http://localhost:8081/?action=stream' width='100%' height='300px' style='border-radius:10px;'></iframe>\n</div>"
    },
    {
        "id": "ui_led_panel",
        "type": "ui_template",
        "group": "ui_group_home",
        "name": "LED Buttons",
        "order": 6,
        "width": 12,
        "height": 3,
        "format": "<div style='display:flex;justify-content:space-around;flex-wrap:wrap;background:#222;padding:15px;border-radius:10px;'>\n  <div style='text-align:center;margin:5px;'>\n    <button ng-click='send({payload:\"LED1_ON\"})' style='padding:10px 20px;background:#00bfa5;color:white;border:none;border-radius:8px;margin-bottom:5px;'>LED 1 ON</button><br>\n    <button ng-click='send({payload:\"LED1_OFF\"})' style='padding:10px 20px;background:#B0B0B0;color:black;border:none;border-radius:8px;'>LED 1 OFF</button>\n  </div>\n  <div style='text-align:center;margin:5px;'>\n    <button ng-click='send({payload:\"LED2_ON\"})' style='padding:10px 20px;background:#00bfa5;color:white;border:none;border-radius:8px;margin-bottom:5px;'>LED 2 ON</button><br>\n    <button ng-click='send({payload:\"LED2_OFF\"})' style='padding:10px 20px;background:#B0B0B0;color:black;border:none;border-radius:8px;'>LED 2 OFF</button>\n  </div>\n  <div style='text-align:center;margin:5px;'>\n    <button ng-click='send({payload:\"LED3_ON\"})' style='padding:10px 20px;background:#00bfa5;color:white;border:none;border-radius:8px;margin-bottom:5px;'>LED 3 ON</button><br>\n    <button ng-click='send({payload:\"LED3_OFF\"})' style='padding:10px 20px;background:#B0B0B0;color:black;border:none;border-radius:8px;'>LED 3 OFF</button>\n  </div>\n  <div style='text-align:center;margin:5px;'>\n    <button ng-click='send({payload:\"LED4_ON\"})' style='padding:10px 20px;background:#00bfa5;color:white;border:none;border-radius:8px;margin-bottom:5px;'>LED 4 ON</button><br>\n    <button ng-click='send({payload:\"LED4_OFF\"})' style='padding:10px 20px;background:#B0B0B0;color:black;border:none;border-radius:8px;'>LED 4 OFF</button>\n  </div>\n</div>",
        "x": 460,
        "y": 500,
        "wires": [["mqtt-led1","mqtt-led2","mqtt-led3","mqtt-led4"]]
    },
    {
        "id": "mqtt-led1",
        "type": "mqtt out",
        "z": "flow-smart-home",
        "name": "LED 1 (Motion)",
        "topic": "home/lights/led1",
        "broker": "mqtt-local"
    },
    {
        "id": "mqtt-led2",
        "type": "mqtt out",
        "z": "flow-smart-home",
        "name": "LED 2 (LDR)",
        "topic": "home/lights/led2",
        "broker": "mqtt-local"
    },
    {
        "id": "mqtt-led3",
        "type": "mqtt out",
        "z": "flow-smart-home",
        "name": "LED 3 (Temp)",
        "topic": "home/lights/led3",
        "broker": "mqtt-local"
    },
    {
        "id": "mqtt-led4",
        "type": "mqtt out",
        "z": "flow-smart-home",
        "name": "LED 4 (Manual)",
        "topic": "home/lights/led4",
        "broker": "mqtt-local"
    }
]
```

✅ **التعديلات الرئيسية:**

1. أضفت **Gauge للـLDR** باسم `ui_ldr_gauge` بجانب الـChart.
2. ربطت **MQTT LDR** مع الـGauge والـChart والـAuto Light Logic.
3. حافظت على **الأسلوب الداكن والمنظم** لكل الواجهة.
4. كل **الأجهزة وأزرار التحكم** متصلة بالـMQTT مباشرة.




-------------------------------------code server with mestquitto server(broker)to simulate this--------------------------

# ========================
import paho.mqtt.client as mqtt
import time
import random

broker = "localhost"
client = mqtt.Client()
client.connect(broker, 1883, 60)

# ========================
# callback عند استقبال أي رسالة
# ========================
def on_message(client, userdata, msg):
    topic = msg.topic
    payload = msg.payload.decode()
    print(f"Received: {topic} -> {payload}")

    # لو الموضوع تابع للـLEDs
    if topic.startswith("home/lights/"):
        led_name = topic.split("/")[-1].upper()  # led1 -> LED1
        print(f"{led_name} state: {payload}")
        # هنا ممكن تضيف أي كود للتحكم في LED فعلي على الهاردوير

client.on_message = on_message

# الاشتراك في جميع مواضيع الـLEDs
client.subscribe("home/lights/led1")
client.subscribe("home/lights/led2")
client.subscribe("home/lights/led3")
client.subscribe("home/lights/led4")

client.loop_start()

# ========================
# حلقة إرسال الحساسات
# ========================
try:
    while True:
        # محاكاة بيانات حساسات
        temp = random.randint(20, 35)
        ldr = random.randint(0, 100)
        motion = random.choice([0, 1])

        # إرسال البيانات على الـMQTT
        client.publish("home/sensors/temperature", temp)
        client.publish("home/sensors/ldr", ldr)
        client.publish("home/sensors/motion", motion)

        print(f"Sent -> Temp: {temp}, LDR: {ldr}, Motion: {motion}")
        time.sleep(5)

except KeyboardInterrupt:
    print("Exiting...")
    client.loop_stop()
    client.disconnect()
...........................................................................


how you can install mesquitto and node-red

Install Mosquitto
sudo apt update
sudo apt install mosquitto mosquitto-clients -y

Start the MQTT broker
sudo systemctl enable mosquitto
sudo systemctl start mosquitto

Test it locally

In Terminal 1:

mosquitto_sub -t test/topic


In Terminal 2:

mosquitto_pub -t test/topic -m "Hello from Nada"
----------------------------------------------------------

Install required packages:
sudo apt update
sudo apt install python3-pip python3-serial python3-gpiozero python3-rpi.gpio mosquitto mosquitto-clients -y
pip3 install paho-mqtt
sudo apt install nodejs npm -y
sudo npm install -g --unsafe-perm node-red

Run everything:
mosquitto &
python3 smart_home_pi.py &
node-red &

....................................
install mjpg for camera stream:-

Option 2 — Build from Source (If Snap Fails)

If the Snap version doesn’t work properly, you can build it manually:

1️⃣ Install dependencies:
sudo apt update
sudo apt install cmake libjpeg8-dev imagemagick libv4l-dev git -y

2️⃣ Clone the source:
git clone https://github.com/jacksonliam/mjpg-streamer.git
cd mjpg-streamer/mjpg-streamer-experimental

3️⃣ Build it:
make

4️⃣ Run the camera stream:
./mjpg_streamer -i "input_uvc.so -d /dev/video0 -r 640x480 -f 10" \
                -o "output_http.so -p 8081 -w ./www"


Now open your browser at:

http://localhost:8081/?action=stream


✅ You should see your laptop camera live!


--------------------------------------------------------------------

Integrate it with Node-RED Dashboard

Once your stream works, go to your Node-RED UI and add a Template node with this HTML:

<iframe src="http://localhost:8081/?action=stream" width="480" height="360"></iframe>


When you open your Node-RED Dashboard (http://localhost:1880/ui), you’ll see your camera stream directly inside your dashboard.


.........................................................................

