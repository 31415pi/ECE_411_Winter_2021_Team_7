
#include "common.h"

//#define DISABLE_GESTURE

#ifdef DISABLE_GESTURE
void gesture_setup() { }
void gesture_service() { }
void gesture_handler() { }
#else
#include <DFRobot_PAJ7620U2.h> // https://github.com/DFRobot/DFRobot_PAJ7620U2

typedef DFRobot_PAJ7620U2::eGesture_t gesture_t;


const int  paj_interrupt_pin = 3;

int gesture_interrupt = 0;
DFRobot_PAJ7620U2 paj(&Wire); // Default to A4 (SDA), A5 (SCL) pins for I2C comunicaitons.



void gesture_setup() {

  while (paj.begin()) {
    Serial.println("PAJ7620U2");
    delay(500);
  }
  paj.setGestureHighRate(true); // High rate is less accurate.
  
  pinMode(paj_interrupt_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(paj_interrupt_pin), gesture_handler, FALLING);
}

void gesture_check() {
  static char last =  paj.eGestureNone;
  gesture_t gesture = paj.getGesture();
  
  if (gesture != paj.eGestureNone) {
    Serial.print("gest: ");
    Serial.println(gesture);

    // eGestureRight eGestureLeft
    // eGestureUp eGestureDown
    // eGestureUp eGestureDown
    // eGestureClockwise eGestureAntiClockwise

    if (gesture == paj.eGestureUp)
      control_event(event_next);
    if (gesture == paj.eGestureDown)
      control_event(event_prev);
    if (gesture == paj.eGestureBackward && last == paj.eGestureForward)
      control_event(event_select);
    if (gesture == paj.eGestureClockwise)
      control_event(event_toggle);

    last = gesture;
  }
}

void gesture_service() {
  static ulong ticks = millis();
  if (0 && elapsed(&ticks, 100)) {
    gesture_check();
  }
  
  if (gesture_interrupt > 0) {
    --gesture_interrupt;
    Serial.println("gest interrupt");
    gesture_check();
  }
}

void gesture_handler() {
  ++gesture_interrupt;
}
#endif
