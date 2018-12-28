
# Sensor Gadgets

**NOTE: This is work in progress**

## Overview

The idea for the project is to introduce a network of sensors at
home. The sensors report their readings to MQTT broker over the
internet.  The readings are processed by
[Node-RED](https://nodered.org/), stored to
[InfluxDB](https://www.influxdata.com/time-series-platform/influxdb/)
time-series database and visualized by
[Chronograf](https://www.influxdata.com/time-series-platform/chronograf/dashboard).

The project consists of single gateway node and several sensor nodes.

### Multi-sensor node

Multi-sensor node is based on SMT32 microcontroller and contains one
or more of the following sensors:

- door (tripped when door remains opened for certain time)
- light
- temperature
- humidity

Multi-sensor node is powered by a battery and it is connected to the
gateway using low power Nordic Semiconductor nRF24L01+ radio module.

![Sensor Node by tero.saarni@gmail.com 76793bf751a487b2 - Upverter](https://upverter.com/tero.saarni@gmail.com/76793bf751a487b2/Sensor-Node/embed_img/15414858090000/)

See
[here](https://upverter.com/tero.saarni@gmail.com/76793bf751a487b2/Sensor-Node/)
for the project page at Upverter.

The following picture shows the PCB populated as outdoor sensor
node. It contains a STM32 microcontroller, radio, HTU21D temperature &
humidity sensor and two AA batteries with a boost converter for 3.3V
power supply.  See [here](sensors/outdoor-sensor-node-mbed) for the
source code.

![Imgur](https://i.imgur.com/DBMON8c.jpg)


### Current sensor node

Current sensor node consist of current transformers for 3 phases and
analog-to-digital converters to measure the voltage across the
transformers.  Measurement is taken NNN times per second and
root-mean-square voltage is calculated.  The three RMS values is
reported to the gateway using nRF24L01+ radio module.  Current sensor
node is based on cheap STM32 development board and it is powered by 5V
power supply. See [here](sensors/current-sensor-node-mbed) for source
code.

![Imgur](https://i.imgur.com/fz5bZAZ.jpg)



### Gateway node

Gateway node is based on Raspberry Pi 3. It receives the sensor
readings via nRF24L01+ radio and forwards them to the IP network via
MQTT.  See [here](gateways/rpi-python/) for the gateway source code.

![Imgur](https://i.imgur.com/JvEXLti.jpg)


Currently the gateway is also running Node-red, InfluxDB and
Chronograf locally.  Chronograf dashboard provides real-time view on
the data stored in InfluxDB. See [here](server) for the installation
scripts.

![Imgur](https://i.imgur.com/CCg2psp.png)

