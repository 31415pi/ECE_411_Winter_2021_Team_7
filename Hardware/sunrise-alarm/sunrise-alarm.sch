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
L MCU_Microchip_PIC18:PIC18F26K22-xSO U?
U 1 1 61792C0A
P 3250 3450
F 0 "U?" H 3250 4631 50  0000 C CNN
F 1 "PIC18F26K22-xSO" H 3250 4540 50  0000 C CNN
F 2 "Package_SO:SOIC-28W_7.5x17.9mm_P1.27mm" H 3450 3450 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/40001412G.pdf" H 3450 3450 50  0001 C CNN
	1    3250 3450
	1    0    0    -1  
$EndComp
$Comp
L Converter_ACDC:IRM-05-5 PS?
U 1 1 61797CD0
P 1800 1450
F 0 "PS?" H 1800 1817 50  0000 C CNN
F 1 "IRM-05-5" H 1800 1726 50  0000 C CNN
F 2 "Converter_ACDC:Converter_ACDC_MeanWell_IRM-05-xx_THT" H 1800 1100 50  0001 C CNN
F 3 "https://www.meanwell.com/Upload/PDF/IRM-05/IRM-05-SPEC.PDF" H 1800 1050 50  0001 C CNN
	1    1800 1450
	1    0    0    -1  
$EndComp
$Comp
L Relay_SolidState:MOC3052M U?
U 1 1 617989E0
P 3600 1800
F 0 "U?" H 3600 2125 50  0000 C CNN
F 1 "MOC3052M" H 3600 2034 50  0000 C CNN
F 2 "" H 3400 1600 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/MOC3052M-D.PDF" H 3600 1800 50  0001 L CNN
	1    3600 1800
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_WallPlug P?
U 1 1 617A28BD
P 850 900
F 0 "P?" H 867 1225 50  0000 C CNN
F 1 "Conn_WallPlug" H 867 1134 50  0000 C CNN
F 2 "" H 1250 900 50  0001 C CNN
F 3 "~" H 1250 900 50  0001 C CNN
	1    850  900 
	1    0    0    -1  
$EndComp
Text Notes 6500 650  0    50   ~ 0
Light Bulb Socket
$Comp
L Connector:Conn_WallSocket J?
U 1 1 617A341F
P 6800 900
F 0 "J?" H 6954 946 50  0000 L CNN
F 1 "Conn_WallSocket" H 6954 855 50  0000 L CNN
F 2 "" H 6400 900 50  0001 C CNN
F 3 "~" H 6400 900 50  0001 C CNN
	1    6800 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 1000 1200 1000
Wire Wire Line
	1050 800  1350 800 
Wire Wire Line
	1400 1550 1200 1550
Wire Wire Line
	1200 1550 1200 1000
Connection ~ 1200 1000
Wire Wire Line
	1200 1000 5700 1000
Wire Wire Line
	1400 1350 1350 1350
Wire Wire Line
	1350 1350 1350 800 
Connection ~ 1350 800 
Wire Wire Line
	1350 800  3950 800 
Wire Wire Line
	3900 1700 3950 1700
Wire Wire Line
	3950 1700 3950 1600
Text Notes 1400 1800 0    50   ~ 0
AC to DC 5v Supply
Text Notes 3400 2200 0    50   ~ 0
AC Controller\n- Ground to enable?\n- Check current limits
$Comp
L SamacSys_Parts:MOC3072SR2VM IC?
U 1 1 617BB411
P 9350 1350
F 0 "IC?" H 10100 1615 50  0000 C CNN
F 1 "MOC3072SR2VM" H 10100 1524 50  0000 C CNN
F 2 "SOP254P916X480-6N" H 10700 1450 50  0001 L CNN
F 3 "http://www.onsemi.com/pub/Collateral/MOC3072M-D.PDF" H 10700 1350 50  0001 L CNN
F 4 "Triac & SCR Output 6PW RP TRIAC 6-Pin DIP Random-Phase TriacDriver Optocoupler (800 Volt Peak)" H 10700 1250 50  0001 L CNN "Description"
F 5 "4.8" H 10700 1150 50  0001 L CNN "Height"
F 6 "863-MOC3072SR2VM" H 10700 1050 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.co.uk/ProductDetail/ON-Semiconductor/MOC3072SR2VM?qs=MLItCLRbWsx5QMvNShNGvA%3D%3D" H 10700 950 50  0001 L CNN "Mouser Price/Stock"
F 8 "ON Semiconductor" H 10700 850 50  0001 L CNN "Manufacturer_Name"
F 9 "MOC3072SR2VM" H 10700 750 50  0001 L CNN "Manufacturer_Part_Number"
	1    9350 1350
	1    0    0    -1  
