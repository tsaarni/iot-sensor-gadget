#!/usr/bin/env python

import logging
import nrf24
import paho.mqtt.client as mqtt


# mqtt broker address
mqtt_address = 'localhost'

# pipe address for receiving messages from sensors
nrf_address = '1mqtt'

logging.basicConfig(level=logging.INFO)
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
    radio.begin(0, 0, 22, 25)  # spi bus, device, ce_pin, irq_pin
    radio.openReadingPipe(1, bytearray(nrf_address, 'utf-8'))
    radio.enableDynamicPayloads()
    radio.printDetails()
    radio.startListening()

    # establish connection to mqtt broker
    logger.info('establishing connection to mqtt broker: address=%s' % mqtt_address)
    mqttc = mqtt.Client()
    mqttc.loop_start()  # run client network loop in background thread
    mqttc.on_connect = mqtt_connect
    mqttc.on_disconnect = mqtt_disconnect
    mqttc.connect(host=mqtt_address)


    # receive messages from sensors and relay them to broker
    logger.info('entering main loop')
    while True:
        while not radio.available(irq_wait=True):
            logger.info("no data")

        buf = []
        radio.read(buf)
        print(binascii.hexlify(bytes(buf)))
        msg = ''.join([chr(x) for x in buf]) # from array of integers into string

        logger.info("received msg: %s" % msg);

        # msg = 'topic?payload'
        try:
            topic, payload = msg.split('?')
        except ValueError as e:
            logger.error(e)
            continue

        #logger.info('publishing: %s' % msg)
        mqttc.publish(topic, payload);


if __name__ == '__main__':
    main()
