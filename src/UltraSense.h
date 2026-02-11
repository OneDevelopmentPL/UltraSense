#ifndef ULTRASENSE_H
#define ULTRASENSE_H

#include <Arduino.h>

class UltraSense {
  public:
    UltraSense(uint8_t trigPin, uint8_t echoPin);

    void begin();
    float readCM();
    float readMM();
    float readInches();
    float readAverageCM(uint8_t samples = 5);

  private:
    uint8_t _trigPin;
    uint8_t _echoPin;

    long measure();
};

#endif

