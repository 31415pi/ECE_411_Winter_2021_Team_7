
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>
#include "Adafruit_SSD1306.h"

#include "common.h"

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

void display_setup()
{
  while(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306");
    delay(500);
  }
  //delay(2000); // Wait for initialization.
}

void display_service()
{
  
}

void display_time(int hhmm, bool tick) {
  char display_buf_hh[] = "12";
  char display_buf_col[] = ":";
  char display_buf_mm[] = "30";
  char display_buf_am[] = "am";
  char display_buf_info[] = "alarm  ";
  
  bool am = hhmm < 12 * 60;
  int hh = (hhmm / 60) % 12; if (hh == 0) hh = 12;
  int mm = hhmm % 60;
  int invert = 0;
  display_buf_hh[0] = '0' + hh / 10;
  display_buf_hh[1] = '0' + hh % 10;
  display_buf_mm[0] = '0' + mm / 10;
  display_buf_mm[1] = '0' + mm % 10;
  display_buf_am[0] = am ? 'a' : 'p';
  if (!alarm_set) display_buf_info[0] = '\0';
  
  if (tick) switch (submode) {
  case submode_none:
    // TODO: Check clock mode?
    display_buf_col[0] = ' '; // Hide Colon
    break;
  case submode_adjust_HH:
    display_buf_hh[0] = ' ';
    display_buf_hh[1] = ' ';
    break;
  case submode_adjust_Mm:
    display_buf_mm[0] = ' ';
    break;
  case submode_adjust_mM:
    display_buf_mm[1] = ' ';
    break;
  case submode_adjust_am:
    display_buf_am[0] = ' ';
    break;
  }

  // Show display 
  oled.clearDisplay();
  oled.invertDisplay((mode == mode_alarm) && tick);
  oled.setTextColor(WHITE);
  
  oled.setTextSize(5, 3);
  
  oled.setCursor(2, 2/2);
  oled.print(display_buf_hh);
  
  oled.setCursor(50, 2/2);
  oled.print(display_buf_col);
  
  oled.setCursor(68, 2/2);
  oled.print(display_buf_mm);

  oled.setTextSize(3);
  oled.setCursor(64 + 32 - 8 + 2, 40/2+2);
  oled.print(display_buf_am);
  
  oled.setTextSize(2);
  oled.setCursor(2, 46/2+4);
  oled.print(display_buf_info);

  oled.display();
}

void display_line(const char *line) {
  oled.clearDisplay();
  oled.invertDisplay(0);
  oled.setTextColor(WHITE);

  oled.setTextSize(2);
  oled.setCursor(4, 24/2); // Line 2
  oled.print(line);
  
  oled.display();
}

void display_show()
{ 
  if (mode == mode_menu) {
    switch (submode) {
    case submode_menu_alarm_toggle:
      //display_update(alarm_set ? "off alarm" : "on  alarm");
      //display_menu("** Menu **", "alarm on", "alarm off", alarm_set ? 2 : 1);
      //display_menu("", "alarm on", "alarm off", alarm_set ? 2 : 1);
      display_line(alarm_set ? "alarm off" : "alarm on");
      break;
    case submode_menu_clock:
      //display_update("set clock");
      //display_menu("", "set clock", "", 2);
      display_line("set clock");
      break;
    case submode_menu_alarm:
      //display_update("set alarm");
      //display_menu("", "set alarm", "", 2);
      display_line("set alarm");
      break;
    }
  } else if (mode == mode_adjust_alarm) {
    //display_update(alarm_hhmm);
    display_time(alarm_hhmm, clock_ss & 1);
  } else { // mode_clock/mode_alarm
    //display_update(clock_hhmm);
    display_time(clock_hhmm, clock_ss & 1);
  }

  /*Serial.print("clock: ");
  Serial.print(clock_hhmm);
  Serial.print(" | ");
  Serial.print((int)mode);
  Serial.print("  ");
  Serial.print((int)submode);
  Serial.print("  ");
  Serial.println((int)clock_ss);//*/
}