$EndComp
$Comp
L SamacSys_Parts:ACST410-8BTR IC?
U 1 1 617BC564
P 4300 1800
F 0 "IC?" H 4800 2065 50  0000 C CNN
F 1 "ACST410-8BTR" H 4800 1974 50  0000 C CNN
F 2 "ACST4108BTR" H 5150 1900 50  0001 L CNN
F 3 "https://www.st.com/resource/en/datasheet/acst4.pdf" H 5150 1800 50  0001 L CNN
F 4 "STMicroelectronics, ACST410-8BTR, TRIAC, 800V 4A, Gate Trigger 1V 10mA, 3-Pin DPAK" H 5150 1700 50  0001 L CNN "Description"
F 5 "2.4" H 5150 1600 50  0001 L CNN "Height"
F 6 "STMicroelectronics" H 5150 1500 50  0001 L CNN "Manufacturer_Name"
F 7 "ACST410-8BTR" H 5150 1400 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "511-ACST410-8BTR" H 5150 1300 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.co.uk/ProductDetail/STMicroelectronics/ACST410-8BTR?qs=SAP8%252B8699SA4xcwG%252BvoKnA%3D%3D" H 5150 1200 50  0001 L CNN "Mouser Price/Stock"
F 10 "ACST410-8BTR" H 5150 1100 50  0001 L CNN "Arrow Part Number"
F 11 "https://www.arrow.com/en/products/acst410-8btr/stmicroelectronics" H 5150 1000 50  0001 L CNN "Arrow Price/Stock"
	1    4300 1800
	1    0    0    -1  
$EndComp
$Comp
L Display_Character:CA56-12EWA U?
U 1 1 617BEBA9
P 7100 3950
F 0 "U?" H 7100 4617 50  0000 C CNN
F 1 "CA56-12EWA" H 7100 4526 50  0000 C CNN
F 2 "Display_7Segment:CA56-12EWA" H 7100 3350 50  0001 C CNN
F 3 "http://www.kingbrightusa.com/images/catalog/SPEC/CA56-12EWA.pdf" H 6670 3980 50  0001 C CNN
	1    7100 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:Buzzer BZ?
U 1 1 617BFC39
P 5300 4500
F 0 "BZ?" H 5452 4529 50  0000 L CNN
F 1 "Buzzer" H 5452 4438 50  0000 L CNN
F 2 "" V 5275 4600 50  0001 C CNN
F 3 "~" V 5275 4600 50  0001 C CNN
	1    5300 4500
	1    0    0    -1  
$EndComp
$Comp
L SFH6286-4T:SFH6286-4T U?
U 1 1 617C0954
P 6650 1850
F 0 "U?" H 6650 2220 50  0000 C CNN
F 1 "SFH6286-4T" H 6650 2129 50  0000 C CNN
F 2 "SOIC254P977X460-4N" H 6650 1850 50  0001 L BNN
F 3 "" H 6650 1850 50  0001 L BNN
F 4 "Vishay" H 6650 1850 50  0001 L BNN "MANUFACTURER"
	1    6650 1850
	1    0    0    -1  
$EndComp
Text Notes 9600 950  0    50   ~ 0
Extra Parts and Packages
$Comp
L power:+5V #PWR?
U 1 1 617CBF21
P 2350 1350
F 0 "#PWR?" H 2350 1200 50  0001 C CNN
F 1 "+5V" H 2365 1523 50  0000 C CNN
F 2 "" H 2350 1350 50  0001 C CNN
F 3 "" H 2350 1350 50  0001 C CNN
	1    2350 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 1350 2350 1350
Wire Wire Line
	2200 1550 2350 1550
$Comp
L power:GND #PWR?
U 1 1 617CD345
P 2350 1550
F 0 "#PWR?" H 2350 1300 50  0001 C CNN
F 1 "GND" H 2355 1377 50  0000 C CNN
F 2 "" H 2350 1550 50  0001 C CNN
F 3 "" H 2350 1550 50  0001 C CNN
	1    2350 1550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 617CDBCF
