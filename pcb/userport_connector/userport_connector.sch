EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 74xx:74LS245 U1
U 1 1 62D0A85F
P 5050 2250
F 0 "U1" H 5050 3231 50  0000 C CNN
F 1 "74LVC245" H 5050 3140 50  0000 C CNN
F 2 "Package_DIP:DIP-20_W7.62mm" H 5050 2250 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS245" H 5050 2250 50  0001 C CNN
	1    5050 2250
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x12_Top_Bottom J1
U 1 1 62D0BB67
P 2250 2150
F 0 "J1" H 2300 2867 50  0000 C CNN
F 1 "PET User Port" H 2300 2776 50  0000 C CNN
F 2 "Connector_PCBEdge:2x12_Card_Edge" H 2250 2150 50  0001 C CNN
F 3 "~" H 2250 2150 50  0001 C CNN
	1    2250 2150
	1    0    0    -1  
$EndComp
Text GLabel 2550 1750 2    50   Input ~ 0
CA1
Text GLabel 2550 1850 2    50   Input ~ 0
PB0
Text GLabel 2550 1950 2    50   Input ~ 0
PB1
Text GLabel 2550 2050 2    50   Input ~ 0
PB2
Text GLabel 2550 2150 2    50   Input ~ 0
PB3
Text GLabel 2550 2250 2    50   Input ~ 0
PB4
Text GLabel 2550 2350 2    50   Input ~ 0
PB5
Text GLabel 2550 2450 2    50   Input ~ 0
PB6
Text GLabel 2550 2550 2    50   Input ~ 0
PB7
Text GLabel 2550 2650 2    50   Input ~ 0
CB2
$Comp
L power:GND #PWR0101
U 1 1 62D0D313
P 2900 1650
F 0 "#PWR0101" H 2900 1400 50  0001 C CNN
F 1 "GND" H 2905 1477 50  0000 C CNN
F 2 "" H 2900 1650 50  0001 C CNN
F 3 "" H 2900 1650 50  0001 C CNN
	1    2900 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 1650 2900 1650
$Comp
L power:GND #PWR0102
U 1 1 62D0D5EA
P 2900 2750
F 0 "#PWR0102" H 2900 2500 50  0001 C CNN
F 1 "GND" H 2905 2577 50  0000 C CNN
F 2 "" H 2900 2750 50  0001 C CNN
F 3 "" H 2900 2750 50  0001 C CNN
	1    2900 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 2750 2900 2750
$Comp
L Connector:Raspberry_Pi_2_3 J2
U 1 1 62D0D9A9
P 2300 5150
F 0 "J2" H 2300 6631 50  0000 C CNN
F 1 "Raspberry_Pi_2_3" H 2300 6540 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x20_P2.54mm_Vertical" H 2300 5150 50  0001 C CNN
F 3 "https://www.raspberrypi.org/documentation/hardware/raspberrypi/schematics/rpi_SCH_3bplus_1p0_reduced.pdf" H 2300 5150 50  0001 C CNN
	1    2300 5150
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0103
U 1 1 62D102D4
P 2100 3550
F 0 "#PWR0103" H 2100 3400 50  0001 C CNN
F 1 "+5V" H 2115 3723 50  0000 C CNN
F 2 "" H 2100 3550 50  0001 C CNN
F 3 "" H 2100 3550 50  0001 C CNN
	1    2100 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 3850 2100 3550
$Comp
L power:+3.3V #PWR0104
U 1 1 62D1089F
P 2400 3550
F 0 "#PWR0104" H 2400 3400 50  0001 C CNN
F 1 "+3.3V" H 2415 3723 50  0000 C CNN
F 2 "" H 2400 3550 50  0001 C CNN
F 3 "" H 2400 3550 50  0001 C CNN
	1    2400 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 3850 2400 3550
$Comp
L power:GND #PWR0105
U 1 1 62D10DAB
P 5050 3050
F 0 "#PWR0105" H 5050 2800 50  0001 C CNN
F 1 "GND" H 5055 2877 50  0000 C CNN
F 2 "" H 5050 3050 50  0001 C CNN
F 3 "" H 5050 3050 50  0001 C CNN
	1    5050 3050
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0106
U 1 1 62D110A4
P 5050 1100
F 0 "#PWR0106" H 5050 950 50  0001 C CNN
F 1 "+3.3V" H 5065 1273 50  0000 C CNN
F 2 "" H 5050 1100 50  0001 C CNN
F 3 "" H 5050 1100 50  0001 C CNN
	1    5050 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 1100 5050 1450
Wire Wire Line
	1900 6450 2000 6450
Connection ~ 2000 6450
Wire Wire Line
	2000 6450 2100 6450
