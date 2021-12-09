
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "common.h"

Adafruit_NeoPixel pixels(cnt_neo_pixels, pin_neo_pixels, NEO_GRB + NEO_KHZ800);


static ulong light_ticks = 0;
static ulong light_delay_ms = 1000;
static ulong light_br = 0;
static uint32_t light_color = 0;

void light_service() {
  if (ENABLED(LIGHT_TRANSITION) && elapsed(&light_ticks, light_delay_ms)) {
    ++light_br;
    log("glow: ", light_br);
    pixels.setBrightness(light_br);
    for (int i = 0; i < cnt_neo_pixels; ++i) {
      pixels.setPixelColor(i, light_color);
      pixels.show();
    }
    if (light_br == 255) ENABLED_CLR(LIGHT_TRANSITION);
  }
}

void light_transition(ulong seconds, u08 r, u08 g, u08 b) {
  log("lights: transition");
  light_ticks = millis();
  light_delay_ms = (seconds * HHMM_SEC_PER_MIN * 1000) / 256;
  light_br = 0;
  light_color = pixels.Color(r, g, b);
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
