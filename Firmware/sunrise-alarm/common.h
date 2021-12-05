
#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(*arr))
typedef unsigned long ulong;

// Settings
extern int clock_ss;
extern int clock_hhmm;
extern int alarm_hhmm;
extern int alarm_set;
extern char mode;
extern char submode;


// Enumerates all possible control events generated by user input or system events.
enum control_event {
  event_tick,    // Second has elapsed. Used for updating flashing of the clock and time.
  event_tick_min,// Tick for each minute change.
  event_timeout, // Timeout of different control modes.
  event_select,  // Select/Menu.
  event_prev,    // Could be optional. Probably nicer to have this.
  event_next,    // Change selected value.
};

// Enumarate all possible mode states.
enum control_mode {
  mode_clock, // Only clock is displaying.
  mode_menu,  // Menu for selecting what to adjust. Uses menu submodes.
  mode_adjust_clock, // Adjust clock. Uses adjust submodes.
  mode_adjust_alarm, // Adjust alarm. Uses adjust submodes.
  mode_alarm, // Alarm is ringing.
};
enum control_submode_adjust {
  submode_none,
  submode_adjust_Hh,
  submode_adjust_hH,
  submode_adjust_Mm,
  submode_adjust_mM,
  submode_adjust_am,
  submode_adjust_end, // LAST
};
enum control_submode_menu {
  submode_menu_none,
  submode_menu_alarm_toggle,
  submode_menu_clock,
  submode_menu_alarm,
  submode_menu_end, // LAST
};

// Enumerates all possible display hide states.
enum display_hide {
  hide_none,
  hide_h_,
  hide__h,
  hide_colon,
  hide_m_,
  hide__m,
  hide_am,
  hide_alarm,
};

void display_setup();
void display_service();
int display_msg_next_show(const char *msg);
void display_update(const char *msg);
void display_update(int hhmm);
void display_show();

void control_setup();
void control_service();
void control_timeout(ulong ms);
void control_event(enum control_event event);

void gesture_setup();
void gesture_service();
void gesture_handler();