Connection ~ 2100 6450
Wire Wire Line
	2100 6450 2200 6450
Connection ~ 2200 6450
Wire Wire Line
	2200 6450 2300 6450
Connection ~ 2300 6450
Wire Wire Line
	2300 6450 2400 6450
Connection ~ 2400 6450
Wire Wire Line
	2400 6450 2500 6450
Connection ~ 2500 6450
Wire Wire Line
	2500 6450 2600 6450
$Comp
L power:GND #PWR0107
U 1 1 62D118A7
P 2600 6600
F 0 "#PWR0107" H 2600 6350 50  0001 C CNN
F 1 "GND" H 2605 6427 50  0000 C CNN
F 2 "" H 2600 6600 50  0001 C CNN
F 3 "" H 2600 6600 50  0001 C CNN
	1    2600 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 6450 2600 6600
Connection ~ 2600 6450
Text GLabel 4550 1750 0    50   Input ~ 0
PB0
Text GLabel 4550 1850 0    50   Input ~ 0
PB1
Text GLabel 4550 1950 0    50   Input ~ 0
PB2
Text GLabel 4550 2050 0    50   Input ~ 0
PB3
Text GLabel 4550 2150 0    50   Input ~ 0
PB4
Text GLabel 4550 2250 0    50   Input ~ 0
PB5
Text GLabel 4550 2350 0    50   Input ~ 0
PB6
Text GLabel 4550 2450 0    50   Input ~ 0
PB7
Text GLabel 3100 4350 2    50   Input ~ 0
D2
Text GLabel 3100 4950 2    50   Input ~ 0
D6
Text GLabel 3100 5050 2    50   Input ~ 0
D5
Text GLabel 3100 5950 2    50   Input ~ 0
D4
Text GLabel 1500 4950 0    50   Input ~ 0
D3
Text GLabel 1500 5750 0    50   Input ~ 0
D7
Text GLabel 1500 5150 0    50   Input ~ 0
DIR
Text GLabel 1500 5050 0    50   Input ~ 0
OUTPUT_ENABLE_BAR
Text GLabel 5550 1750 2    50   Input ~ 0
D0
Text GLabel 5550 1850 2    50   Input ~ 0
D1
Text GLabel 5550 1950 2    50   Input ~ 0
D2
Text GLabel 5550 2050 2    50   Input ~ 0
D3
Text GLabel 5550 2150 2    50   Input ~ 0
D4
Text GLabel 5550 2250 2    50   Input ~ 0
D5
Text GLabel 5550 2350 2    50   Input ~ 0
D6
Text GLabel 5550 2450 2    50   Input ~ 0
D7
Text GLabel 1500 4550 0    50   Input ~ 0
D0
Text GLabel 4550 2650 0    50   Input ~ 0
DIR
Text GLabel 3100 5850 2    50   Input ~ 0
D1
Text GLabel 1500 5450 0    50   Input ~ 0
CA1
Text GLabel 1500 5550 0    50   Input ~ 0
BCB2
Text GLabel 4550 2750 0    50   Input ~ 0
OUTPUT_ENABLE_BAR
$Comp
L Device:R R1
U 1 1 62D87B1D
P 4500 4150
F 0 "R1" H 4570 4196 50  0000 L CNN
F 1 "1K" H 4570 4105 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4430 4150 50  0001 C CNN
F 3 "~" H 4500 4150 50  0001 C CNN
	1    4500 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 62D87F30
P 4500 4450
F 0 "R2" H 4570 4496 50  0000 L CNN
F 1 "1K" H 4570 4405 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4430 4450 50  0001 C CNN
F 3 "~" H 4500 4450 50  0001 C CNN
	1    4500 4450
	1    0    0    -1  
$EndComp
Text GLabel 4250 4000 0    50   Input ~ 0
CB2
Wire Wire Line
	4250 4000 4500 4000
Text GLabel 4850 4300 2    50   Input ~ 0
BCB2
Wire Wire Line
	4500 4300 4850 4300
Connection ~ 4500 4300
$Comp
L power:GND #PWR0108
U 1 1 62D88D6B
P 4500 4900
F 0 "#PWR0108" H 4500 4650 50  0001 C CNN
F 1 "GND" H 4505 4727 50  0000 C CNN
F 2 "" H 4500 4900 50  0001 C CNN
F 3 "" H 4500 4900 50  0001 C CNN
	1    4500 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 62D899E6
P 4500 4750
F 0 "R3" H 4570 4796 50  0000 L CNN
F 1 "1K" H 4570 4705 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4430 4750 50  0001 C CNN
F 3 "~" H 4500 4750 50  0001 C CNN
	1    4500 4750
	1    0    0    -1  
$EndComp
$EndSCHEMATC
