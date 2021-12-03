
# Sunrise Alarm DC



## Evaluation of Screens for Testing

<https://www.amazon.com/Pieces-Display-Module-SSD1306-3-3V-5V/dp/B08CDN5PSJ/ref=pd_lpo_3?pd_rd_i=B08CDN5PSJ&th=1>

- Answer on amazon site says that it is not configurable.
- No Manual/Datasheet on amazon website. Reviews say need to Google.
- Best guess based on reviews is that the controller is a clone of the **Adafruit_SSD1306**
    - Link to possible cloned screen. Many configurations so difficult to tell which.
		- Version with i2c only? <https://www.adafruit.com/product/931>
		- Version with SPI only? <https://www.adafruit.com/product/661>
	- Adafruit screens Use onboard jumper to switch i2c address. Have a "D/C" pin fir this reason.
	- Default i2c address: 0x3C
	- Alternate i2c address: 0x3D
	- Some versions are SPI only or I2C only.
	- Link to display [library](https://github.com/adafruit/Adafruit_SSD1306)
	- Links
		- [Tutorial](https://learn.adafruit.com/monochrome-oled-breakouts/downloads)
		- [Datasheet](http://www.adafruit.com/datasheets/SSD1306.pdf)
			- I2c Address "Either “0111100” or “0111101”"

### Conclusions

Unable to switch i2c address on knockoff screen. Since the Adafruit screen uses an additional pin to switch the address no-pin means we are unable to switch. No provided datasheet for the knockoff device means there is no discoverable internal way to swap them. Answers on amazon confirm.

- Possible solution to add a i2c select pin from the Arduino to select which display we are writing to. This may conflict with the internal states of the SSD1306 libraries.

## Search on Mouser for screens

<https://www.mouser.com/c/optoelectronics/displays/oled-displays-accessories/?q=i2c%20oled&operating%20supply%20voltage=2.4%20V%20to%205.5%20V%7C~2.8%20V%2C%205%20V%7C~3.1%20V%20to%205.25%20V~~5%20V&rp=optoelectronics%2Fdisplays%2Foled-displays-accessories%7C~Operating%20Supply%20Voltage>

- Options are very expensive.
- Probably more reliable.
- **Out of price range...**

## Evaluation of Maddie's proposed screens

- $6.39 per screen [HiLetgo-Serial-128x64](https://www.amazon.com/HiLetgo-Serial-128X64-Display-Color/dp/B06XRBTBTB/ref=asc_df_B06XRBTBTB/?tag=&linkCode=df0&hvadid=312232463708&hvpos=&hvnetw=g&hvrand=12771893554953602876&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9061080&hvtargid=pla-563271619351&ref=&adgrpid=57656765450&th=1)
	- No selectable address

- $2.80 per screen (bundle of 10) [Frienda-Serial-128x64](https://www.amazon.com/dp/B08VNNCLHD/ref=sspa_dk_detail_0?spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEyV1dEVVhUUFdWOUwzJmVuY3J5cHRlZElkPUEwOTUyNTc4MVpaOVpWNFVET1c3RiZlbmNyeXB0ZWRBZElkPUEwNzgyMzEyWjZDRFVKMkZQOEhZJndpZGdldE5hbWU9c3BfZGV0YWlsMiZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU&th=1)
	- I2C address is changeable.
		- Has resistor on the back to select. Resolder to pick address.
	- Default i2c address 0x72
	- Alternate i2c address 0x7A
	- Larger and taller display!

### Conclusion

The Frienda model is a great choice. With both selectable i2c address and a lower cost we would be able to have a large time display with two screens per final product.

- We are able to draw the time large and 
- Low cost!
- Unfortunately no RGB support.


Options on Mouser may be better manufactured and more reliable. However the cheap cost of 10 displays for the same price (or even under) as a oled display on Mouser. The two extra displays should make up for any defects. Hopefully amazon shipping won't let us down.

**tldr;** My suggestion is to go with the Frienda. Use 2 screens per device. If you accept order 1 of devices below.

- [Frienda-Serial-128x64](https://www.amazon.com/dp/B08VNNCLHD/ref=sspa_dk_detail_0?spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEyV1dEVVhUUFdWOUwzJmVuY3J5cHRlZElkPUEwOTUyNTc4MVpaOVpWNFVET1c3RiZlbmNyeXB0ZWRBZElkPUEwNzgyMzEyWjZDRFVKMkZQOEhZJndpZGdldE5hbWU9c3BfZGV0YWlsMiZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU&th=1)