P 2450 2850
F 0 "#PWR?" H 2450 2700 50  0001 C CNN
F 1 "+5V" H 2465 3023 50  0000 C CNN
F 2 "" H 2450 2850 50  0001 C CNN
F 3 "" H 2450 2850 50  0001 C CNN
	1    2450 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 2850 2550 2850
Text Notes 8150 7650 0    50   ~ 0
2021-10-27
Text Notes 10600 7650 0    50   ~ 0
v0.1
Text Notes 7400 7500 0    79   ~ 0
Sunrise Alarm Clock - ece411
$Comp
L power:GND #PWR?
U 1 1 617D035A
P 7250 1950
F 0 "#PWR?" H 7250 1700 50  0001 C CNN
F 1 "GND" H 7255 1777 50  0000 C CNN
F 2 "" H 7250 1950 50  0001 C CNN
F 3 "" H 7250 1950 50  0001 C CNN
	1    7250 1950
	1    0    0    -1  
$EndComp
Text Notes 5900 2250 0    50   Italic 0
Zero-Crossing Detector\n- Get resistor values
Text Notes 3700 2450 0    50   Italic 0
Pin Mapping Not Final
$Comp
L Device:R_US R?
U 1 1 617D84BF
P 3950 1450
F 0 "R?" H 4018 1496 50  0000 L CNN
F 1 "R_US" H 4018 1405 50  0000 L CNN
F 2 "" V 3990 1440 50  0001 C CNN
F 3 "~" H 3950 1450 50  0001 C CNN
	1    3950 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 800  3950 1300
$Comp
L Device:R_US R?
U 1 1 617DA1A1
P 3150 1700
F 0 "R?" V 2945 1700 50  0000 C CNN
F 1 "R_US" V 3036 1700 50  0000 C CNN
F 2 "" V 3190 1690 50  0001 C CNN
F 3 "~" H 3150 1700 50  0001 C CNN
	1    3150 1700
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 617E066A
P 2900 1700
F 0 "#PWR?" H 2900 1550 50  0001 C CNN
F 1 "+5V" H 2915 1873 50  0000 C CNN
F 2 "" H 2900 1700 50  0001 C CNN
F 3 "" H 2900 1700 50  0001 C CNN
	1    2900 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 1700 3000 1700
Wire Wire Line
	3300 1900 3200 1900
Wire Wire Line
	3900 1900 4300 1900
Wire Wire Line
	4300 1800 4300 800 
Wire Wire Line
	4300 800  3950 800 
Connection ~ 3950 800 
Wire Wire Line
	5300 1800 5450 1800
Wire Wire Line
	5450 1800 5450 800 
Wire Wire Line
	5450 800  6050 800 
Wire Wire Line
	6050 1750 6050 1550
Connection ~ 6050 800 
Wire Wire Line
	6050 800  6600 800 
Wire Wire Line
	6050 1950 5700 1950
Wire Wire Line
	5700 1950 5700 1550
Connection ~ 5700 1000
Wire Wire Line
	5700 1000 6600 1000
$Comp
L Device:R_US R?
U 1 1 617EB11B
P 5700 1400
F 0 "R?" H 5768 1446 50  0000 L CNN
F 1 "R_US" H 5768 1355 50  0000 L CNN
F 2 "" V 5740 1390 50  0001 C CNN
F 3 "~" H 5700 1400 50  0001 C CNN
	1    5700 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 1250 5700 1000
$Comp
L Device:R_US R?
U 1 1 617EC1C3
P 6050 1400
F 0 "R?" H 6118 1446 50  0000 L CNN
F 1 "R_US" H 6118 1355 50  0000 L CNN
F 2 "" V 6090 1390 50  0001 C CNN
F 3 "~" H 6050 1400 50  0001 C CNN
	1    6050 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 1250 6050 800 
$Comp
L Device:R_US R?
U 1 1 617EEA46
P 7400 1750
F 0 "R?" V 7195 1750 50  0000 C CNN
F 1 "R_US" V 7286 1750 50  0000 C CNN
F 2 "" V 7440 1740 50  0001 C CNN
F 3 "~" H 7400 1750 50  0001 C CNN
	1    7400 1750
	0    1    1    0   
$EndComp
Wire Wire Line
	7550 1750 7650 1750
Wire Wire Line
	7650 1750 7650 2400
Wire Wire Line
	7650 2400 5400 2400
$EndSCHEMATC
