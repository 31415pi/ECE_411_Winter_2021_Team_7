
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "common.h"

Adafruit_NeoPixel pixels(cnt_neo_pixels, pin_neo_pixels, NEO_GRB + NEO_KHZ800);


static ulong light_ticks = 0;
static ulong light_delay_ms = 1000;
static ulong light_br = 0;
static uint32_t light_color = 0;
static uint8_t light_r, light_g, light_b, light_morning = 0;

void light_service() {
  if (ENABLED(LIGHT_TRANSITION) && elapsed(&light_ticks, light_delay_ms)) {
    ++light_br;
    log("glow: ", light_br);
    pixels.setBrightness(light_br);
    //if (light_morning) light_color = pixels.Color(light_r, light_br < 64 ? 64 : light_br, light_br < 223 ? 0 : (((int)light_br - 223)*8 - 1));
    //if (light_morning) light_color = pixels.Color(light_r, light_br < 64 ? 64 : light_br, light_br);
    if (light_morning) light_color = pixels.Color(light_r, light_br < 64 ? 64 : light_br, light_br < 192 ? 0 : (((int)light_br-191)*4-1));
    for (int i = 0; i < cnt_neo_pixels; ++i) {
      pixels.setPixelColor(i, light_color);
      pixels.show();
    }
    if (light_br == 255) {
      ENABLED_CLR(LIGHT_TRANSITION);
      ENABLED_SET(LIGHT);
    }
  }
}

void light_transition(ulong minutes, u08 r, u08 g, u08 b) {
  log("lights: transition");
  light_ticks = millis();
  light_delay_ms = (minutes * HHMM_SEC_PER_MIN * 1000) / 256;

  light_br = 0;
  light_color = pixels.Color(r, g, b);
  light_r = r;
  light_g = g;
  light_b = b;
  light_morning = 1;
  ENABLED_SET(LIGHT_TRANSITION);
}

void light_on(ulong seconds) {
  log("lights: on slow");
  light_ticks = millis();
  light_delay_ms = (seconds * 1000) / 256;

  light_br = 0;
  light_morning = 0;
  light_color = pixels.Color(0xFF, 0xFF, 0xFF);
  ENABLED_SET(LIGHT);
  ENABLED_SET(LIGHT_TRANSITION);
}

void light_off() {
  log("lights: off");
  ENABLED_CLR(LIGHT);
  ENABLED_CLR(LIGHT_TRANSITION);
  pixels.clear();
  pixels.show();
}

void light_on(u08 brightness, u08 r, u08 g, u08 b) {
  log("lights: on");
  ENABLED_SET(LIGHT);
  uint32_t color = pixels.Color(r, g, b);
  //pixels.clear();
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
  pixels.setBrightness(0xff); //(rand() & 0xFF);
  for (int i = 0; i < cnt_neo_pixels; ++i) {
    pixels.setPixelColor(i, color);
    pixels.show();
  }
}

void light_setup() {
  pixels.begin();
  light_off();
  sound_off();
}
