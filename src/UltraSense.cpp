#include "UltraSense.h"

UltraSense::UltraSense(uint8_t trigPin, uint8_t echoPin) {
  _trigPin = trigPin;
  _echoPin = echoPin;
  _motionMode = false;
  _motionFlag = false;
  _motionCb = nullptr;
  _lastDuration = 0;
}

void UltraSense::begin() {
  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);
  _motionMode = false;
}

void UltraSense::beginMotionDetection(float sensitivity, uint16_t windowMs) {
  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);

  _motionMode = true;
  _sensitivity = sensitivity;
  _windowMs = windowMs;
  _motionFlag = false;
  _lastUpdate = millis();

  float sum = 0;
  for (uint8_t i = 0; i < 5; i++) {
    sum += readCM();
    delay(60);
  }
  _baseline = sum / 5.0;
}

long UltraSense::measure() {
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);
  _lastDuration = pulseIn(_echoPin, HIGH, 30000);
  return _lastDuration;
}

long UltraSense::readRaw() {
  return measure();
}

float UltraSense::readCM() {
  measure();
  return _lastDuration * 0.0343f / 2.0f;
}

float UltraSense::readMM() {
  return _lastDuration * 0.343f / 2.0f;
}

float UltraSense::readInches() {
  return _lastDuration * 0.0343f / 2.0f / 2.54f;
}

float UltraSense::readAverageCM(uint8_t samples) {
  float sum = 0;
  for (uint8_t i = 0; i < samples; i++) {
    sum += readCM();
    delay(60);
  }
  return sum / samples;
}

float UltraSense::readAverageMM(uint8_t samples) {
  return readAverageCM(samples) * 10.0f;
}

float UltraSense::readAverageInches(uint8_t samples) {
  return readAverageCM(samples) / 2.54f;
}

bool UltraSense::isOutOfRange() {
  return (_lastDuration == 0);
}

float UltraSense::getSpeed(uint16_t delayMs) {
  float d1 = readCM();
  unsigned long t1 = millis();

  delay(delayMs);

  float d2 = readCM();
  unsigned long t2 = millis();

  float dt = (t2 - t1) / 1000.0f;
  if (dt == 0) return 0;

  return (d2 - d1) / dt;
}

void UltraSense::onMotion(MotionCallback cb) {
  _motionCb = cb;
}

void UltraSense::setSensitivity(float cm) {
  _sensitivity = cm;
}

void UltraSense::setWindowMs(uint16_t ms) {
  _windowMs = ms;
}

void UltraSense::update() {
  if (!_motionMode) return;

  float current = readCM();

  if (isOutOfRange()) return;

  float delta = abs(current - _baseline);

  if (delta >= _sensitivity) {
    if (!_motionFlag) {
      _motionFlag = true;
      if (_motionCb != nullptr) {
        _motionCb();
      }
    }
    _lastUpdate = millis();
  } else {
    _motionFlag = false;

    if (millis() - _lastUpdate >= _windowMs) {
      _baseline = 0.8f * _baseline + 0.2f * current;
      _lastUpdate = millis();
    }
  }
}

bool UltraSense::motionDetected() {
  bool flag = _motionFlag;
  _motionFlag = false;
  return flag;
}
