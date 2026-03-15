#ifndef ULTRASENSE_H
#define ULTRASENSE_H

#include <Arduino.h>

// Callback type for motion detection
typedef void (*MotionCallback)();

class UltraSense {
  public:
    // === INIT ===
    UltraSense(uint8_t trigPin, uint8_t echoPin);

    // Standard mode
    void begin();

    // Motion detection mode
    // sensitivity  – minimalna zmiana [cm] uznawana za ruch (domyślnie 5 cm)
    // windowMs     – co ile ms odświeżać wewnętrzny odczyt bazowy (domyślnie 500 ms)
    void beginMotionDetection(float sensitivity = 5.0, uint16_t windowMs = 500);

    // === ODCZYTY ===
    float readCM();
    float readMM();
    float readInches();
    float readAverageCM(uint8_t samples = 5);
    float readAverageMM(uint8_t samples = 5);
    float readAverageInches(uint8_t samples = 5);
    long  readRaw();           // surowe mikrosekundy

    // === ZASIĘG ===
    // Zwraca true jeśli ostatni pomiar był poza zasięgiem (timeout / 0)
    bool isOutOfRange();

    // === PRĘDKOŚĆ ===
    // Zwraca prędkość obiektu w cm/s (wartość ujemna = obiekt się oddala)
    // Wykonuje dwa pomiary z przerwą delayMs [ms]
    float getSpeed(uint16_t delayMs = 50);

    // === MOTION DETECTION ===
    // Sprawdza czy wykryto ruch (polling) – wywołuj w loop()
    bool motionDetected();

    // Rejestruje callback wywoływany przez update() przy wykryciu ruchu
    void onMotion(MotionCallback cb);

    // Musi być wywoływane w loop() gdy używasz trybu motion detection
    void update();

    // Zmiana parametrów motion detection w locie
    void setSensitivity(float cm);
    void setWindowMs(uint16_t ms);

  private:
    uint8_t  _trigPin;
    uint8_t  _echoPin;

    // Tryb pracy
    bool     _motionMode;

    // Motion detection state
    float    _sensitivity;       // próg zmiany [cm]
    uint16_t _windowMs;          // okno czasowe odświeżania baseline [ms]
    float    _baseline;          // referencyjny dystans [cm]
    unsigned long _lastUpdate;   // czas ostatniego odświeżenia baseline
    bool     _motionFlag;        // ustawiana przez update(), kasowana po odczycie
    MotionCallback _motionCb;    // opcjonalny callback

    // Pomocnicze
    long measure();
    long _lastDuration;          // przechowuje wynik ostatniego measure()
};

#endif
