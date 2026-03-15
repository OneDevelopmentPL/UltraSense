/*
  UltraSense – Example 04: Motion Detection (callback)
  ------------------------------------------------------
  Ten sam tryb motion detection co w Example 03, ale zamiast
  pollingu rejestrujemy funkcję callback – zostanie wywołana
  automatycznie przez sensor.update() w momencie wykrycia ruchu.

  Dobry gdy chcesz odseparować logikę "co robimy przy ruchu"
  od głównego loop().

  Schemat połączeń:
    HC-SR04 VCC  → 5V
    HC-SR04 GND  → GND
    HC-SR04 TRIG → pin 9
    HC-SR04 ECHO → pin 10
    Buzzer       → pin 8
    LED          → pin 13
*/

#include <UltraSense.h>

UltraSense sensor(9, 10);

const int LED_PIN    = 13;
const int BUZZER_PIN = 8;

// Ta funkcja wywoływana jest automatycznie przy każdym wykryciu ruchu
void onMotionHandler() {
  Serial.println("[CALLBACK] Wykryto ruch!");

  // Krótki dźwięk buzzera
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);

  // Mignięcie LED
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Czułość 5 cm (domyślna), okno spokoju 500 ms (domyślne)
  sensor.beginMotionDetection();

  // Rejestracja callbacka
  sensor.onMotion(onMotionHandler);

  Serial.println("UltraSense – Motion Detection (callback)");
  Serial.println("Kalibracja... nie ruszaj obiektów przez 3 sekundy.");
  delay(3000);
  Serial.println("Gotowy.");
  Serial.println("-----------------------------------------");
}

void loop() {
  // update() sprawdza ruch i w razie potrzeby woła onMotionHandler()
  sensor.update();

  // Reszta programu działa normalnie, niezależnie od czujnika
  // np. obsługa przycisków, wyświetlacza, WiFi itp.
}
