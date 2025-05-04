#include <Encoder.h>

const int encoderPin = 34;
Encoder encoder(20);

void IRAM_ATTR encoderISR() {
  encoder.addTick();
  unsigned long lastTickTime = encoder.getTimestamp(); 
  encoder.setTimestamp(micros());
  if (lastTickTime != 0) {
    encoder.setTickInterval(encoder.getTimestamp() - lastTickTime);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(encoderPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPin), encoderISR, RISING);
}

void loop() {
  Serial.print("Ticks: ");
  Serial.print(encoder.getTicks());
  Serial.print(" | RPM: ");
  Serial.println(encoder.getRPM());
  delay(100);
}

