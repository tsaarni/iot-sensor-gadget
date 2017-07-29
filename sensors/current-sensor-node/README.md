
# Current sensor node

## Install pre-requisites

pip install platformio

## Compilation

    # compile and upload
    platformio run --target upload

    # just compile
    platformio run

    # monitor log prints
    platformio serialports monitor -b 115200
