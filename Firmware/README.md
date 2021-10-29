
# Programing Setup

## Tools
[Microchip MPLAB](https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-x-ide)
- Install 8-bit and 16-bit support.

[Code Configurator](https://www.microchip.com/en-us/development-tools-tools-and-software/embedded-software-center/mplab-code-configurator)

[XC Compilers](https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-xc-compilers)

## Device

[PIC18F26K22](../Datasheets/datasheet%20PIC18F26K22%20(microcontroller).pdf)
```
                                 ┌────┐__┌────┐
                    MCLR/VPP/RE3 ├  1      28 ┤ RB7/PGD  ICSP_DATA
                             RA0 ├  2      27 ┤ RB6/PGC  ICSP_CLK
                             RA1 ├  3      26 ┤ RB5
                             RA2 ├  4      25 ┤ RB4
                             RA3 ├  5      24 ┤ RB3
                             RA4 ├  6      23 ┤ RB2      INT2 SDA2
                             RA5 ├  7      22 ┤ RB1      INT1 SCL2 
                             VSS ├  8      21 ┤ RB0      INT0
                             RA7 ├  9      20 ┤ VDD
                             RA6 ├ 10      19 ┤ VSS
                             RC0 ├ 11      18 ┤ RC7
                             RC1 ├ 12      17 ┤ RC6
                             RC2 ├ 13      16 ┤ RC5
                       SCL1  RC3 ├ 14      15 ┤ RC4      SDA1
                                 ╘════════════╛
                                  PIC18(L)F2XK22
Stats:
64K Bytes Flash
32768 Single Word Instructions
3896 Bytes SRAM
1024 Bytes EEPROM
25   I/O
19   10-bit A/D Channels
2    SPI
2    I2C
3    8-bit timers
4    16-bit timers
```

![Additional Pin Mappings](/Firmware/PinMappings.png)

## Reset
Reset is done via the MCLR pin. Active low for reset. Can be toggled by MCLRE pin.

## In-Circuit Programing ICPS
Mode is PGC and PGD.
LVP bit must be enabled.

24.9 Single-Supply ICSP Programming.

See "Flash Memory Programming".

> The LVP bit may be set or cleared only when using standard high-voltage
> programming (VIHH applied to the MCLR/VPP/RE3 pin). Once LVP has been
> disabled, only the standard high-voltage programming is available and must
> be used to program the device.


## Compare Modules
Ref 14.2 Compare Mode in datasheet.
Compare mode lets us trigger and external event a set-time after 










