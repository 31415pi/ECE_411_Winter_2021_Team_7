
#include <Arduino.h>
#include "common.h"

void button_service() {
  static bool enter = 0;
  if (detect_button(&enter, pin_button_ent) == button_pressed) {
    #ifdef BUTTONS_TEST_SOUND_LIGHT
    log("enter");
    if (ENABLED(SOUND)) {
      sound_off();
    } else {
      sound_on();
    }
    #else
    control_event(event_select);
    #endif
  }
  
  static bool select = 0;
  static ulong select_ticks = 0;
  
  #ifdef BUTTONS_TEST_SOUND_LIGHT
  static int color = 0;
  switch (detect_button_repeat(&select, pin_button_sel, 500, &select_ticks)) {
  case button_pressed:
    light_on(255, 255 * !!(color & 1), 255 * !!(color & 2), 255 * !!(color & 4));
    ++color;
    break;
  case button_released:
    light_off();
    break;
  case button_repeat:
    light_random();
    break;
  }
  #else
  switch (detect_button_repeat(&select, pin_button_sel, 250, &select_ticks)) {
  case button_pressed:
  case button_repeat:
    control_event(event_next);
    break;
  }
  #endif
}
