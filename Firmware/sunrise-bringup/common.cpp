
#include <Arduino.h>
#include "common.h"

int detect_button(bool *state, int pin) {
  int val = digitalRead(pin);
  if (val && !*state)
    return button_pressed;
  if (!val && *state)
    return button_released;
  return button_none;
}

int detect_button_repeat(bool *state, int pin, ulong delay, ulong *last) {
  int val = digitalRead(pin);
  if (val == 0) {
    if (!*state)
      return button_none;
    *state = 0;
    return button_released;
  }
  if (*state) {
    ulong now = millis();
    long diff = (long)(now - *last);
    if (diff > delay) {
      *last += diff;
      return button_repeat;
    }
    return 0;
  } else {
    *state = 1;
    *last = millis();
    return button_pressed;
  }
}

int elapsed(ulong *ticks, long delay) {
  long diff = millis() - *ticks;
  if (diff > delay) {
    *ticks += delay;
    return 1;
  }
  return 0;
}

int elapsed_reset(ulong *ticks, long delay) {
  long diff = millis() - *ticks;
  if (diff > delay) {
    *ticks += diff;
    return 1;
  }
  return 0;
}
