EESchema Schematic File Version 2
LIBS:tinkerforge
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
Title "Barometer Bricklet v2"
Date "2017-08-30"
Rev "2.0"
Comp "Tinkerforge GmbH"
Comment1 "Licensed under CERN OHL v.1.1"
Comment2 "Copyright (©) 2017, L.Lauer <lukas@tinkerforge.com>"
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 600  7700 0    40   ~ 0
Copyright Tinkerforge GmbH 2017.\nThis documentation describes Open Hardware and is licensed under the\nCERN OHL v. 1.1.\nYou may redistribute and modify this documentation under the terms of the\nCERN OHL v.1.1. (http://ohwr.org/cernohl). This documentation is distributed\nWITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING OF\nMERCHANTABILITY, SATISFACTORY QUALITY AND FITNESS FOR A\nPARTICULAR PURPOSE. Please see the CERN OHL v.1.1 for applicable\nconditions\n
$Comp
L DRILL U3
U 1 1 4C6050A5
P 10650 6150
F 0 "U3" H 10700 6200 60  0001 C CNN
F 1 "DRILL" H 10650 6150 60  0000 C CNN
F 2 "kicad-libraries:DRILL_NP" H 10650 6150 60  0001 C CNN
F 3 "" H 10650 6150 60  0001 C CNN
	1    10650 6150
	1    0    0    -1  
$EndComp
$Comp
L DRILL U4
U 1 1 4C6050A2
P 10650 6350
F 0 "U4" H 10700 6400 60  0001 C CNN
F 1 "DRILL" H 10650 6350 60  0000 C CNN
F 2 "kicad-libraries:DRILL_NP" H 10650 6350 60  0001 C CNN
F 3 "" H 10650 6350 60  0001 C CNN
	1    10650 6350
	1    0    0    -1  
$EndComp
$Comp
L DRILL U6
U 1 1 4C60509F
P 11000 6350
F 0 "U6" H 11050 6400 60  0001 C CNN
F 1 "DRILL" H 11000 6350 60  0000 C CNN
F 2 "kicad-libraries:DRILL_NP" H 11000 6350 60  0001 C CNN
F 3 "" H 11000 6350 60  0001 C CNN
	1    11000 6350
	1    0    0    -1  
$EndComp
$Comp
L DRILL U5
U 1 1 4C605099
P 11000 6150
F 0 "U5" H 11050 6200 60  0001 C CNN
F 1 "DRILL" H 11000 6150 60  0000 C CNN
F 2 "kicad-libraries:DRILL_NP" H 11000 6150 60  0001 C CNN
F 3 "" H 11000 6150 60  0001 C CNN
	1    11000 6150
	1    0    0    -1  
$EndComp
Text GLabel 2550 1700 2    39   Output ~ 0
S-CS
$Comp
L VCC #PWR01
U 1 1 4C5FCFB4
P 2300 850
F 0 "#PWR01" H 2300 950 30  0001 C CNN
F 1 "VCC" H 2300 950 30  0000 C CNN
F 2 "" H 2300 850 60  0001 C CNN
F 3 "" H 2300 850 60  0001 C CNN
	1    2300 850 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 4C5FCF5E
P 1100 2500
F 0 "#PWR02" H 1100 2500 30  0001 C CNN
F 1 "GND" H 1100 2430 30  0001 C CNN
F 2 "" H 1100 2500 60  0001 C CNN
F 3 "" H 1100 2500 60  0001 C CNN
	1    1100 2500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 4C5FCF4F
P 1600 2500
F 0 "#PWR03" H 1600 2500 30  0001 C CNN
F 1 "GND" H 1600 2430 30  0001 C CNN
F 2 "" H 1600 2500 60  0001 C CNN
F 3 "" H 1600 2500 60  0001 C CNN
	1    1600 2500
	1    0    0    -1  
$EndComp
$Comp
L CON-SENSOR2 P1
U 1 1 59A678E0
P 1100 1700
F 0 "P1" H 950 2100 60  0000 C CNN
F 1 "CON-SENSOR2" V 1250 1700 60  0000 C CNN
F 2 "kicad-libraries:CON-SENSOR2" H 1200 1550 60  0001 C CNN
F 3 "" H 1200 1550 60  0000 C CNN
	1    1100 1700
	-1   0    0    -1  
$EndComp
$Comp
L LPS22HB U2
U 1 1 59A67B09
P 8700 2950
F 0 "U2" H 8450 3600 60  0000 C CNN
F 1 "LPS22HB" V 8950 2600 60  0000 C CNN
F 2 "kicad-libraries:HLGA-10L" H 8650 3250 60  0001 C CNN
F 3 "" H 8650 3250 60  0000 C CNN
	1    8700 2950
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 59A67CE1
P 8350 2050
F 0 "C5" V 8400 2100 50  0000 L CNN
F 1 "100nF" V 8300 2100 50  0000 L CNN
F 2 "kicad-libraries:C0402F" H 8350 2050 60  0001 C CNN
F 3 "" H 8350 2050 60  0001 C CNN
	1    8350 2050
	0    -1   -1   0   
$EndComp
$Comp
L C C6
U 1 1 59A67D23
P 9050 2050
F 0 "C6" V 9100 2100 50  0000 L CNN
F 1 "100nF" V 8900 2050 50  0000 L CNN
F 2 "kicad-libraries:C0402F" H 9050 2050 60  0001 C CNN
F 3 "" H 9050 2050 60  0001 C CNN
	1    9050 2050
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR04
U 1 1 59A67FB4
P 8750 3750
F 0 "#PWR04" H 8750 3750 30  0001 C CNN
F 1 "GND" H 8750 3680 30  0001 C CNN
F 2 "" H 8750 3750 60  0001 C CNN
F 3 "" H 8750 3750 60  0001 C CNN
	1    8750 3750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 59A67FD7
P 8650 3750
F 0 "#PWR05" H 8650 3750 30  0001 C CNN
F 1 "GND" H 8650 3680 30  0001 C CNN
F 2 "" H 8650 3750 60  0001 C CNN
F 3 "" H 8650 3750 60  0001 C CNN
	1    8650 3750
	1    0    0    -1  
$EndComp
NoConn ~ 1450 1400
Text GLabel 2550 1800 2    39   Output ~ 0
S-CLK
Text GLabel 2550 1900 2    39   Output ~ 0
S-MOSI
Text GLabel 2550 2000 2    39   Input ~ 0
S-MISO
$Comp
L C C2
U 1 1 59A688A5
P 1850 1150
F 0 "C2" V 1900 1200 50  0000 L CNN
F 1 "10uF" V 1800 1200 50  0000 L CNN
F 2 "kicad-libraries:C0805" H 1850 1150 60  0001 C CNN
F 3 "" H 1850 1150 60  0001 C CNN
	1    1850 1150
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 59A68920
P 2300 1150
F 0 "C3" V 2350 1200 50  0000 L CNN
F 1 "1uF" V 2250 1200 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 2300 1150 60  0001 C CNN
F 3 "" H 2300 1150 60  0001 C CNN
	1    2300 1150
	1    0    0    -1  
$EndComp
$Comp
L R_PACK4 RP1
U 1 1 59A68BF3
P 2000 2050
F 0 "RP1" H 2000 2500 50  0000 C CNN
F 1 "82" H 2000 2000 50  0000 C CNN
F 2 "kicad-libraries:4X0402" H 2000 2050 50  0001 C CNN
F 3 "" H 2000 2050 50  0000 C CNN
	1    2000 2050
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 59A68F1D
P 1600 2250
F 0 "C1" V 1650 2300 50  0000 L CNN
F 1 "220pF" V 1550 2300 50  0000 L CNN
F 2 "kicad-libraries:C0402F" H 1600 2250 60  0001 C CNN
F 3 "" H 1600 2250 60  0001 C CNN
	1    1600 2250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 59A69103
P 2300 1550
F 0 "#PWR06" H 2300 1550 30  0001 C CNN
F 1 "GND" H 2300 1480 30  0001 C CNN
F 2 "" H 2300 1550 60  0001 C CNN
F 3 "" H 2300 1550 60  0001 C CNN
	1    2300 1550
	1    0    0    -1  
$EndComp
$Comp
L XMC1XXX24 U1
U 1 1 59A6925A
P 4950 5550
F 0 "U1" H 4800 5950 60  0000 C CNN
F 1 "XMC11XX24" H 4950 5100 60  0000 C CNN
F 2 "kicad-libraries:QFN24-4x4mm-0.5mm" H 5100 6300 60  0001 C CNN
F 3 "" H 5100 6300 60  0000 C CNN
	1    4950 5550
	1    0    0    -1  
$EndComp
$Comp
L XMC1XXX24 U1
U 3 1 59A6930E
P 4950 1800
F 0 "U1" H 4800 2100 60  0000 C CNN
F 1 "XMC11XX24" H 4950 1500 60  0000 C CNN
F 2 "kicad-libraries:QFN24-4x4mm-0.5mm" H 5100 2550 60  0001 C CNN
F 3 "" H 5100 2550 60  0000 C CNN
	3    4950 1800
	1    0    0    -1  
$EndComp
$Comp
L XMC1XXX24 U1
U 4 1 59A69353
P 4950 4150
F 0 "U1" H 4800 4650 60  0000 C CNN
F 1 "XMC11XX24" H 4950 3700 60  0000 C CNN
F 2 "kicad-libraries:QFN24-4x4mm-0.5mm" H 5100 4900 60  0001 C CNN
F 3 "" H 5100 4900 60  0000 C CNN
	4    4950 4150
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 59A697EC
P 4500 5500
F 0 "C4" H 4550 5600 50  0000 L CNN
F 1 "100n" H 4550 5400 50  0000 L CNN
F 2 "kicad-libraries:C0402F" H 4500 5500 60  0001 C CNN
F 3 "" H 4500 5500 60  0000 C CNN
	1    4500 5500
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR07
U 1 1 59A69992
P 4500 5950
F 0 "#PWR07" H 4500 5950 30  0001 C CNN
F 1 "GND" H 4500 5880 30  0001 C CNN
F 2 "" H 4500 5950 60  0001 C CNN
F 3 "" H 4500 5950 60  0001 C CNN
	1    4500 5950
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR08
U 1 1 59A69AFC
P 4500 5200
F 0 "#PWR08" H 4500 5300 30  0001 C CNN
F 1 "VCC" H 4500 5300 30  0000 C CNN
F 2 "" H 4500 5200 60  0001 C CNN
F 3 "" H 4500 5200 60  0001 C CNN
	1    4500 5200
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 59A6A2DF
P 4250 4400
F 0 "R1" V 4250 4500 50  0000 C CNN
F 1 "1k" V 4250 4300 50  0000 C CNN
F 2 "kicad-libraries:R0603F" H 4250 4400 60  0001 C CNN
F 3 "" H 4250 4400 60  0000 C CNN
	1    4250 4400
	0    1    1    0   
$EndComp
$Comp
L LED D1
U 1 1 59A6A408
P 3750 4400
F 0 "D1" H 3750 4500 50  0000 C CNN
F 1 "blue" H 3750 4300 50  0000 C CNN
F 2 "kicad-libraries:D0603E" H 3750 4400 50  0001 C CNN
F 3 "" H 3750 4400 50  0000 C CNN
	1    3750 4400
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P3
U 1 1 59A6A44B
P 4150 4150
F 0 "P3" H 4150 4300 50  0000 C CNN
F 1 "BOOT" V 4250 4150 50  0000 C CNN
F 2 "kicad-libraries:SolderJumper" H 4150 4050 50  0001 C CNN
F 3 "" H 4150 4050 50  0000 C CNN
	1    4150 4150
	-1   0    0    1   
$EndComp
NoConn ~ 4600 4500
NoConn ~ 4600 4300
NoConn ~ 4600 4200
NoConn ~ 4600 4000
NoConn ~ 4600 3900
Text GLabel 4450 3800 0    39   Output ~ 0
S-MISO
$Comp
L GND #PWR09
U 1 1 59A6AA4C
P 4400 4250
F 0 "#PWR09" H 4400 4250 30  0001 C CNN
F 1 "GND" H 4400 4180 30  0001 C CNN
F 2 "" H 4400 4250 60  0001 C CNN
F 3 "" H 4400 4250 60  0001 C CNN
	1    4400 4250
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR010
U 1 1 59A6AAC7
P 3500 4250
F 0 "#PWR010" H 3500 4350 30  0001 C CNN
F 1 "VCC" H 3500 4350 30  0000 C CNN
F 2 "" H 3500 4250 60  0001 C CNN
F 3 "" H 3500 4250 60  0001 C CNN
	1    3500 4250
	1    0    0    -1  
$EndComp
NoConn ~ 4600 1950
NoConn ~ 4600 1850
NoConn ~ 4600 1750
NoConn ~ 4600 1650
NoConn ~ 4600 3000
$Comp
L CONN_01X01 P2
U 1 1 59A6B0EA
P 4000 2400
F 0 "P2" H 4000 2500 50  0000 C CNN
F 1 "CONN_01X01" H 4050 2300 50  0000 C CNN
F 2 "kicad-libraries:DEBUG_PAD" H 4000 2400 50  0001 C CNN
F 3 "" H 4000 2400 50  0000 C CNN
	1    4000 2400
	-1   0    0    1   
$EndComp
Text GLabel 4450 3100 0    39   Input ~ 0
S-CS
Text GLabel 4450 3200 0    39   Input ~ 0
S-CLK
Text GLabel 4450 3300 0    39   Input ~ 0
S-MOSI
Text GLabel 3900 2600 0    39   Input ~ 0
M-MISO
Text GLabel 3900 2800 0    39   Output ~ 0
M-CLK
Text Notes 5400 2700 0    39   ~ 0
SPI Master\nP0.6 : CH1-DX0 : MISO\nP0.7 : CH1-DOUT : MOSI\nP0.8 : CH1-SCLKOUT : CLK\nP0.9 : CH1-SELO0 : SEL\n
Text Notes 5400 3150 0    39   ~ 0
SPI Slave/CH0\nP0.13 : USIC0_CH0-DX2F : SEL\nP0.14 : USIC0_CH0-DX1A : CLK\nP0.15 : USIC0_CH0-DX0B : MOSI\nP2.0 : USIC0_CH0-DOUT0 : MISO
Text GLabel 3900 2900 0    39   Output ~ 0
M-CS
Text GLabel 3900 2700 0    39   Output ~ 0
M-MOSI
$Comp
L XMC1XXX24 U1
U 2 1 59A692AF
P 4950 2850
F 0 "U1" H 4800 3400 60  0000 C CNN
F 1 "XMC11XX24" H 4950 2300 60  0000 C CNN
F 2 "kicad-libraries:QFN24-4x4mm-0.5mm" H 5100 3600 60  0001 C CNN
F 3 "" H 5100 3600 60  0000 C CNN
	2    4950 2850
	1    0    0    -1  
$EndComp
Text GLabel 7750 2700 0    39   Input ~ 0
M-CLK
Text GLabel 7750 2900 0    39   Input ~ 0
M-MOSI
Text GLabel 7750 3000 0    39   Output ~ 0
M-MISO
Text GLabel 7750 3100 0    39   Input ~ 0
M-CS
Text GLabel 7750 3200 0    39   Output ~ 0
INT
Text GLabel 4450 2500 0    39   Input ~ 0
INT
$Comp
L R_PACK4 RP2
U 1 1 59A6D565
P 4150 2950
F 0 "RP2" H 4150 3400 50  0000 C CNN
F 1 "82" H 4150 2900 50  0000 C CNN
F 2 "kicad-libraries:4X0402" H 4150 2950 50  0001 C CNN
F 3 "" H 4150 2950 50  0000 C CNN
	1    4150 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 2600 3950 2600
Wire Wire Line
	3900 2700 3950 2700
Wire Wire Line
	3900 2800 3950 2800
Wire Wire Line
	3950 2900 3900 2900
Wire Wire Line
	4450 2500 4600 2500
Wire Wire Line
	8200 3200 7750 3200
Wire Wire Line
	8200 3100 7750 3100
Wire Wire Line
	8200 3000 7750 3000
Wire Wire Line
	7750 2900 8200 2900
Wire Wire Line
	7750 2700 8200 2700
Wire Wire Line
	4350 2700 4600 2700
Wire Wire Line
	4350 2900 4600 2900
Wire Wire Line
	4200 2400 4600 2400
Wire Wire Line
	4350 2600 4600 2600
Wire Wire Line
	4450 3300 4600 3300
Wire Wire Line
	4450 3200 4600 3200
Wire Wire Line
	4450 3100 4600 3100
Wire Wire Line
	4350 2800 4600 2800
Wire Wire Line
	4450 3800 4600 3800
Wire Wire Line
	3500 4400 3500 4250
Wire Wire Line
	3550 4400 3500 4400
Wire Wire Line
	4000 4400 3950 4400
Wire Wire Line
	4500 4400 4600 4400
Wire Wire Line
	4400 4200 4400 4250
Wire Wire Line
	4350 4200 4400 4200
Wire Wire Line
	4600 4100 4350 4100
Connection ~ 4500 5850
Connection ~ 4500 5250
Connection ~ 4500 5750
Wire Wire Line
	4500 5850 4600 5850
Wire Wire Line
	4500 5700 4500 5950
Wire Wire Line
	4600 5750 4500 5750
Wire Wire Line
	4500 5250 4600 5250
Wire Wire Line
	4500 5200 4500 5300
Wire Wire Line
	1600 2500 1600 2450
Connection ~ 1600 2000
Wire Wire Line
	1600 2000 1600 2050
Wire Wire Line
	2200 2000 2550 2000
Wire Wire Line
	2200 1900 2550 1900
Wire Wire Line
	2200 1800 2550 1800
Wire Wire Line
	2200 1700 2550 1700
Wire Wire Line
	1800 2000 1450 2000
Wire Wire Line
	1450 1900 1800 1900
Wire Wire Line
	1800 1800 1450 1800
Wire Wire Line
	1450 1700 1800 1700
Connection ~ 2300 900 
Connection ~ 1850 900 
Wire Wire Line
	1850 950  1850 900 
Wire Wire Line
	2300 850  2300 950 
Wire Wire Line
	1650 900  2300 900 
Wire Wire Line
	1650 1600 1650 900 
Wire Wire Line
	1450 1600 1650 1600
Connection ~ 1850 1500
Wire Wire Line
	1850 1350 1850 1500
Connection ~ 2300 1500
Wire Wire Line
	2300 1350 2300 1550
Wire Wire Line
	1450 1500 2300 1500
Wire Wire Line
	1100 2150 1100 2500
Connection ~ 7900 2800
Wire Wire Line
	8150 2050 7900 2050
Wire Wire Line
	8200 2800 7900 2800
Wire Wire Line
	8650 3700 8650 3750
Wire Wire Line
	8750 3700 8750 3750
Wire Wire Line
	9250 2050 9300 2050
Wire Wire Line
	8750 2050 8850 2050
Wire Wire Line
	8750 1600 8750 2150
Wire Wire Line
	8650 2050 8550 2050
Wire Wire Line
	8650 1600 8650 2150
$Comp
L GND #PWR011
U 1 1 59A68132
P 7900 3750
F 0 "#PWR011" H 7900 3750 30  0001 C CNN
F 1 "GND" H 7900 3680 30  0001 C CNN
F 2 "" H 7900 3750 60  0001 C CNN
F 3 "" H 7900 3750 60  0001 C CNN
	1    7900 3750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 4CE29748
P 9300 3750
F 0 "#PWR012" H 9300 3750 30  0001 C CNN
F 1 "GND" H 9300 3680 30  0001 C CNN
F 2 "" H 9300 3750 60  0001 C CNN
F 3 "" H 9300 3750 60  0001 C CNN
	1    9300 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 2050 9300 3750
Wire Wire Line
	7900 1800 7900 3750
Connection ~ 8650 2050
$Comp
L C C7
U 1 1 59A6ED32
P 8350 1800
F 0 "C7" V 8400 1850 50  0000 L CNN
F 1 "1uF" V 8300 1850 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 8350 1800 60  0001 C CNN
F 3 "" H 8350 1800 60  0001 C CNN
	1    8350 1800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8550 1800 8650 1800
Wire Wire Line
	8150 1800 7900 1800
Connection ~ 7900 2050
Connection ~ 8750 2050
Connection ~ 8650 1800
$Comp
L VCC #PWR013
U 1 1 59A6F279
P 8650 1600
F 0 "#PWR013" H 8650 1700 30  0001 C CNN
F 1 "VCC" H 8650 1700 30  0000 C CNN
F 2 "" H 8650 1600 60  0001 C CNN
F 3 "" H 8650 1600 60  0001 C CNN
	1    8650 1600
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR014
U 1 1 59A6F368
P 8750 1600
F 0 "#PWR014" H 8750 1700 30  0001 C CNN
F 1 "VCC" H 8750 1700 30  0000 C CNN
F 2 "" H 8750 1600 60  0001 C CNN
F 3 "" H 8750 1600 60  0001 C CNN
	1    8750 1600
	1    0    0    -1  
$EndComp
$EndSCHEMATC
