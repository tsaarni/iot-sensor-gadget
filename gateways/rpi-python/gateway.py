#!/usr/bin/env python

import time
import RF24
import RPi.GPIO as GPIO
import paho.mqtt.client as mqtt


radio = RF24.RF24(RPI_BPLUS_GPIO_J8_22, RPI_BPLUS_GPIO_J8_24, BCM2835_SPI_SPEED_8MHZ)
mqttc = mqtt.Client()


def radio_interrupt(channel):
    if radio.available():
        while radio.available():
            len = radio.getDynamicPayloadSize()
            buf = radio.read(len)
            print('Got payload size={} value="{}"'.format(len, receive_payload.decode('utf-8')))




GPIO.setmode(GPIO.BCM)

GPIO.setup(2, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.add_event_detect(2, GPIO.FALLING, callback=radio_interrupt)


radio.begin()
radio.enableDynamicPayloads()
radio.setRetries(5,15)
radio.printDetails()

radio.openWritingPipe(pipes[1])
radio.openReadingPipe(1, pipe_name)
radio.startListening()

connect(host, port=1883, keepalive=60, bind_address="")

while 1:
    time.sleep(1000)
