# ECE411 Sunrise Alarm Clock - Team 7

> "Never wake-up in darkness..."

View the [Product Design Specification](./Product%20Design%20Specification%20v1.pdf) for more information.

Look at the [Project Board](https://github.com/31415pi/ECE_411_Winter_2021_Team_7/projects/1).

Schematic located at [Firmware/Schematic](./Firmware/Schematic.pdf).

![L1 Decomposition](/CAD/L1%20Decomposition.png)


## Parts List

Parts list on [google drive](https://docs.google.com/spreadsheets/d/1yFu2dnekZCLbKxV9tUKsMTaaS4XpjHtpUTBXEi358RU/edit#gid=0). [Convert to Markdown](https://tabletomarkdown.com/convert-spreadsheet-to-markdown/).

| Part         | Name                                                 | Type            | Notes                        | Datasheet Internal                                                                                                                                                                                                                                                                      | Datasheet External | Website                                                                                                    | Source                                                          | Price  |
| ------------ | ---------------------------------------------------- | --------------- | ---------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------ | ---------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------- | ------ |
| HT16K33      | RAM Mapping 16\*8 LED Controller Driver with keyscan | LED Controller  |                              | [https://github.com/31415pi/ECE\_411\_Winter\_2021\_Team\_7/blob/main/Datasheets/HT16K33v120(LEDcontroller).pdf](https://github.com/31415pi/ECE_411_Winter_2021_Team_7/blob/main/Datasheets/HT16K33v120(LEDcontroller).pdf)                                                             |                    | [https://www.holtek.com/productdetail/-/vg/16K33](https://www.holtek.com/productdetail/-/vg/16K33)         |                                                                 |        |
| PIC18F26K42  |                                                      | Microcontroller | Actual Model Read from Chip. | [https://github.com/31415pi/ECE\_411\_Winter\_2021\_Team\_7/blob/main/Datasheets/PIC18(L)F26-27-45-46-47-55-56-57K42-Data-Sheet-40001919G.pdf](https://github.com/31415pi/ECE_411_Winter_2021_Team_7/blob/main/Datasheets/PIC18(L)F26-27-45-46-47-55-56-57K42-Data-Sheet-40001919G.pdf) |                    | [https://www.microchip.com/en-us/product/PIC18F26K42](https://www.microchip.com/en-us/product/PIC18F26K42) | EPL                                                             | $ 1.50 |
| IRM-05-5     |                                                      | DC Power Supply |                              | [https://github.com/31415pi/ECE\_411\_Winter\_2021\_Team\_7/blob/main/Datasheets/IRM-05(ac-5vsupply).pdf](https://github.com/31415pi/ECE_411_Winter_2021_Team_7/blob/main/Datasheets/IRM-05(ac-5vsupply).pdf)                                                                           |                    |                                                                                                            | [Mouser](https://www.mouser.com/ProductDetail/709-IRM05-5)      | $ 8.81 |
| MOC3052TVM   |                                                      | AC Controller   |                              | [https://github.com/31415pi/ECE\_411\_Winter\_2021\_Team\_7/blob/main/Datasheets/MOC3052M(ACcont).pdf](https://github.com/31415pi/ECE_411_Winter_2021_Team_7/blob/main/Datasheets/MOC3052M(ACcont).pdf)                                                                                 |                    |                                                                                                            | [Mouser](https://www.mouser.com/ProductDetail/512-MOC3052SR2M)  | $ 1.15 |
| ACST410-8BTR |                                                      | AC Switch       |                              | [https://github.com/31415pi/ECE\_411\_Winter\_2021\_Team\_7/blob/main/Datasheets/ACST410(ACswitch).pdf](https://github.com/31415pi/ECE_411_Winter_2021_Team_7/blob/main/Datasheets/ACST410(ACswitch).pdf)                                                                               |                    |                                                                                                            | [Mouser](https://www.mouser.com/ProductDetail/511-ACST410-8BTR) | $ 0.85 |
| SFH628A      |                                                      | AC Sensor       |                              | [https://github.com/31415pi/ECE\_411\_Winter\_2021\_Team\_7/blob/main/Datasheets/SFH628A(ACsensor).pdf](https://github.com/31415pi/ECE_411_Winter_2021_Team_7/blob/main/Datasheets/SFH628A(ACsensor).pdf)                                                                               |                    |                                                                                                            | [Mouser](https://www.mouser.com/ProductDetail/782-SFH6286-4T)   | $ 1.27 |
| COM-10931    | 7-Segment Display - 4-Digit (White)                  | Time Display    |                              | [https://github.com/31415pi/ECE\_411\_Winter\_2021\_Team\_7/blob/main/Datasheets/COM-10931\_ATA3492BW(7seg4digitSparkfun).pdf](https://github.com/31415pi/ECE_411_Winter_2021_Team_7/blob/main/Datasheets/COM-10931_ATA3492BW(7seg4digitSparkfun).pdf)                                  |                    | [https://www.sparkfun.com/products/10931](https://www.sparkfun.com/products/10931)                         | [Mouser](https://www.mouser.com/ProductDetail/474-COM-10931)    | $ 2.63 |




Alternate [Sparkfun Time Display](https://www.sparkfun.com/products/10931).

## Tools

- KiCad. [Third Party Libraries](https://www.kicad.org/libraries/third_party/)
- [Library Loader](https://componentsearchengine.com/tools) for loading schematics into KiCad and others. [Setup Instructions](https://www.samacsys.com/kicad/)
