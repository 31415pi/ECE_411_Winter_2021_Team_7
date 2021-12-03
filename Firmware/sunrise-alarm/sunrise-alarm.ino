

#include <DFRobot_PAJ7620U2.h> // https://github.com/DFRobot/DFRobot_PAJ7620U2

#include "common.h"

typedef DFRobot_PAJ7620U2::eGesture_t gesture_t;


const int test_interrupt_pin = 2;
const int paj_interrupt_pin = 3;


DFRobot_PAJ7620U2 paj(&Wire); // Default to A4 (SDA), A5 (SCL) pins for I2C comunicaitons.




int tick_event_service(struct tick_event *t) {
  if (t->started_ms - millis() > t->tick_ms) {
    t->started_ms += t->tick_ms;
    return 1;
  }
  return 0;
}



int test_interrupt = 0;

void test_setup() {
  pinMode(test_interrupt_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(test_interrupt_pin), test_handler, FALLING);
}

void test_service() {
  if (test_interrupt) {
    test_interrupt = 0;

    Serial.println("Interrupt occured");
  }
}
void test_handler() {
  test_interrupt = 1;
}



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
  gesture_t gesture;
  
  if (gesture_interrupt <= 0) return;
  --gesture_interrupt;
  
  gesture = paj.getGesture();

  if (gesture != paj.eGestureNone) {
    String description = paj.gestureDescription(gesture);
    Serial.print(millis());
    Serial.print(" gesture ");
    Serial.println(description);


    if (gesture == paj.eGestureUp) 
      control_event(event_next);
    if (gesture == paj.eGestureDown)
      control_event(event_prev);
    if (gesture == paj.eGestureBackward)
      control_event(event_menu);
    //delay(10);
    //goto repeat;
  }
}

void gesture_handler() {
  ++gesture_interrupt;
  //Serial.println("Gesture int");
}





enum control_mode mode;
int clock_ss = 0;
int clock_hhmm = 0;
int alarm_hhmm = 0;
int alarm_set = 0;
char time_display[10] = "00:00 am*";

enum enum_hide {
  hide_none  = 0x00,
  hide_hh    = 0x01,
  hide_mm    = 0x02,
  hide_am    = 0x04,
  hide_alarm = 0x08,
  hide_colon = 0x10,
};

enum enum_hide display_hide = hide_colon;

void time_inc(int *hhmm, int change) {
  *hhmm = (*hhmm + change) % (24 * 60);
}

void show_time(int hhmm, int hide) {
  int HH = hhmm / 60;
  int mm = hhmm % 60;
  int hh = HH % 12;
  char buf[10] = "00:00 am*";
  
  buf[0] = '0' + (hh / 10);
  buf[1] = '0' + (hh % 10);
  buf[3] = '0' + (mm / 10);
  buf[4] = '0' + (mm % 10);
  buf[6] = HH < 12 ? 'a' : 'p';
  buf[8] = alarm_set ? '*' : ' ';
  
  switch (hide) {
  case hide_hh:
    buf[0] = ' ';
    buf[1] = ' ';
    break;
  case hide_colon:
    buf[2] = ' ';
    break;
  case hide_mm:
    buf[3] = ' ';
    buf[4] = ' ';
    break;
  case hide_am:
    buf[6] = ' ';
    buf[7] = ' ';
    break;
  case hide_alarm:
    buf[8] = ' ';
    break;
  }

  Serial.print(buf);
}

void Serial_print(ulong value) {
  ulong test = 10;
  for (ulong i = 1; i < 10; ++i, test *= 10) {
    if (value < test) Serial.print(' ');
  }
  Serial.print(value);
}
void show_all() {
  Serial_print(millis());
  Serial.print("  ");
  Serial.print(mode);
  Serial.print("  ");
  show_time(clock_hhmm, (clock_ss & 1) ? hide_none : display_hide);
  Serial.println();
}


void control_setup() {
  mode = mode_clock;
  clock_hhmm = 0;
  alarm_hhmm = 0;
}

void control_event(enum control_event event) {
  int adjust_dir = 1;
  enum control_mode next_mode = mode;
  
  switch (event) {
  case event_tick:
    clock_ss += 1;
    if (clock_ss > 10) {
      clock_ss -= 10;
      time_inc(&clock_hhmm, 1);
    }
    break;
    
  case event_timeout:
    if (mode != mode_clock) {
      next_mode = mode_clock;
    }
    break;
    
  case event_menu:
    Serial.println("event menu");
    if (mode == mode_clock) {
      next_mode = mode_adjust_clock_hh;
    } else if (mode == mode_adjust_clock_hh) {
      next_mode = mode_adjust_clock_mm;
    } else if (mode == mode_adjust_clock_mm) {
      next_mode = mode_adjust_clock_am;
    } else if (mode == mode_adjust_clock_am) {
      next_mode = mode_clock;
    } else {
      next_mode = mode_clock;
    }
    break;
    
  case event_prev:
    adjust_dir = -1; // Default is 1.
  case event_next:
    switch (mode) {
    case mode_adjust_clock_hh:
      time_inc(&clock_hhmm, adjust_dir * 60);
      break;
    case mode_adjust_clock_mm:
      time_inc(&clock_hhmm, adjust_dir *  1);
      break;
    case mode_adjust_clock_am:
      time_inc(&clock_hhmm,  12 * 60);
      break;
    }
    break;
  }

  if (next_mode != mode) switch(mode = next_mode) {
  case mode_clock:
    display_hide = hide_colon;
    break;
  case mode_adjust_clock_hh:
    display_hide = hide_hh;
    break;
  case mode_adjust_clock_mm:
    display_hide = hide_mm;
    break;
  case mode_adjust_clock_am:
    display_hide = hide_am;
    break;
  case mode_adjust_alarm_hh:
    display_hide = hide_hh;
    break;
  case mode_adjust_alarm_mm:
    display_hide = hide_mm;
    break;
  case mode_adjust_alarm_am:
    display_hide = hide_am;
    break;
  case mode_adjust_alarm_set:
    display_hide = hide_alarm;
    break;
  }
  
  show_all();
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
  
}

void loop() {
  static struct tick_event tick_second = { millis(),      1000 };

  test_service();
  gesture_service();
  
  if (tick_event_service(&tick_second)) {
    control_event(event_tick);
  }
}
