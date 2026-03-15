/*
  UltraSense – Example 03: Motion Detection (polling)
  -----------------------------------------------------
  HC-SR04 jako "czujnik PIR" – wykrywanie ruchu przez
  porównanie aktualnego odczytu z dynamicznym baseline.

  Tryb polling: sprawdzasz motionDetected() samodzielnie w loop().
  Dobry gdy chcesz mieć pełną kontrolę nad logiką programu.

  Parametry beginMotionDetection():
    sensitivity [cm] – minimalna zmiana dystansu uznawana za ruch
    windowMs [ms]    – po ilu ms spokoju baseline się odświeża

  Schemat połączeń:
    HC-SR04 VCC  → 5V
    HC-SR04 GND  → GND
    HC-SR04 TRIG → pin 9
    HC-SR04 ECHO → pin 10
    LED          → pin 13 (wbudowana)
*/

#include <UltraSense.h>

UltraSense sensor(9, 10);

const int LED_PIN     = 13;
const int LED_TIME_MS = 2000; // jak długo LED świeci po wykryciu

unsigned long ledOffAt = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);

  // Czułość 6 cm, odświeżanie baseline co 700 ms spokoju
  sensor.beginMotionDetection(6.0, 700);

  Serial.println("UltraSense – Motion Detection (polling)");
  Serial.println("Kalibracja... nie ruszaj obiektów przez 3 sekundy.");
  delay(3000);
  Serial.println("Gotowy – obserwuję ruch.");
  Serial.println("-----------------------------------------");
}

void loop() {
  // WAŻNE: update() musi być wywołane w każdej iteracji loop()
  sensor.update();

  if (sensor.motionDetected()) {
    float dist = sensor.readCM();
    Serial.print("[RUCH] dystans: ");
    Serial.print(dist, 1);
    Serial.println(" cm");

    digitalWrite(LED_PIN, HIGH);
    ledOffAt = millis() + LED_TIME_MS;
  }

  // Wyłącz LED po czasie
  if (millis() >= ledOffAt) {
    digitalWrite(LED_PIN, LOW);
  }
}
