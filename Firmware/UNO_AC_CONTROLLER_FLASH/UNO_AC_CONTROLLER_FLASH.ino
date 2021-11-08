
// Interrupts on digital pins 2,3
const int pin_zerox_int = 2;
const int pin_ac_en = 4;
const int apin_pot = A0;


const long half_period_us = (int) (1000000.f / (60 * 2)); // ~8.3ms / 8333us

typedef unsigned long ulong;

bool  ac_enable = true;
long  ac_enable_delay_us = half_period_us; // 0 full power
long  ac_enable_percent = 0;
long  ac_enable_raw = 0;
ulong ac_xings = 0;
ulong ac_xings_prev = 0;

void on_zerox_int() {
  ++ac_xings;
  //Serial.println("interrupt zerox"); // Don't Print.
  
  digitalWrite(pin_ac_en, LOW);

  if (ac_enable && ac_enable_delay_us < half_period_us - 200) {
    //noInterrupts();
    
    delayMicroseconds(ac_enable_delay_us); // TODO: Timer
    digitalWrite(pin_ac_en, HIGH);
    // TODO: Turn off even if no zeroxings occur after delay. Stays on 50%.
    
    //interrupts();
  }
}


#define ANALOG_MAX 1023l
void ac_update(long percent_power) {
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

void ac_measure() {
  ulong xings;
  ulong diff;
  ulong elapsed;
  ulong dt;
  static ulong t = 0;

  elapsed = millis();

  // TODO: Compute crossing rate.
  dt = elapsed - t;
  if (dt > 1000) { // Once per second.
    t += dt;

    xings = ac_xings;
    diff  = xings - ac_xings_prev;
    ac_xings_prev = xings;
  
    Serial.print(diff);
   Serial.println(" crossings");
  }
  
  
}

void setup() {
  Serial.begin(38400);
  delay(50); // Allow for serial to load.
  Serial.println("Start");
  
  // put your setup code here, to run once:
  pinMode(apin_pot, INPUT);
  pinMode(pin_ac_en, OUTPUT);
  pinMode(pin_zerox_int, INPUT_PULLUP);
  // MODE: LOW, CHANGE, RISING, FALLING 
  attachInterrupt(digitalPinToInterrupt(pin_zerox_int), on_zerox_int, FALLING);
}

int pot_value = 0;
void loop() {
  long val;
  
  val = analogRead(apin_pot);
  if (val != pot_value) {
    pot_value = val;
    ac_update(pot_value);
  }

  delay(25);
  ac_measure();
  
}
