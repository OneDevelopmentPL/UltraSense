/*
  UltraSense – Example 02: Average & Speed
  -----------------------------------------
  Pokazuje uśrednianie pomiarów oraz pomiar prędkości obiektu.

  Średnia z wielu próbek eliminuje przypadkowe skoki wartości.
  getSpeed() robi dwa pomiary z przerwą i liczy cm/s:
    wartość ujemna = obiekt się ZBLIŻA
    wartość dodatnia = obiekt się ODDALA

  Schemat połączeń:
    HC-SR04 VCC  → 5V
    HC-SR04 GND  → GND
    HC-SR04 TRIG → pin 9
    HC-SR04 ECHO → pin 10
*/

#include <UltraSense.h>

UltraSense sensor(9, 10);

void setup() {
  Serial.begin(9600);
  sensor.begin();
  Serial.println("UltraSense – Average & Speed");
  Serial.println("-----------------------------");
}

void loop() {
  // Średnia z 7 próbek (domyślnie 5)
  float avgCM = sensor.readAverageCM(7);

  // Prędkość: dwa pomiary z przerwą 80 ms
  float speed = sensor.getSpeed(80);

  if (sensor.isOutOfRange()) {
    Serial.println("Brak obiektu w zasięgu");
  } else {
    Serial.print("Średnia: ");
    Serial.print(avgCM, 1);
    Serial.print(" cm  |  Prędkość: ");
    Serial.print(speed, 1);
    Serial.print(" cm/s");

    if (speed < -2.0) {
      Serial.print("  << zbliża się");
    } else if (speed > 2.0) {
      Serial.print("  >> oddala się");
    } else {
      Serial.print("  -- stoi w miejscu");
    }

    Serial.println();
  }

  delay(300);
}
