# 🚗 Reverse Parking Proximity Warning System

An Arduino-based reverse parking sensor that measures the distance to obstacles behind a vehicle and provides layered visual and audible feedback — Green / Yellow / Red LEDs, an RGB NeoPixel strip, a piezo buzzer, and a live 16x2 I2C LCD readout.

Built and simulated in [Tinkercad](https://www.tinkercad.com/).

---

## 📋 Features

- **Ultrasonic distance sensing** using an HC-SR04 sensor
- **Three-zone LED indicator system**
  - 🟢 Green — object is 150cm or further away (safe)
  - 🟡 Yellow — object is between 50cm and 150cm (caution)
  - 🔴 Red — object is closer than 50cm (danger)
- **Aural warning (piezo buzzer)** — sounds continuously in the Yellow zone, with a higher-frequency warning tone in the Red zone, silent when clear
- **NeoPixel RGB strip (4 pixels)** — colour-matches the active zone, flashes red/blue alternating when an obstacle is very close
- **16x2 I2C LCD display** — shows the live distance reading and a status message in real time
- **Serial Monitor output** — logs distance readings for debugging and calibration

---

## 🔧 Components Used

| Component | Purpose |
|---|---|
| Arduino Uno | Main microcontroller |
| HC-SR04 Ultrasonic Sensor | Measures distance to nearest obstacle |
| Red / Yellow / Green LEDs | Zone status indicators |
| Piezo Buzzer | Aural proximity warning |
| NeoPixel RGB LED Strip (4x) | Ambient colour-coded feedback |
| 16x2 I2C LCD (PCF8574 backpack) | Live distance + status readout |
| 220Ω Resistors | Current-limiting for LEDs |

---

## 🔌 Pin Assignments

| Arduino Pin | Connected To |
|---|---|
| D9 | HC-SR04 Trig |
| D10 | HC-SR04 Echo |
| D5 | Red LED |
| D6 | Yellow LED |
| D7 | Green LED |
| D8 | Piezo Buzzer |
| D4 | NeoPixel Strip DIN |
| A4 (SDA) | LCD Data Line |
| A5 (SCL) | LCD Clock Line |
| 5V | HC-SR04 VCC, LED strip +5V, LCD VCC |
| GND | Shared ground rail for all components |

---

## 📐 Distance Zones and System Behaviour

| Zone | Distance | LEDs | NeoPixel Strip | Buzzer | LCD Message |
|---|---|---|---|---|---|
| Green | >= 150 cm | Green ON | Green glow | Off | "Safe: Far away" |
| Yellow | 50 cm – 150 cm | Yellow ON | Orange glow | Continuous tone | "Caution: Medium" |
| Red | < 50 cm | Red ON | Alternating red/blue flash | Rapid/high-pitched tone | "!! TOO CLOSE !!" |

---

## 💻 Code

The full Arduino sketch is in [`distance_indicator.ino`](./distance_indicator.ino).

Libraries required:
- [`Adafruit_NeoPixel`](https://github.com/adafruit/Adafruit_NeoPixel)
- [`LiquidCrystal_I2C`](https://github.com/johnrickman/LiquidCrystal_I2C)

---

## 🧪 Testing

All core functions (LED zones, buzzer tones, NeoPixel colours, LCD readout) were tested and verified — see the full **Test Plan & Results** and **Intermediate Report** included in this repository for detailed documentation, wiring schematic, and pseudocode.

---

## 📄 Documentation

- [`Intermediate_Report.docx`](./Intermediate_Report.docx) — Project scope, timeline, pseudocode, wiring schematic, test results, and supervisor approval sign-off

---

## 🚀 Getting Started

1. Wire the circuit according to the pin assignment table above (or see the wiring diagram in the Intermediate Report).
2. Open `distance_indicator.ino` in the Arduino IDE or Tinkercad.
3. Install the required libraries (`Adafruit_NeoPixel`, `LiquidCrystal_I2C`).
4. Upload the sketch to your Arduino Uno.
5. Open the Serial Monitor (9600 baud) to view live distance readings.

---

## 📜 License

This project is open for educational and personal use.
