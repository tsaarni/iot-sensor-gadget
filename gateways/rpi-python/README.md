
# MQTT gateway for sensors

This scripts acts as a relay between sensor nodes and MQTT broker.
The sensor nodes presented in this project use nRF24L01+ radio and
therefore cannot access IP network directly.  The script, running on
Raspberry Pi with an nRF24L01+ radio module, receives messages from
sensors and forwards them to MQTT broker.


## Installation

Enable SPI by adding following line in `/boot/config.txt`

    device_tree_param=spi=on


Install python modules

    virtualenv my-venv
    . my-venv/bin/activate
    pip install -r requirements.txt





### Pinout

Following table describes how to connect nRF24L01+ to Raspberry Pi.


    description         nRF24L01+   RPi pin   BCM pin
    ------------------+-----------+---------+---------
    GND   black       |        1  |     25  |
    VCC   white/gray  |        2  |     17  |
    ------------------+-----------+---------+---------
    CE    gray        |        3  |     15  |   BCM22
    CSN   purple      |        4  |     24  |   BCM8
    SCK   blue        |        5  |     23  |   BCM11
    MOSI  green       |        6  |     19  |   BCM10
    MISO  yellow      |        7  |     21  |   BCM9
    IRQ   orange      |        8  |     22  |   BCM25




## References

* [Raspberry Pi pinout](https://pinout.xyz/pinout/pin22_gpio25)
* [nRF24L01+ module pinout](http://imgur.com/a/XlmRq)
* [Python port of the RF24 library for NRF24L01+ radios](https://github.com/jpbarraca/pynrf24)
* [RPi.GPIO documentation](https://sourceforge.net/p/raspberry-gpio-python/wiki/Home/)


## Problems

### Cannot run the script as unprivileged user

In Arch Linux the GPIO dev and sysfs nodes are writable only by
root.  One can use
[udev rules from raspbian](https://github.com/RPi-Distro/spindle/blob/master/wheezy-stage3)
to allow some GPIO functionality to be accessed by unprivileged user:

    printf "SUBSYSTEM==\"gpio*\", PROGRAM=\"/bin/sh -c 'chown -R root:gpio /sys/class/gpio && chmod -R 770 /sys/class/gpio; chown -R root:gpio /sys/devices/virtual/gpio && chmod -R 770 /sys/devices/virtual/gpio'\"\n" > /etc/udev/rules.d/99-com.rules
    printf 'SUBSYSTEM=="i2c-dev", GROUP="i2c", MODE="0660"\n' >> /etc/udev/rules.d/99-com.rules
    printf 'SUBSYSTEM=="spidev", GROUP="spi", MODE="0660"\n' >> /etc/udev/rules.d/99-com.rules


In addition to these, also `/dev/gpiomem` needs `gpio` group
permissions.  After fixing the above problems `RPi.GPIO` still fails
to work fully.  The problem can be demonstrated by running following
code:

    import RPi.GPIO as GPIO
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(25, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.wait_for_edge(25, GPIO.FALLING)


This results in error `RuntimeError: Error waiting for edge`.  Reason
can be observed by running Python under `strace`:

    open("/sys/class/gpio/gpio25/direction", O_WRONLY) = -1 EACCES (Permission denied)


Running as root is the workaround until better set of udev rules are found.
