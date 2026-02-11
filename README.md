# 🚀 UltraSense

UltraSense is a lightweight and easy-to-use ultrasonic sensor library for Arduino and ESP32.
Designed for the popular HC-SR04 sensor.

Perfect for robotics, distance measurement, obstacle avoidance, and IoT projects.

---

## ✨ Features

* 📏 Distance measurement in:

  * Centimeters
  * Millimeters
  * Inches
* 📊 Built-in averaging filter
* ⏱️ Timeout protection (prevents blocking)
* 🧠 Simple and clean API
* 🔌 Compatible with Arduino & ESP32

---

## 📦 Installation

### Option 1 – Manual

1. Download this repository as ZIP.
2. Extract to:

```
Documents/Arduino/libraries/
```

3. Restart Arduino IDE.

### Option 2 – Git

```
git clone https://github.com/YOUR_USERNAME/UltraSense.git
```

---

## 🔧 Wiring (HC-SR04)

| HC-SR04 | Arduino         |
| ------- | --------------- |
| VCC     | 5V              |
| GND     | GND             |
| TRIG    | Any Digital Pin |
| ECHO    | Any Digital Pin |

⚠️ For ESP32 use a voltage divider on ECHO (5V → 3.3V).

---

## 🛠️ Basic Example

```cpp
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
```

---

## 📐 API Reference

### Constructor

```cpp
UltraSense(uint8_t trigPin, uint8_t echoPin);
```

### Methods

| Method                 | Description                     |
| ---------------------- | ------------------------------- |
| begin()                | Initializes sensor pins         |
| readCM()               | Returns distance in centimeters |
| readMM()               | Returns distance in millimeters |
| readInches()           | Returns distance in inches      |
| readAverageCM(samples) | Returns averaged distance       |

---

## 🧪 Tested On

* Arduino Uno
* Arduino Nano
* ESP32

---

## 📜 License

MIT License

---

## 👨‍💻 Author

Created by Iwo Wolanin
Feel free to contribute or open issues.

