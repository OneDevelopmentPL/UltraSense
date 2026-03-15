# UltraSense

A simple and intuitive Arduino library for the **HC-SR04** ultrasonic sensor.  
Supports distance readings in CM / MM / inches, object speed measurement, and a built-in **motion detection mode** — turning your HC-SR04 into a PIR-like presence sensor.

---

## Installation

1. Download the repository as a ZIP file
2. In Arduino IDE: **Sketch → Include Library → Add .ZIP Library...**
3. Select the downloaded file

---

## Wiring

```
HC-SR04     Arduino
-------     -------
VCC    →    5V
GND    →    GND
TRIG   →    pin 9  (or any digital pin)
ECHO   →    pin 10 (or any digital pin)
```

---

## Quick Start

```cpp
#include <UltraSense.h>

UltraSense sensor(9, 10); // TRIG, ECHO

void setup() {
  Serial.begin(9600);
  sensor.begin();
}

void loop() {
  float cm = sensor.readCM();

  if (sensor.isOutOfRange()) {
    Serial.println("Out of range");
  } else {
    Serial.println(cm);
  }

  delay(500);
}
```

---

## API

### Initialization

| Method | Description |
|--------|-------------|
| `UltraSense(trigPin, echoPin)` | Constructor – provide TRIG and ECHO pin numbers |
| `begin()` | Initialize in standard mode |
| `beginMotionDetection(sensitivity, windowMs)` | Initialize in motion detection mode |

**`beginMotionDetection` parameters:**

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `sensitivity` | `float` | `5.0` | Minimum distance change [cm] to trigger motion |
| `windowMs` | `uint16_t` | `500` | Time [ms] of stillness before baseline refreshes |

---

### Distance Readings

| Method | Returns | Description |
|--------|---------|-------------|
| `readCM()` | `float` | Distance in centimeters |
| `readMM()` | `float` | Distance in millimeters |
| `readInches()` | `float` | Distance in inches |
| `readAverageCM(samples)` | `float` | Average of `samples` readings in CM (default 5) |
| `readAverageMM(samples)` | `float` | Average of `samples` readings in MM (default 5) |
| `readAverageInches(samples)` | `float` | Average of `samples` readings in inches (default 5) |
| `readRaw()` | `long` | Raw echo duration in microseconds |

---

### Range & Speed

| Method | Returns | Description |
|--------|---------|-------------|
| `isOutOfRange()` | `bool` | `true` when object is out of range (~400 cm) or no echo received |
| `getSpeed(delayMs)` | `float` | Object speed in cm/s; negative = approaching, positive = moving away; delay between measurements defaults to 50 ms |

---

### Motion Detection

> Available only after calling `beginMotionDetection()`.

| Method | Description |
|--------|-------------|
| `update()` | **Required in `loop()`** – checks for motion, fires callback, refreshes baseline |
| `motionDetected()` | Returns `true` if motion was detected since last call (auto-reset) |
| `onMotion(callback)` | Registers a function called automatically when motion is detected |
| `setSensitivity(cm)` | Change sensitivity at runtime |
| `setWindowMs(ms)` | Change stillness window at runtime |

---

## How Motion Detection Works

The HC-SR04 has no built-in motion sensing, but UltraSense simulates it:

1. **Calibration** – `beginMotionDetection()` takes several readings and establishes a **baseline** (the reference distance of the environment)
2. **Detection** – on every `update()` call, the current reading is compared to the baseline; if the difference ≥ `sensitivity` → motion detected
3. **Adaptation** – when no motion is detected for `windowMs` ms, the baseline is gently updated using **EMA** (α = 0.2), so the sensor adapts to slow environmental changes (e.g. temperature drift)
4. **Freeze** – while motion is ongoing, the baseline is not updated

```
Distance
  │        baseline ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─
  │                          ↑ motion!
  │                    ┌─────┘     └─────┐
  │────────────────────┘                 └──────
  └──────────────────────────────────────────→ time
```

---

## Examples

| Sketch | Description |
|--------|-------------|
| `01_BasicDistance` | Read CM / MM / inches with out-of-range handling |
| `02_AverageAndSpeed` | Averaged readings and object speed measurement |
| `03_MotionDetection_Polling` | PIR-like motion detection – poll `motionDetected()` in loop() |
| `04_MotionDetection_Callback` | PIR-like motion detection – automatic callback + buzzer |

---

## Practical Tips

**Sensitivity vs environment:**
- In a quiet indoor space you can set `sensitivity` to 3–4 cm
- In a place with vibrations or air movement, increase it to 8–10 cm

**Measurement speed:**
- `getSpeed(delayMs)` blocks execution for `delayMs` ms – avoid very short values if responsiveness matters
- In motion detection mode, `update()` takes ~30–50 ms per call (one HC-SR04 measurement)

**HC-SR04 limitations:**
- Range: ~2 cm – ~400 cm
- Beam angle: ~15°
- Minimum interval between measurements: ~60 ms (the library handles this internally)
- Speed of sound assumed at 343 m/s (~20°C)

---

## License

MIT License – free to use, modify and distribute.

---

## Author

[OneDevelopmentPL](https://github.com/OneDevelopmentPL)