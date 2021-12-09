
#include <Arduino.h>
#include "common.h"

ulong sound_ticks;
ulong sound_duration;

void sound_off() {
  ENABLED_CLR(SOUND);
  noTone(pin_buzzer_pwm);
}

void sound_chirp() {
  tone(pin_buzzer_pwm, 2000, 1);
}

void sound_bom() {
  tone(pin_buzzer_pwm, 80, 20);
}

void sound_on() {
  ENABLED_SET(SOUND);
  sound_ticks = millis();
  sound_duration = 0;
}

void sound_service() {
  if (ENABLED(SOUND) && elapsed(&sound_ticks, 250)) {
    int note = hz_pentatonic();
    if (note)
      tone(pin_buzzer_pwm, hz_pentatonic(), rythem(250)); 
  }
}


// Implement different scales and rythem.

int hz_pentatonic() {
  switch (rand() % 6) {
  case 0: return 262; // C4
  case 1: return 294; // D4
  case 2: return 330; // E4
  case 3: return 392; // G4
  case 4: return 440; // A4
  default: return 0; // No Sound.
  }
}

int hz_happy() {
  switch (rand() % 10) {
  case 0: return 262; // C4
  case 1: return 294; // D4
  case 2: return 330; // E4
  case 3: return 392; // E4
  case 4: return 440; // A4
  case 5: return 440; // A4
  case 6: return 440; // A4
  case 7: return 440; // A4
  default: return 0; // No Sound.
  }
}

int hz_sad() {
  return;
}

int rythem(int base) {
  int r = rand() & 0xF;
  if (r == 15) return base >> 2;
  if (r >= 10) return base >> 1;
  return base;
}
