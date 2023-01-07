#!/usr/bin/env python3

import paho.mqtt.client as mqtt
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
    # eprint("Received message on topic " + msg.topic + ": " + str(msg.payload))
    # eprint(".", end = '', flush=True)

    iso8601_time = datetime.now().isoformat(sep=" ", timespec="milliseconds")
    data = msg.payload.decode("utf-8")

    # As a MQTT may contain multiple lines, prepend each  line with the timestamp.
    # NOTE: As we add the timestamp on the client side, the milliseconds do not have too much meaning anymore.
    #       We could interpolate, but meh.
    for line in data.splitlines():
        print(f"{iso8601_time},{line}", end="", flush=True)


client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect(broker_address, broker_port, 60)

print("time,AccX,AccY,AccZ,GyroX,GyroY,GyroZ")

client.loop_forever()
