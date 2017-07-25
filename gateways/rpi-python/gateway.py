#!/usr/bin/env python

import nrf24


radio = nrf24.NRF24()
radio.begin(1, 0, "P9_23", "P9_24")
radio.openReadingPipe(1, ['1','m','q','t','t'])


buf = []
radio.read(buf)
