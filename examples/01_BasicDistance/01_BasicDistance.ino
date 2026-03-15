/*
  UltraSense – Example 01: Basic Distance
  ----------------------------------------
  Najprostszy przykład: odczyt odległości w CM, MM i calach
  co 500 ms z obsługą braku odczytu (poza zasięgiem).

  Schemat połączeń:
    HC-SR04 VCC  → 5V
    HC-SR04 GND  → GND
    HC-SR04 TRIG → pin 9
    HC-SR04 ECHO → pin 10
*/

#include <UltraSense.h>

UltraSense sensor(9, 10); // TRIG=9, ECHO=10

void setup() {
  Serial.begin(9600);
  sensor.begin();
  Serial.println("UltraSense – Basic Distance");
  Serial.println("----------------------------");
}

void loop() {
  float cm     = sensor.readCM();
  float mm     = sensor.readMM();
  float inches = sensor.readInches();

  if (sensor.isOutOfRange()) {
    Serial.println("Poza zasięgiem (> ~400 cm)");
  } else {
    Serial.print("CM: ");
    Serial.print(cm, 1);
    Serial.print("  |  MM: ");
    Serial.print(mm, 0);
    Serial.print("  |  Inches: ");
    Serial.println(inches, 2);
  }

  delay(500);
}
