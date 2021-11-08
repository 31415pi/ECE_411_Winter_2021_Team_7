
// Interrupts on digital pins 2,3
const int pin_zerox_int = 2;
const int pin_ac_en = 4;
const int apin_pot = A0;

const long half_period_us = (int) (1000000.f / 60 / 2); // ~8.3ms / 8333us

bool ac_enable = false;
long  ac_enable_delay_us = half_period_us; // 0 full power
long  ac_enable_percent = 0;
long  ac_enable_raw = 0;

void on_zerox_int() {
  Serial.println("interrupt zerox");
  
  digitalWrite(pin_ac_en, LOW);

  if (ac_enable && ac_enable_delay_us < half_period_us) {
    delayMicroseconds(ac_enable_delay_us);
    digitalWrite(pin_ac_en, HIGH);
  }
}

#define ANALOG_MAX 1023l
void update_ac(long percent_power) {
  ac_enable_raw = constrain(percent_power, 0, ANALOG_MAX);
  ac_enable_percent = (100 * ac_enable_raw) / ANALOG_MAX;
  ac_enable_delay_us = ((ANALOG_MAX - ac_enable_raw) * half_period_us) / ANALOG_MAX;

  Serial.print(ac_enable ? "AC: ENABLED   " : "AC: disabled  ");
  Serial.print(ac_enable_percent);
  Serial.print("%   ");
  Serial.print(ac_enable_raw);
  Serial.print("    ");
  Serial.print(ac_enable_delay_us);
  Serial.println(" us");
}

void setup() {
  // put your setup code here, to run once:
  pinMode(apin_pot, INPUT);
  pinMode(pin_ac_en, OUTPUT);
  pinMode(pin_zerox_int, INPUT_PULLUP);
  // MODE: LOW, CHANGE, RISING, FALLING 
  attachInterrupt(digitalPinToInterrupt(pin_zerox_int), on_zerox_int, FALLING);
  
  Serial.begin(38400);
  delay(50); // Allow for serial to load.
  Serial.println("Start");
}

int pot_value = 0;
void loop() {
  long val = analogRead(apin_pot);
  if (val != pot_value) {
    pot_value = val;
    update_ac(pot_value);
  }
  
  delay(100);
}
