
#include <Arduino.h>
#include "common.h"

// Provides a fixed width print.
static void Serial_print(ulong value);

static char events[100] = "";
static char display_buf[] = "00:00 am*";

void display_setup()
{

}

void display_service()
{
  
}

void display_update(const char *msg)
{
  strncpy(display_buf, msg, sizeof(display_buf)-1);
}

void display_update(int hhmm)
{
  int hide = clock_ss & 1;
  int HH = hhmm / 60;
  int mm = hhmm % 60;
  int hh = HH % 12;

  display_buf[0] = '0' + (hh / 10);
  display_buf[1] = '0' + (hh % 10);
  display_buf[2] = ':';
  display_buf[3] = '0' + (mm / 10);
  display_buf[4] = '0' + (mm % 10);
  display_buf[5] = ' ';
  display_buf[6] = HH < 12 ? 'a' : 'p';
  display_buf[7] = 'm';
  display_buf[8] = alarm_set ? '*' : ' ';

  if (hide) switch (submode) {
  case submode_none:
    // TODO: Check clock mode?
    display_buf[2] = ' '; // Hide Colon
    break;
  case submode_adjust_Hh:
    display_buf[0] = ' ';
    break;
  case submode_adjust_hH:
    display_buf[1] = ' ';
    break;
  case submode_adjust_Mm:
    display_buf[3] = ' ';
    break;
  case submode_adjust_mM:
    display_buf[4] = ' ';
    break;
  case submode_adjust_am:
    display_buf[6] = ' ';
    break;
  }
}

int display_msg_next_show(const char *msg)
{
  int len = strlen(events);
  if (len + strlen(msg) + 1 < sizeof(events)) {
    if (len > 0) strcat(&events[len], ",");
    strcat(&events[len], msg);
    return 0;
  }
  return 1;
}


// Provides a fixed width print.
static void Serial_print(ulong value) {
  ulong test = 10;
  for (ulong i = 1; i < 10; ++i, test *= 10) {
    if (value < test) Serial.print(' ');
  }
  Serial.print(value);
}

void display_show()
{ 
  if (mode == mode_menu) {
    switch (submode) {
    case submode_menu_alarm_toggle:
      display_update(alarm_set ? "off alarm" : "on  alarm");
      break;
    case submode_menu_clock:
      display_update("set clock");
      break;
    case submode_menu_alarm:
      display_update("set alarm");
      break;
    default:
      display_update("ERRORmenu");
      break;
    }
  } else if (mode == mode_adjust_alarm) {
    display_update(alarm_hhmm);
  } else {
    display_update(clock_hhmm);
  }
  Serial.print(display_buf);
  Serial.print("|  ");
  Serial.print((int)mode);
  Serial.print("  ");
  Serial.print((int)submode);
  Serial.print("  ");
  Serial.print((int)clock_ss);
  Serial.print("  ");
  Serial.println(events); events[0] = '\0';
}
