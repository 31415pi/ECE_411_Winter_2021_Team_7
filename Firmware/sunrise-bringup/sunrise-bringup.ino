
#include <Adafruit_NeoPixel.h>
#include "common.h"






Adafruit_NeoPixel pixels(cnt_neo_pixels, pin_neo_pixels, NEO_GRB + NEO_KHZ800);

void light_off() {
  log("lights: off");
  ENABLED_CLR(LIGHT);
  pixels.clear();
  pixels.show();
}
void light_on(u08 brightness, u08 r, u08 g, u08 b) {
  log("lights: on");
  ENABLED_SET(LIGHT);
  uint32_t color = pixels.Color(r, g, b);
  pixels.clear();
  pixels.setBrightness(brightness);
  for (int i = 0; i < cnt_neo_pixels; ++i) {
    pixels.setPixelColor(i, color);
    pixels.show();
  }
}
void light_random() {
  log("lights: rand");
  ENABLED_SET(LIGHT);
  uint32_t color = pixels.Color(rand() & 0xFF, rand() & 0xFF, rand() & 0xFF);
  pixels.clear();
  pixels.setBrightness(rand() & 0xFF);
  for (int i = 0; i < cnt_neo_pixels; ++i) {
    pixels.setPixelColor(i, color);
    pixels.show();
  }
}

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


void button_service() {
  static bool enter = 0;
  if (detect_button(&enter, pin_button_ent) == button_pressed) {
    log("enter");
    if (ENABLED(SOUND)) {
      sound_off();
    } else {
      sound_on();
    }
  }
  
  static bool select = 0;
  static ulong select_ticks = 0;
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
  if (0 && detect_button_repeat(&select, pin_button_sel, 500, &select_ticks)) {
    log("select");
    if (ENABLED(LIGHT)) {
      light_off();
    } else {
      //light_random();
    }
  }
}

// Globals.
int enabled = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(pin_buzzer_pwm, OUTPUT);
  pinMode(pin_button_ent, INPUT);
  pinMode(pin_button_sel, INPUT);

  pixels.begin();
  light_off();
  sound_off();
}

void loop() {
  button_service();
  sound_service();
  
  // put your main code here, to run repeatedly:
  static int count = 0;
  static ulong ticks = millis();
  if (elapsed(&ticks, 1000)) {
    log("count: ", ++count);
    //if (count & 1) sound_chirp();
    //else sound_bom();
  }
}
