
#include <Arduino.h>

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
