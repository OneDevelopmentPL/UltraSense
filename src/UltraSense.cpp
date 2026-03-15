#include "UltraSense.h"

// ─────────────────────────────────────────────
//  KONSTRUKTOR
// ─────────────────────────────────────────────
UltraSense::UltraSense(uint8_t trigPin, uint8_t echoPin) {
  _trigPin    = trigPin;
  _echoPin    = echoPin;
  _motionMode = false;
  _motionFlag = false;
  _motionCb   = nullptr;
  _lastDuration = 0;
}

// ─────────────────────────────────────────────
//  INIT
// ─────────────────────────────────────────────
void UltraSense::begin() {
  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);
  _motionMode = false;
}

void UltraSense::beginMotionDetection(float sensitivity, uint16_t windowMs) {
  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);

  _motionMode  = true;
  _sensitivity = sensitivity;
  _windowMs    = windowMs;
  _motionFlag  = false;
  _lastUpdate  = millis();

  // Ustal baseline – wykonaj kilka pomiarów i uśrednij
  float sum = 0;
  for (uint8_t i = 0; i < 5; i++) {
    sum += readCM();
    delay(60);
  }
  _baseline = sum / 5.0;
}

// ─────────────────────────────────────────────
//  POMIAR SUROWY (prywatny)
// ─────────────────────────────────────────────
long UltraSense::measure() {
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);
  _lastDuration = pulseIn(_echoPin, HIGH, 30000); // 30 ms timeout
  return _lastDuration;
}

// ─────────────────────────────────────────────
//  ODCZYTY
// ─────────────────────────────────────────────
long UltraSense::readRaw() {
  return measure();
}

float UltraSense::readCM() {
  long d = measure();
  return d * 0.0343f / 2.0f;
}

float UltraSense::readMM() {
  return readCM() * 10.0f;
}

float UltraSense::readInches() {
  return readCM() / 2.54f;
}

float UltraSense::readAverageCM(uint8_t samples) {
  float sum = 0;
  for (uint8_t i = 0; i < samples; i++) {
    sum += readCM();
    delay(10);
  }
  return sum / samples;
}

float UltraSense::readAverageMM(uint8_t samples) {
  return readAverageCM(samples) * 10.0f;
}

float UltraSense::readAverageInches(uint8_t samples) {
  return readAverageCM(samples) / 2.54f;
}

// ─────────────────────────────────────────────
//  ZASIĘG
// ─────────────────────────────────────────────
bool UltraSense::isOutOfRange() {
  // Ostatni wynik measure() == 0 oznacza timeout – obiekt poza ~4 m
  return (_lastDuration == 0);
}

// ─────────────────────────────────────────────
//  PRĘDKOŚĆ
// ─────────────────────────────────────────────
float UltraSense::getSpeed(uint16_t delayMs) {
  float d1 = readCM();
  unsigned long t1 = millis();

  delay(delayMs);

  float d2 = readCM();
  unsigned long t2 = millis();

  float dt = (t2 - t1) / 1000.0f; // sekundy
  if (dt == 0) return 0;

  // Wartość ujemna = obiekt się zbliża, dodatnia = oddala
  return (d2 - d1) / dt;
}

// ─────────────────────────────────────────────
//  MOTION DETECTION
// ─────────────────────────────────────────────
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

  // Ignoruj odczyty poza zasięgiem
  if (isOutOfRange()) return;

  float delta = abs(current - _baseline);

  if (delta >= _sensitivity) {
    // Wykryto ruch
    if (!_motionFlag) {
      _motionFlag = true;
      if (_motionCb != nullptr) {
        _motionCb();
      }
    }
    // Reset okna – nie aktualizuj baseline gdy coś się porusza
    _lastUpdate = millis();
  } else {
    _motionFlag = false;

    // Odśwież baseline po upłynięciu okna spokoju
    if (millis() - _lastUpdate >= _windowMs) {
      // Łagodna aktualizacja baseline (exponential moving average, α = 0.2)
      _baseline   = 0.8f * _baseline + 0.2f * current;
      _lastUpdate = millis();
    }
  }
}

bool UltraSense::motionDetected() {
  bool flag = _motionFlag;
  _motionFlag = false; // auto-kasowanie po odczycie
  return flag;
}
