# smart_home_pi.py
# Raspberry Pi script (BCM pin numbering)
# - Reads LDR and LM35 temperature from Arduino UNO over serial (/dev/ttyACM0)
# - Simulates motion sensor
# - Publishes sensors to MQTT topics
# - Subscribes to LED topics and controls Raspberry Pi GPIO (BCM)
#
# Requirements:
#   pip3 install paho-mqtt pyserial RPi.GPIO
#
import paho.mqtt.client as mqtt
import time
import random
import serial
import RPi.GPIO as GPIO
import threading
import sys
import os

# === Configuration ===
SERIAL_PORT = os.environ.get('ARDUINO_PORT', '/dev/ttyACM0')  # Uno usually appears as /dev/ttyACM0
SERIAL_BAUD = 9600
MQTT_BROKER = os.environ.get('MQTT_BROKER', 'localhost')
PUBLISH_INTERVAL = 5.0  # seconds

# BCM pins for LEDs (you asked BCM numbering)
LED_PINS = {
    'led1': 17,  # GPIO17 (BCM)
    'led2': 27,  # GPIO27 (BCM)
    'led3': 22,  # GPIO22 (BCM)
    'led4': 5    # GPIO5  (BCM)
}

# === Setup GPIO ===
GPIO.setmode(GPIO.BCM)
for p in LED_PINS.values():
    GPIO.setup(p, GPIO.OUT)
    GPIO.output(p, GPIO.LOW)

# === MQTT client ===
client = mqtt.Client()

def on_connect(client, userdata, flags, rc):
    print(f"Connected to MQTT broker {MQTT_BROKER}, rc={rc}")
    # subscribe to LED topics
    for led in LED_PINS.keys():
        topic = f"home/lights/{led}"
        client.subscribe(topic)
        print("Subscribed to", topic)

def on_message(client, userdata, msg):
    topic = msg.topic
    payload = msg.payload.decode().strip()
    print(f"MQTT Received: {topic} -> {payload}")
    if topic.startswith("home/lights/"):
        led = topic.split('/')[-1]
        if led in LED_PINS:
            GPIO.output(LED_PINS[led], GPIO.HIGH if payload.upper() == 'ON' else GPIO.LOW)
            print(f"Set {led} -> {payload}")

client.on_connect = on_connect
client.on_message = on_message

try:
    client.connect(MQTT_BROKER, 1883, 60)
except Exception as e:
    print("ERROR: Cannot connect to MQTT broker:", e)
    sys.exit(1)

client.loop_start()

# === Serial read from Arduino ===
arduino = None
try:
    arduino = serial.Serial(SERIAL_PORT, SERIAL_BAUD, timeout=1)
    time.sleep(2.0)  # allow Arduino reset
    print(f"Connected to Arduino on {SERIAL_PORT}")
except Exception as e:
    print("Warning: Could not open serial port to Arduino:", e)
    arduino = None

def parse_serial_line(line):
    # expected format: LDR:520,TEMP:27.5
    ldr = None
    temp = None
    try:
        parts = line.split(',')
        for p in parts:
            if ':' in p:
                k, v = p.split(':',1)
                k = k.strip().upper()
                v = v.strip()
                if k == 'LDR':
                    ldr = int(float(v))
                elif k == 'TEMP':
                    temp = float(v)
    except Exception:
        pass
    return ldr, temp

def read_arduino_once():
    if not arduino:
        return None, None
    try:
        raw = arduino.readline().decode(errors='ignore').strip()
        if not raw:
            return None, None
        ldr, temp = parse_serial_line(raw)
        if ldr is None and temp is None:
            # try to parse if different format
            if 'LDR' in raw or 'TEMP' in raw:
                # best effort parse numbers
                import re
                nums = re.findall(r"[0-9]+(?:\.[0-9]+)?", raw)
                if len(nums) >= 2:
                    return int(float(nums[0])), float(nums[1])
            return None, None
        return ldr, temp
    except Exception as e:
        print('Serial read error:', e)
        return None, None

# === Main publishing loop ===
try:
    while True:
        ldr_val, temp_val = read_arduino_once()
        if ldr_val is None:
            # simulate analog 0-1023 for LDR if Arduino not connected / no data
            ldr_val = random.randint(0, 1023)
        if temp_val is None:
            # simulate LM35 temp in C
            temp_val = round(random.uniform(20.0, 35.0), 1)

        # simulate motion sensor (no PIR) - you can change logic here
        motion = random.choice([0, 1])

        # Map LDR 0-1023 to percentage 0-100 for dashboard convenience
        ldr_percent = int(ldr_val * 100 / 1023)

        # publish
        client.publish('home/sensors/temperature', temp_val)
        client.publish('home/sensors/ldr', ldr_percent)
        client.publish('home/sensors/motion', motion)

        print(f"Published -> Temp: {temp_val} °C | LDR: {ldr_percent}% | Motion: {motion}")

        time.sleep(PUBLISH_INTERVAL)

except KeyboardInterrupt:
    print('Stopping...')
finally:
    client.loop_stop()
    client.disconnect()
    if arduino:
        arduino.close()
    GPIO.cleanup()
