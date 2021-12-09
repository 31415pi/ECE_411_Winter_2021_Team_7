
typedef unsigned long ulong;
typedef unsigned short u08;

template <typename T> void log(T val) {
  Serial.println(val);
}
template <typename T, typename... Types> void log(T val, Types... args) {
  Serial.print(val);
  log(args...);
}

enum { button_none, button_pressed, button_released, button_repeat };
int detect_button(bool *state, int pin);
int detect_button_repeat(bool *state, int pin, ulong delay, ulong *last);
int elapsed(ulong *ticks, long delay);
int elapsed_reset(ulong *ticks, long delay);

// Music
int hz_pentatonic();
int hz_happy();
int hz_sad();
int rythem(int base);
