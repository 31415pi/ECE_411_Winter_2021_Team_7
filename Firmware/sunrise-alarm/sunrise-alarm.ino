


#include "common.h"

// Pinout
// A4 (SDA), A5 (SCL) pins for I2C comunicaitons.
//const int rtc_interrupt_pin = 2;
//const int paj_interrupt_pin = 3;


void test_setup() {
  //pinMode(test_interrupt_pin, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(test_interrupt_pin), test_handler, FALLING);
}

void setup() {
  ulong started_ms, elapsed_ms;

  started_ms = millis();
  elapsed_ms = 0;
  Serial.begin(115200);
  // Wait for 200ms for Serial to connect.
  while(!Serial && (millis() - started_ms < 200)) {
    elapsed_ms = millis() - started_ms;
    if (elapsed_ms > 200)
      break; 
  }
  Serial.println("Serial Started...");

  test_setup();
  gesture_setup();
  control_setup();
  display_setup();
  display_msg_next_show("started");
}

void loop() {
  { // Simulate RTC interrupts.
    static ulong trigger = millis();
    ulong now = millis();
    long diff = now - trigger;
    if (diff >= 0) {
      trigger = now + diff + 1000;
      control_event(event_tick);
    }
  }

  gesture_service();
  control_service();
  display_service();
}
