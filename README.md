
# Sensor Gadgets

**NOTE: This is work in progress**

## Overview

The idea for the project is to introduce a network of sensors at home which report their readings to MQTT broker over the Internet.
The readings can then be further processed and stored e.g. into a time series database and visualized by a dashboard.

The Sensor Gadget network consists of single gateway node and one or more sensor nodes.

### Multi-sensor node

Multi-sensor node is based on Atmel ATmega328 microcontroller and contains one or several of the following sensors:

- door (tripped when door remains opened for certain time)
- light
- temperature
- humidity
- battery level

Multi-sensor node is powered by a battery and it is connected to the gateway using low power Nordic Semiconductor nRF24L01+ radio module.
Further details can be seen in [multi-sensor node schematics](https://media.githubusercontent.com/media/tsaarni/sensor-gadgets/master/docs/multi-sensor-node-atmega328/sensor-node-atmega328.png).


### Current sensor node

Current sensor node consist of current transformers for 3 phases and analog-to-digital converters to measure the voltage across the transformers.  Measurement is taken NNN times per second and root-mean-square voltage is calculated.  The three RMS values is reported to the gateway using nRF24L01+ radio module.
Current sensor node is powered by 5V power supply.


### Gateway node

Gateway node connects the sensors to IP network and forwards the readings to MQTT broker.

The hardware is based on WeMos d1 mini development board for ESP8266 microcontroller.  It has integrated wifi and TCP/IP support.  The gateway node also has nRF24L01+ radio module for receiving data from sensors.
Gateway is powered by USB power adapter.

