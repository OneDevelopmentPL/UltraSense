#include "UltraSense.h"

UltraSense::UltraSense(uint8_t trigPin, uint8_t echoPin) {
  _trigPin = trigPin;
  _echoPin = echoPin;
}

void UltraSense::begin() {
  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);
}

long UltraSense::measure() {
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);

  long duration = pulseIn(_echoPin, HIGH, 30000); // 30ms timeout
  return duration;
}

float UltraSense::readCM() {
  long duration = measure();
  return duration * 0.0343 / 2.0;
}

float UltraSense::readMM() {
  return readCM() * 10.0;
}

float UltraSense::readInches() {
  return readCM() / 2.54;
}

float UltraSense::readAverageCM(uint8_t samples) {
  float sum = 0;
  for (uint8_t i = 0; i < samples; i++) {
    sum += readCM();
    delay(10);
  }
  return sum / samples;
}

