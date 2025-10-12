import paho.mqtt.client as mqtt

broker = "localhost"
client = mqtt.Client()
client.connect(broker, 1883, 60)

# تعريف callback عند استقبال أي رسالة
def on_message(client, userdata, msg):
    topic = msg.topic
    payload = msg.payload.decode()
    print(f"Received: {topic} -> {payload}")

    # لو الموضوع تابع للـLEDs
    if topic.startswith("home/lights/"):
        led_name = topic.split("/")[-1].upper()  # led1 -> LED1
        print(f"{led_name} state: {payload}")

# الاشتراك في جميع المواضيع الخاصة بالـLEDs
client.on_message = on_message
client.subscribe("home/lights/led1")
client.subscribe("home/lights/led2")
client.subscribe("home/lights/led3")
client.subscribe("home/lights/led4")

client.loop_start()

try:
    print("Waiting for LED button presses from Node-RED...")
    while True:
        pass  # الحلقة الرئيسية فقط لتبقي البرنامج يعمل

except KeyboardInterrupt:
    print("Exiting...")
    client.loop_stop()
    client.disconnect()
