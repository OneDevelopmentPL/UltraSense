#include <UltraSense.h>

UltraSense sensor(9, 10);

void setup() {
  Serial.begin(9600);
  sensor.begin();
}

void loop() {
  float distance = sensor.readAverageCM(5);
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);
}

