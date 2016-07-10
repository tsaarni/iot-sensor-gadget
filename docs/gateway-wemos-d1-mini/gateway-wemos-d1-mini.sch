EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Gateway"
Date "2016-07-08"
Rev "1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L WeMos_mini U1
U 1 1 577FAC09
P 3650 3750
F 0 "U1" H 3650 4250 60  0000 C CNN
F 1 "WeMos_mini" H 3650 3250 60  0000 C CNN
F 2 "" H 4200 3050 60  0000 C CNN
F 3 "" H 4200 3050 60  0000 C CNN
	1    3650 3750
	1    0    0    -1  
$EndComp
$Comp
L nRF24L01+ U2
U 1 1 577FAD2A
P 7750 3850
F 0 "U2" H 7750 3550 50  0000 C CNN
F 1 "nRF24L01+" H 7750 4150 50  0000 C CNN
F 2 "MODULE" H 7750 3950 50  0001 C CNN
F 3 "DOCUMENTATION" H 7750 3800 50  0001 C CNN
	1    7750 3850
	1    0    0    -1  
$EndComp
Text GLabel 8500 3800 2    60   Input ~ 0
MOSI
Text GLabel 8500 3950 2    60   Input ~ 0
MISO
Text GLabel 8500 3650 2    60   Input ~ 0
SCK
NoConn ~ 8500 4100
Text GLabel 7000 4100 0    60   Input ~ 0
CSN
Text GLabel 7000 3950 0    60   Input ~ 0
CE
Text GLabel 6100 4000 0    60   Input ~ 0
VCC
Text GLabel 6100 3450 0    60   Input ~ 0
GND
Text GLabel 3150 3500 0    60   Input ~ 0
GND
Text GLabel 4150 3400 2    60   Input ~ 0
VCC
Text GLabel 4150 3700 2    60   Input ~ 0
MISO
Text GLabel 4150 3600 2    60   Input ~ 0
MOSI
Text GLabel 4150 3800 2    60   Input ~ 0
SCK
Text GLabel 3150 3800 0    60   Input ~ 0
CE
Text GLabel 3150 3900 0    60   Input ~ 0
CSN
$Comp
L CP C1
U 1 1 577FB5B0
P 6350 3700
F 0 "C1" H 6375 3800 50  0000 L CNN
F 1 "10u" H 6375 3600 50  0000 L CNN
F 2 "" H 6388 3550 50  0000 C CNN
F 3 "" H 6350 3700 50  0000 C CNN
	1    6350 3700
	-1   0    0    1   
$EndComp
NoConn ~ 3150 3400
NoConn ~ 3150 3600
NoConn ~ 3150 3700
NoConn ~ 3150 4000
NoConn ~ 3150 4100
NoConn ~ 4150 4100
NoConn ~ 4150 4000
NoConn ~ 4150 3900
NoConn ~ 4150 3500
Wire Wire Line
	7000 3800 6650 3800
Wire Wire Line
	6650 3800 6650 4000
Wire Wire Line
	6350 3850 6350 4000
Wire Wire Line
	6350 3550 6350 3450
Wire Wire Line
	6100 3450 6650 3450
Wire Wire Line
	6650 3450 6650 3650
Wire Wire Line
	6650 3650 7000 3650
Wire Wire Line
	6650 4000 6100 4000
Connection ~ 6350 3450
Connection ~ 6350 4000
$EndSCHEMATC
