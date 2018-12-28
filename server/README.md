
# Home automation server

This project includes Ansible scripts for installing the server
environment for the home automation environment.  The environment
consist of [Node-RED](https://nodered.org/) with
[MQTT broker](https://github.com/zuhito/node-red-contrib-mqtt-broker)
support,
[InfluxDB](https://www.influxdata.com/time-series-platform/influxdb/)
for storing timeseries data from the sensors and
[Chronograf](https://www.influxdata.com/time-series-platform/chronograf/)
for visualization.


## Installation procedure

Install ArchLinux AUR helper for Ansible

    git clone https://github.com/kewlfft/ansible-aur.git ~/.ansible/plugins/modules/aur


Run playbook by executing following

    ansible-playbook --ask-become-pass deploy.yml


After installation has succeeded run following to execute final steps

    ansible-playbook --ask-become-pass hardening.yml
