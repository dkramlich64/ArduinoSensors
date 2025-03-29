// include the library code:
#include <LiquidCrystal.h>

// Sensor variables
int pulsePin = A0;

#define ms_per_min 60000 // 60,000 milliseconds in one second

int value=0;
unsigned long lastPulse = 0;
unsigned long currPulse;
unsigned long diff;
unsigned int bpm;


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  lcd.print("Starting Up");
  Serial.begin(9600);
}

void loop() {
  value = analogRead(pulsePin);
  if (value > 750 && value < 900) {
    currPulse = millis();
    if (currPulse - lastPulse > 200 ) {  // avoid multiple continuous values
      if (lastPulse != 0) {
        diff = currPulse - lastPulse;
        bpm = (int)(ms_per_min / diff);
        Serial.println(bpm);
        lcd.clear();
        lcd.print("BPM");
        lcd.setCursor(0, 1);
        lcd.print(bpm);
        lastPulse = currPulse;
      }
      else {
        lastPulse = currPulse;
      }
    }
  }
  delay(5); // keep arduino from running constantly
}
