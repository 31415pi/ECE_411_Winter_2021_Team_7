

#include <Arduino.h>
#include "common.h"


#define ADJUST_TIMEOUT_MS (1000 * 10)
#define HHMM_SEC_PER_MIN 5 // 60
#define HHMM_MAX (24*60)

// Increment change time by amount. Keep to range 0 - HHMM_MAX.
void hhmm_change(int *hhmm, int change) {
  *hhmm = (*hhmm + change) % HHMM_MAX;
}

// Compute difference betwween two times.
// Should show 0 when equal.
// Should show up to HHMM_MAX-1 when not equal.
int hhmm_minuites_until(int until, int from) {
  int diff = until - from;
  if (diff < 0) diff += HHMM_MAX;
  return diff;
}






static bool timeout_enabled = false;
static ulong timeout_after_ticks;

void control_setup()
{
  mode = mode_clock;
  clock_hhmm = 0;
  alarm_hhmm = 0;
}

void control_service()
{
  if (timeout_enabled) {
    long diff = millis() - timeout_after_ticks;
    if (diff >= 0) {
      timeout_enabled = false;
      control_event(event_timeout);
    }
  }
}

void control_timeout(ulong ms)
{
  if (ms == 0) {
    timeout_enabled = false;
  } else {
    timeout_after_ticks = millis() + ms;
    timeout_enabled = true;
  }
}

int clock_hhmm = 0;
int alarm_hhmm = 0;
int clock_ss = 0;
int alarm_minutes_brighten = 20; // Start glowing X minutes before alarm.
int alarm_seconds = 60; // Alarm length in seconds.
int alarm_set = 0;

char mode = mode_clock;
char submode = submode_none;

void control_mode(char new_mode, char new_submode = submode_none)
{
  switch(new_mode) {
  case mode_clock:
    new_submode = submode_none;
    control_timeout(0);
    break;
  case mode_menu:
    if (new_submode == submode_menu_none) new_submode = submode_menu_end - 1;
    if (new_submode == submode_menu_end) new_submode = submode_menu_none + 1;
    break;
  case mode_adjust_clock:
    if (new_submode == submode_none) new_submode = submode_adjust_end - 1;
    if (new_submode == submode_adjust_end) new_submode = submode_none + 1;
    control_timeout(ADJUST_TIMEOUT_MS);
    break;
  case mode_adjust_alarm:
    if (new_submode == submode_none) new_submode = submode_adjust_end - 1;
    if (new_submode == submode_adjust_end) new_submode = submode_none + 1;
    control_timeout(ADJUST_TIMEOUT_MS);
    break;
  case mode_alarm:
    control_timeout(1000 * alarm_seconds);
    break;
  }
  
  mode = new_mode;
  submode = new_submode;
  
  display_show();
}

void control_event(enum control_event event) {
  int adjust_dir = 1;
  int *adjust_hhmm = NULL;
  
  switch (event) {
  case event_tick:
    clock_ss += 1;
    if (clock_ss > HHMM_SEC_PER_MIN) {
      clock_ss -= HHMM_SEC_PER_MIN;
      control_event(event_tick_min);
      break; // Display show handled by internal.
    }
    display_show();
    break;

  case event_tick_min: // Only called Internally
    display_msg_next_show("event_tick_minute");
    clock_ss = 0;
    if (mode != mode_adjust_clock) { // Only adjust time when not manually setting time.
      hhmm_change(&clock_hhmm, 1);

      if (alarm_set && mode != mode_adjust_alarm) {
        if (alarm_hhmm == clock_hhmm) { // Time for alarm.
          display_msg_next_show("alarm_triggered");
          control_mode(mode_alarm);
          break;
        }
        ulong until = hhmm_minuites_until(alarm_hhmm, clock_hhmm);
        if (until < alarm_minutes_brighten) { // Start glowing of lights. Proportionally to distance.
          // Todo: Maybe do logarithmic?
          // Todo: Check every second for smoother adjust? Or possibly adjust gradually.
          // TODO
          display_msg_next_show("update_brightness");
        }
      }
    }

    // Update the display. May update flashing.
    display_show();
    break;
    
  case event_timeout:
    display_msg_next_show("event_timeout");
    if (mode != mode_clock) {
      control_mode(mode_clock);
    }
    break;
    
  case event_select:
    display_msg_next_show("event_select");
    
    switch (mode) {
    case mode_clock:
      control_mode(mode_menu, submode_menu_alarm_toggle);
      break;
    case mode_menu:
      switch (submode) {
        case submode_menu_alarm_toggle:
          alarm_set = !alarm_set;
          control_mode(mode_clock);
          break;
        case submode_menu_clock:
          control_mode(mode_adjust_clock, submode_adjust_Hh);
          break;
        case submode_menu_alarm:
          control_mode(mode_adjust_alarm, submode_adjust_Hh);
          break;
        default:
          control_mode(mode_clock);
          break;
      }
      break;
    case mode_adjust_clock:
    case mode_adjust_alarm:
      if (submode + 1 >= submode_adjust_end) {
          control_mode(mode_clock);
      } else {
        control_mode(mode, submode + 1);
      }
      break;
    case mode_alarm:
      // TODO: Disable Alarm.
      display_msg_next_show("alarm_stopped");
      control_mode(mode_clock);
      break;
    }
    break;
        
  case event_prev:
  case event_next:
    if (event == event_next) {
      display_msg_next_show("event_next");
    } else {
      display_msg_next_show("event_prev");
      adjust_dir = -1; // Default is 1.
    }
    
    switch (mode) {
    case mode_menu:
      control_mode(mode_menu, submode + adjust_dir);
      break;
    case mode_adjust_clock:
    case mode_adjust_alarm:
      adjust_hhmm = (mode == mode_adjust_clock) ? &clock_hhmm : &alarm_hhmm;
      switch (submode) {
        case submode_adjust_Hh:
          hhmm_change(adjust_hhmm, 10 * 60 * adjust_dir);
          break;
        case submode_adjust_hH:
          hhmm_change(adjust_hhmm,      60 * adjust_dir);
          break;
        case submode_adjust_Mm:
          hhmm_change(adjust_hhmm,      10 * adjust_dir);
          break;
        case submode_adjust_mM:
          hhmm_change(adjust_hhmm,      1 * adjust_dir);
          break;
        case submode_adjust_am:
          hhmm_change(adjust_hhmm, 12 * 60* adjust_dir);
          break;
      }
      control_timeout(ADJUST_TIMEOUT_MS); // Reset timeout.
      
      // Question: No need to update. Will update next tick?
      display_show();
      break;
    case mode_alarm:
      // TODO: Disable Alarm.
      display_msg_next_show("alarm_stopped");
      control_mode(mode_clock);
      break;
    }
    break;
  }
}
