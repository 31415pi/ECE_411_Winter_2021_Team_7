// ECE411 Team7 -
//   Julia Filipchuk <bfilipc2@pdx.edu>
//   Maddie Klementyn <muk2@pdx.edu>
//   Jana AlHuneidi <alhuneid@pdx.edu>
//   Ashlei Brady <bashlei@pdx.edu>
// Install Libarries:
//   Adafruit SSD1306 (Use included Custom Version)
//     Adafruit GFX (Intalled as dependency)
//   Adafruit NeoPixel
//   DFRobot PAJ7620U2 (Use included Custom Version)

#include "common.h"

// Pinout
// A4 (SDA), A5 (SCL) pins for I2C comunicaitons.
//const int rtc_interrupt_pin = 2;
//const int paj_interrupt_pin = 3;

int enabled = 0;

void setup() {
  Serial.begin(115200);
 
  gesture_setup();
  control_setup();
  display_setup();
  light_setup();

  // Buttons and Pins
  pinMode(pin_buzzer_pwm, OUTPUT);
  pinMode(pin_button_ent, INPUT);
  pinMode(pin_button_sel, INPUT);
  pinMode(pin_led_prog, OUTPUT);
  pinMode(pin_led_power, OUTPUT);
}

void loop() {
  { // Simulate RTC interrupts.
    static ulong trigger = millis();
    ulong now = millis();
    long diff = now - trigger;
    if (diff >= 0) {
      trigger = now + diff + 1000;
      //control_event(event_tick);
    }
    static ulong ticks = millis();
    if (elapsed(&ticks, 1000))
      control_event(event_tick);
  }

  gesture_service();
  button_service();
  control_service();
  display_service();
  sound_service();
  light_service();
}
