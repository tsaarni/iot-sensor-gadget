
# MQTT gateway for sensors

This scripts acts as a relay between sensor nodes and MQTT broker.
The sensor nodes presented in this project use nRF24L01+ radio and
therefore cannot access IP network directly.  The script, running on
Raspberry Pi with an nRF24L01+ radio module, receives messages from
sensors and forwards them to MQTT broker.


## Installation

Enable SPI by adding following in `/boot/config.txt`

    device_tree_param=spi=on
    dtoverlay=spi1-3cs


Install python modules

    virtualenv my-venv
    . my-venv/bin/activate
    pip install -r requirements.txt





### Pinout

Following table describes how to connect nRF24L01+ to Raspberry Pi.


    Alternative 1: SPI0, chip select 0
    ==================================

    desc      nRF24L01+   RPi pin   BCM pin
    --------+-----------+---------+---------
    GND     |        1  |     25  |
    VCC     |        2  |     17  |
    --------+-----------+---------+---------
    CE      |        3  |     15  |   BCM22
    CSN     |        4  |     24  |   BCM8
    SCK     |        5  |     23  |   BCM11
    MOSI    |        6  |     19  |   BCM10
    MISO    |        7  |     21  |   BCM9
    IRQ     |        8  |     22  |   BCM25


    Alternative 2: SPI1, chip select 2
    ==================================

    desc      nRF24L01+   RPi pin   BCM pin
    --------+-----------+---------+---------
    GND     |        1  |     39  |
    VCC     |        2  |      1  |
    --------+-----------+---------+---------
    CE      |        3  |     37  |   BCM26
    CSN     |        4  |     36  |   BCM16
    SCK     |        5  |     40  |   BCM21
    MOSI    |        6  |     38  |   BCM20
    MISO    |        7  |     35  |   BCM19
    IRQ     |        8  |     33  |   BCM13



### Service

Define systemd service for starting the script `/etc/systemd/system/nrf24gateway.service`

    [Unit]
    Description=nrf24-gateway
    After=network.target

    [Service]
    Restart=always
    KillSignal=SIGINT
    WorkingDirectory=/home/user/sensor-gadgets/gateways/rpi-python/
    ExecStart=/home/user/sensor-gadgets/gateways/rpi-python/my-venv/bin/python gateway.py --serve-in-foreground

    [Install]
    WantedBy=multi-user.target

Enable service

    sudo systemctl --system daemon-reload
    sudo systemctl enable nrf24gateway.service
    sudo systemctl start nrf24gateway.service

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
