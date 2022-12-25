import paho.mqtt.client as mqtt
import csv
from datetime import datetime

# XXX: Borrowed from ChatGPT!

# MQTT broker address and port
broker_address = "broker.hivemq.com"
broker_port = 1883

# MQTT topic to subscribe to
topic = "debuglevel/C8:C9:A3:C9:45:CC/sleepsensor"

# CSV file to write to
csv_file = "data.csv"

# Open the CSV file for writing
file_handle = open(csv_file, "w")
file_handle.write("time,AccX,AccY,AccZ,GyroX,GyroY,GyroZ\n")

# Callback function for when the client receives a CONNACK response from the server
def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    
    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe(topic)

# Callback function for when a PUBLISH message is received from the server
def on_message(client, userdata, msg):
    #print("Received message on topic " + msg.topic + ": " + str(msg.payload))
    #print(".", end = '', flush=True)

    iso8601_time = datetime.now().isoformat()
    data = msg.payload.decode("utf-8")

    file_handle.write(f"{iso8601_time},{data}\n")

# Create a new MQTT client
client = mqtt.Client()

# Set the callback functions
client.on_connect = on_connect
client.on_message = on_message

# Connect to the MQTT broker
client.connect(broker_address, broker_port, 60)

# Run the MQTT client loop indefinitely
client.loop_forever()
