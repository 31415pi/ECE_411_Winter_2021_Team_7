
#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(*arr))
typedef unsigned long ulong;


enum control_event {
  event_tick,
  event_tick_minute,
  event_timeout,
  event_menu,
  event_prev,
  event_next,
};

enum control_mode {
  mode_clock,
  mode_adjust_clock_hh,
  mode_adjust_clock_mm,
  mode_adjust_clock_am,
  mode_adjust_alarm_hh,
  mode_adjust_alarm_mm,
  mode_adjust_alarm_am,
  mode_adjust_alarm_set,
};

void control_setup();
void control_event(enum control_event event);


void test_setup();
void test_service();
void test_handler();


void gesture_setup();
void gesture_service();
void gesture_handler();


struct tick_event {
  ulong started_ms;
  ulong  tick_ms;
};

int tick_event_service(struct tick_event *t);
