#!/usr/bin/env python

import time
import RF24
import RPi.GPIO as GPIO
import paho.mqtt.client as mqtt


radio = RF24.RF24(RPI_BPLUS_GPIO_J8_22, RPI_BPLUS_GPIO_J8_24, BCM2835_SPI_SPEED_8MHZ)
mqtt = mqtt.Client()


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

mqtt.connect(host='localhost')
mqtt.subscribe('/foo')
mqtt.loop_forever()






import nrf24
radio = nrf24.NRF24()
radio.begin(0, 0, 22, 25)
radio.openReadingPipe(1, bytearray('1mqtt', 'utf-8'))
radio.enableDynamicPayloads()

radio.printDetails()
radio.startListening()

while True:
    while not radio.available(1, irq_wait=True):
        pass
    buf = []
    radio.read(buf)
    print(buf)
