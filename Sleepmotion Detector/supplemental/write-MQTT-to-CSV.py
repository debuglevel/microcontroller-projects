#!/usr/bin/env python3

# python3 write-MQTT-to-CSV.py > ../Data\ Analysis/describe-the-occasion.csv
# python3 write-MQTT-to-CSV.py | xz -c > ../Data\ Analysis/describe-the-occasion.csv.xz
# python3 write-MQTT-to-CSV.py | ( trap '' INT; xz -9e -c > ../Data\ Analysis/describe-the-occasion.csv.xz )  # To ensure only the script terminates on CRTL+C and xz handles the buffer.

import paho.mqtt.client as mqtt
import csv
from datetime import datetime
import sys

# Configuration
broker_address = "broker.hivemq.com"
broker_port = 1883
topic = "debuglevel/+/sleepsensor"

# Code
def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def on_connect(client, userdata, flags, rc):
    eprint("Connected with result code " + str(rc))
    
    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe(topic)

def on_message(client, userdata, msg):
    #eprint("Received message on topic " + msg.topic + ": " + str(msg.payload))
    #eprint(".", end = '', flush=True)

    iso8601_time = datetime.now().isoformat()
    data = msg.payload.decode("utf-8")

    print(f"{iso8601_time},{data}")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect(broker_address, broker_port, 60)

print("time,AccX,AccY,AccZ,GyroX,GyroY,GyroZ")

client.loop_forever()
