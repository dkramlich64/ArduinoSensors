int pulsePin = A0;

#define ms_per_min 60000 // 60,000 milliseconds in one second

int value=0;
unsigned long lastPulse = 0;
unsigned long currPulse;
unsigned long diff;
unsigned int bpm;

void setup() {
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
        lastPulse = currPulse;
      }
      else {
        lastPulse = currPulse;
      }
    }
  }
  delay(5);
}
