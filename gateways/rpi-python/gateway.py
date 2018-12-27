#!/usr/bin/env python

import logging
import nrf24
import paho.mqtt.client as mqtt
import binascii
import time
import RPi.GPIO as GPIO

# spidev node /dev/spidev<SPI>.<CSE>
rpi_spi = 1
rpi_cse = 2

rpi_ce_pin  = 26
rpi_irq_pin = 13

# mqtt broker address
mqtt_address = 'localhost'

# pipe address for receiving messages from sensors
nrf_address = '1mqtt'

#logging.basicConfig(level=logging.DEBUG)
#logging.basicConfig(level=logging.ERROR)
logger = logging.getLogger('gateway')


########################################################################

def mqtt_connect(client, *rest):
    logger.info('connection to mqtt broker established')


def mqtt_disconnect(client, *rest):
    logger.info('connection to mqtt broker was terminated')


def main():

    # setup radio
    logger.info('initializing radio: address=%s' % nrf_address)
    radio = nrf24.NRF24()
    radio.begin(rpi_spi, rpi_cse, rpi_ce_pin, rpi_irq_pin)  # spi bus, device, ce_pin, irq_pin
    radio.openReadingPipe(1, bytearray(nrf_address, 'utf-8'))
    radio.enableDynamicPayloads()
    radio.setCRCLength(nrf24.NRF24.CRC_16);
    radio.setAutoAck(False);
    radio.printDetails()
    radio.startListening()

    # setup irq directly instead of using nrf24 module's interrupt support
    # due to bug: https://github.com/jpbarraca/pynrf24/pull/34
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(rpi_irq_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)

    # establish connection to mqtt broker
    logger.info('establishing connection to mqtt broker: address=%s' %
                mqtt_address)
    mqttc = mqtt.Client()
    mqttc.loop_start()  # run client network loop in background thread
    mqttc.on_connect = mqtt_connect
    mqttc.on_disconnect = mqtt_disconnect
    mqttc.connect(host=mqtt_address)

    # receive messages from sensors and relay them to broker
    logger.info('entering main loop')
    while True:
        GPIO.wait_for_edge(rpi_irq_pin, GPIO.FALLING, timeout=5000)
        while not radio.available():
            logger.info('no data received')

        buf = []
        radio.read(buf)
        #logger.debug(binascii.hexlify(bytes(buf)))
        # from array of integers into string
        msg = ''.join([chr(x) for x in buf])

        #logger.info("received msg: %s" % msg)

        # msg = 'topic?payload'
        try:
            topic, payload = msg.split('?')
        except ValueError as e:
            logger.error(e)
            continue

        #logger.info('publishing: %s' % msg)
        mqttc.publish(topic, payload)


if __name__ == '__main__':
    main()
