

#include <Arduino.h>
#include "common.h"


// Increment change time by amount. Keep to range 0 - HHMM_MAX.
void hhmm_change(int *hhmm, int change) {
  int val = (*hhmm + change);
  if (val < 0) val += HHMM_MAX;
  else if (val >= HHMM_MAX) val -= HHMM_MAX;
  *hhmm = val;
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
static ulong timeout_ticks;
static ulong timeout_seconds;

void control_setup()
{
  
}

void control_service()
{
  if (timeout_enabled && elapsed(&timeout_ticks, 1000)) {
    Serial.print("timeout seconds: ");
    Serial.println(timeout_seconds);
    if (--timeout_seconds == 0) {
      timeout_enabled = false;
      control_event(event_timeout);
    }
  }
}

void control_timeout_ms(ulong ms)
{
  if (ms == 0) {
    timeout_enabled = false;
  } else {
    timeout_seconds = 1;
    timeout_ticks = millis() + (1000 - ms);
    timeout_enabled = true;
  }
}

void control_timeout(ulong seconds) {
  if (seconds == 0) {
    timeout_enabled = false;
  } else {
    timeout_seconds = seconds;
    timeout_ticks = millis();
    timeout_enabled = true;
  }
}

int clock_hhmm = INITIAL_TIME;
int alarm_hhmm = INITIAL_ALARM;
int alarm_minutes_brighten = INITIAL_GLOW_DURATION; // Start glowing X minutes before alarm.
int alarm_seconds = INITIAL_ALARM_SECONDS; // Alarm length in seconds.
int clock_ss = 0;
int alarm_glow = 0;
int alarm_set = 1;

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
    control_timeout(ADJUST_TIMEOUT);
    break;
  case mode_adjust_clock:
    if (new_submode == submode_none) new_submode = submode_adjust_end - 1;
    if (new_submode == submode_adjust_end) new_submode = submode_none + 1;
    control_timeout(ADJUST_TIMEOUT);
    break;
  case mode_adjust_alarm:
    if (new_submode == submode_none) new_submode = submode_adjust_end - 1;
    if (new_submode == submode_adjust_end) new_submode = submode_none + 1;
    control_timeout(ADJUST_TIMEOUT);
    break;
  case mode_alarm:
    light_on(255, 255, 255, 255);
    sound_on();
    control_timeout(alarm_seconds);
    break;
  }

  // Catch Case Transitions.
  if (mode == mode_adjust_clock || mode == mode_adjust_alarm) {
    //check_alarm(); // Disabled for now.
  }
  if (mode == mode_alarm && new_mode != mode_alarm) {
    //light_off();
    light_on(255, 255, 255, 255); // Stays on after alarm.
    sound_off();
    alarm_glow = 0;
  }
  
  mode = new_mode;
  submode = new_submode;
  
  display_show();
}

void check_alarm() {
  if (alarm_set && mode != mode_adjust_alarm) {
    if (alarm_hhmm == clock_hhmm) { // Time for alarm.
      log("alrm");
      control_mode(mode_alarm);
      alarm_glow = 0;
    }
    ulong until = hhmm_minuites_until(alarm_hhmm, clock_hhmm);
    if (!alarm_glow && until < alarm_minutes_brighten) { // Start glowing of lights. Proportionally to distance.
      // Todo: Maybe do logarithmic?
      // Todo: Check every second for smoother adjust? Or possibly adjust gradually.
      // TODO
      
      alarm_glow = 1;
      light_transition(until, 0xFF, 0xFF, 0xFF);
      Serial.print("glow");
    }
  }
}

void alarm_toggle() {
  alarm_set != alarm_set;
  alarm_glow = 0;
  if (alarm_set) {
  
  } else {
    light_off();
  }
  check_alarm();
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
    /*if (alarm_set && alarm_glow && mode != mode_adjust_alarm && mode != mode_adjust_clock) {
      //ulong minutes = alarm_minutes_brighten - hhmm_minuites_until(alarm_hhmm, clock_hhmm);
      //u08 power = (minutes * ((ulong)0xFFFF / alarm_minutes_brighten) + clock_ss * ((ulong)0xFFFF / HHMM_SEC_PER_MIN / alarm_minutes_brighten)) >> 8; // 0 to 255
      //log("glow: ", minutes, " ", clock_ss, " ", power);
      //light_on(power, 0xFF, 0xFF, 0xFF);
    }*/
    #ifdef WILD_ALARM
    if (mode == mode_alarm) {
      light_random();
    }
    #endif
    
    display_show();
    break;

  case event_tick_min: // Only called Internally
    log("evt minute");
    clock_ss = 0;
    if (mode != mode_adjust_clock) { // Only adjust time when not manually setting time.
      hhmm_change(&clock_hhmm, 1);

      check_alarm();
    }

    // Update the display. May update flashing.
    display_show();
    break;
    
  case event_timeout:
    log("evt timeout");
    if (mode != mode_clock) {
      control_mode(mode_clock);
    }
    break;
    
  case event_select:
    log("evt select");
    //display_msg_next_show("event_select");
    
    switch (mode) {
    case mode_clock:
      control_mode(mode_menu, submode_menu_alarm_toggle);
      break;
    case mode_menu:
      switch (submode) {
        case submode_menu_alarm_toggle:
          alarm_toggle();
          control_mode(mode_clock);
          break;
        case submode_menu_clock:
          control_mode(mode_adjust_clock, submode_adjust_HH);
          break;
        case submode_menu_alarm:
          control_mode(mode_adjust_alarm, submode_adjust_HH);
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
      //display_msg_next_show("alarm_stopped");
      control_mode(mode_clock);
      break;
    }
    break;
        
  case event_prev:
  case event_next:
    if (event == event_next) {
      //display_msg_next_show("event_next");
    } else {
      //display_msg_next_show("event_prev");
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
        case submode_adjust_HH:
          hhmm_change(adjust_hhmm, 60 * adjust_dir);
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
      control_timeout(ADJUST_TIMEOUT); // Reset timeout.
      
      // Question: No need to update. Will update next tick?
      display_show();
      break;
    case mode_alarm:
      // TODO: Disable Alarm.
      //display_msg_next_show("alarm_stopped");
      control_mode(mode_clock);
      break;
    }
    break;

  case event_toggle:
    log("evt toggle");
    if (mode == mode_clock) {
      alarm_toggle();
      display_show();
    }
    break;

  case event_light_on:
    if (mode == mode_clock && !alarm_glow && !ENABLED(LIGHT)) {
      log("event light on");
      light_on(2);
    }
    break;
    
  case event_light_off:
    if (mode == mode_clock && !alarm_glow && ENABLED(LIGHT)) {
      log("event light off");
      light_off();
    }
    break;
  }
}
