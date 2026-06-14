#ifndef ULTRASENSE_H
#define ULTRASENSE_H

#include <Arduino.h>

typedef void (*MotionCallback)();

class UltraSense {
  public:
    UltraSense(uint8_t trigPin, uint8_t echoPin);

    void begin();

    void beginMotionDetection(float sensitivity=5.0, uint16_t windowMs = 500);

    float readCM();
    float readMM();
    float readInches();
    float readAverageCM(uint8_t samples = 5);
    float readAverageMM(uint8_t samples = 5);
    float readAverageInches(uint8_t samples = 5);
    long  readRaw();

    bool isOutOfRange();

    float getSpeed(uint16_t delayMs = 50);

    bool motionDetected();

    void onMotion(MotionCallback cb);

    void update();

    void setSensitivity(float cm);
    void setWindowMs(uint16_t ms);

  private:
    uint8_t  _trigPin;
    uint8_t  _echoPin;

    bool     _motionMode;

    float    _sensitivity;
    uint16_t _windowMs;
    float    _baseline;
    unsigned long _lastUpdate;
    bool     _motionFlag;
    MotionCallback _motionCb;

    long measure();
    long _lastDuration;
};

#endif
