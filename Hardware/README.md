
# Hardware Notes

Add libraries to KiCad. <https://www.samacsys.com/kicad/>

## Revisions

### v0.6.1
- Replaces standard button with actual button.

- Added buttons.
- Added AC to Main board connection. Split power lines.
- Corrected non-connected.
- Updated schematic symbols.
- Ran annotations. Components now have numbers.
- Ran ERC check.

### v0.5

- Updated 5v to 3.3v Power Supply.
- Updated Logic control for LED Display.
Use single decoder with V_IH = 1.5v. Works for 1-way control.
- Added a third digit line for alarm and colon.
- Finished buzzer circuit. Tested prototype.
- Corrected Zero Crossing Circuit to be on power line always.
- Corrected Triac Driver resistor to feedback from OUT of power triac.
- Updated symbols.
- AC System Done!
- Added Jumper to Gesture Sensor.
- Tested: Display Works fine with 3.3v. Use Either.
- Added Oscillator
- Added Varistor

### v0.4

- Schematic for LED Display.
- *Noticed LED Display needs 5v!*
- Add PIN assignments.
- Added PIN assignments for gesture sensor.

### v0.3

- Added Gesture Sensor.
- Switch to 3.3v supply. Modified resistors.
- Fix test_led. Added diode.

### v0.2

- Added LED time display.
- Added Buzzer.
- Added Test LED.
- Added Programing Header.

### v0.1

- Added PIC.
- Added AC circuit.
- Added Power supply. Use 5v supply lines.
- Added Rest button.