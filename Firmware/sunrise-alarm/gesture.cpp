
#include "common.h"

#include <DFRobot_PAJ7620U2.h> // https://github.com/DFRobot/DFRobot_PAJ7620U2

typedef DFRobot_PAJ7620U2::eGesture_t gesture_t;

const int paj_interrupt_pin = 3;

DFRobot_PAJ7620U2 paj(&Wire); // Default to A4 (SDA), A5 (SCL) pins for I2C comunicaitons.

int gesture_interrupt = 0;

void gesture_setup() {

  while (paj.begin() != 0) {
    Serial.println("PAJ7620U2 Failed to connect.");
    delay(500);
  }
  paj.setGestureHighRate(true); // High rate is less accurate.
  
  pinMode(paj_interrupt_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(paj_interrupt_pin), gesture_handler, FALLING);
}

void gesture_service() {
  static gesture_t last =  paj.eGestureNone;
  gesture_t gesture;
  
  if (gesture_interrupt <= 0) return;
  --gesture_interrupt;
  
  gesture = paj.getGesture();

  if (gesture != paj.eGestureNone) {
    String description = paj.gestureDescription(gesture);
    display_msg_next_show("gesture");
    display_msg_next_show(description.c_str());

    if (gesture == paj.eGestureUp)
      control_event(event_next);
    if (gesture == paj.eGestureDown)
      control_event(event_prev);
    if (gesture == paj.eGestureBackward && last == paj.eGestureForward)
      control_event(event_select);

    last = gesture;
  }
}

void gesture_handler() {
  ++gesture_interrupt;
}
