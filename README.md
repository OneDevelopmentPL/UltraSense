# 🚀 UltraSense

UltraSense is a lightweight and easy-to-use ultrasonic sensor library for Arduino and ESP32.
Designed for the popular HC-SR04 sensor.

Perfect for robotics, distance measurement, obstacle avoidance, and IoT projects.

---

![OpenLibraries-Arduino](https://img.shields.io/badge/OpenLibraries--Arduino-Official_Collaboration-2ea44f)

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

### Option 1 – From library manager.

1. Enter the Library Manager.
2. Search for "UltraSense".
3. Click "Install"

### Option 2 – Manual
1. In this GitHub Page, click "Code", then "Download ZIP"
2. Go to Arduino IDE.
3. Click "Sketch", "Include library", "Add .ZIP Library".
4. Select downloaded .zip file.

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

Created by OneDevelopmentPL
Feel free to contribute or open issues.

