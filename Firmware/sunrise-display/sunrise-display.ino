
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

int count = 0;

void setup() {
  // put your setup code here, to run once:
  while(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 connection failed");
    delay(1000);
  }
  delay(2000); // Wait for initialization.
  count = 0;
}

char display_buf_hh[] = "12";
char display_buf_mm[] = "30";
char display_buf_col[] = ":";
char display_buf_info[] = "alarm  ";

void display_time(int hhmm, int hide, bool alrm_set, bool alrm, bool tick) {
  //bool tick = 
  bool am = hhmm < 12 * 60;
  int hh = hhmm / 60 % 12;
  int mm = hhmm % 60;
  display_buf_hh[0] = '0' + hh / 10;
  display_buf_hh[1] = '0' + hh % 10;
  display_buf_mm[0] = '0' + mm / 10;
  display_buf_mm[1] = '0' + mm % 10;

  // Show display 
  oled.clearDisplay();
  oled.invertDisplay(alrm);
  oled.setTextColor(WHITE);
  
  oled.setTextSize(5);
  
  oled.setCursor(2, 2);
  oled.print(display_buf_hh);
  
  oled.setCursor(50, 2);
  oled.print(tick ? ":" : " ");
  
  oled.setCursor(68, 2);
  oled.print(display_buf_mm);

  oled.setTextSize(3);
  oled.setCursor(64 + 32 - 8 + 2, 32 + 8);
  oled.print(am ? "am" : "pm");
  
  oled.setTextSize(2);
  oled.setCursor(2, 32 + 16 - 2);
  oled.print(display_buf_info);

  oled.display();
}

// Only 10 characters per line will be displayed
void display_menu(const char *top, const char *mid, const char *bot, int sel) {
  char lines[3][11];
  strncpy(lines[0], top, 10); lines[0][10] = '\0';
  strncpy(lines[1], mid, 10); lines[1][10] = '\0';
  strncpy(lines[2], bot, 10); lines[2][10] = '\0';
  
  oled.clearDisplay();
  oled.invertDisplay(0);
  oled.setTextColor(WHITE);
  
  oled.setTextSize(2);
  oled.setCursor(4, 2); // Line 1
  oled.print(lines[0]);
  
  oled.setCursor(4, 24); // Line 2
  oled.print(lines[1]);
  
  oled.setTextColor(WHITE);
  oled.setCursor(4, 46); // Line 3
  oled.print(lines[2]);

  switch (sel) {
  case 0:
    oled.fillRect(2,  0, 128 - 4, 18, INVERSE);
    break;
  case 1:
    oled.fillRect(2, 22, 128 - 4, 18, INVERSE);
    break;
  case 2:
    oled.fillRect(2, 44, 128 - 4, 18, INVERSE);
    break;
  }

  oled.display();
}

void loop() {
  // put your main code here, to run repeatedly:

  
  
  display_time(count, 0, 1, 0, count & 1);
  display_menu("this", "is", "test", 2);

  Serial.print(count);
  Serial.println(" Displayed");
  
  delay(1000);
  
  // Set time. Warp if needed.
  if (++count > 24 * 60) count = 0;
}
