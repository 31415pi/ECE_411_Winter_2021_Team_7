
#include "common.h"

//#define DISABLE_GESTURE
//#define GESTURE_INTERRUPT

#ifdef DISABLE_GESTURE
void gesture_setup() { }
void gesture_service() { }
void gesture_handler() { }
#else
#include "DFRobot_PAJ7620U2.h" // https://github.com/DFRobot/DFRobot_PAJ7620U2

typedef DFRobot_PAJ7620U2::eGesture_t gesture_t;


DFRobot_PAJ7620U2 paj(&Wire); // Default to A4 (SDA), A5 (SCL) pins for I2C comunicaitons.

#ifdef GESTURE_INTERRUPT
const int  paj_interrupt_pin = 3;

int gesture_interrupt = 0;
void gesture_handler() {
  ++gesture_interrupt;
}

#endif


void gesture_setup() {

  while (paj.begin()) {
    Serial.println("PAJ7620U2");
    delay(500);
  }
  paj.setGestureHighRate(true); // High rate is less accurate.

  #ifdef GESTURE_INTERRUPT
  pinMode(paj_interrupt_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(paj_interrupt_pin), gesture_handler, FALLING);
  #endif
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
    bool repeat = (gesture == last);

    if (gesture == paj.eGestureUp)
      control_event(event_next);
    if (gesture == paj.eGestureDown)
      control_event(event_prev);
    if (gesture == paj.eGestureBackward && last == paj.eGestureForward)
      control_event(event_select);
    if (gesture == paj.eGestureClockwise)// && repeat)
      control_event(event_light_on);
    if (gesture == paj.eGestureAntiClockwise)// && repeat)
      control_event(event_light_off);

    last = gesture;
  }
}

void gesture_service() {
  // Polling for gestures.
  static ulong ticks = millis();
  if (elapsed(&ticks, GESTURE_POLLING_INTERVAL_MS)) {
    gesture_check();
  }

  #ifdef GESTURE_INTERRUPT
  if (gesture_interrupt > 0) {
    --gesture_interrupt;
    Serial.println("gest interrupt");
    gesture_check();
  }
  #endif
}

#endif
