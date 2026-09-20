# Smart Dustbin

A contactless, automatic dustbin built with an Arduino, an ultrasonic sensor and a servo motor. Wave your hand in front of the bin and the lid opens on its own, stays open for five seconds, then closes.

![Smart Dustbin](images/smart-dustbin.jpg)

## Why

Touching a bin lid is the least hygienic part of throwing something away. This project removes that step entirely with about ₹700 of parts and 60 lines of code.

## How it works

An HC-SR04 ultrasonic sensor mounted on the front of the bin measures the distance to whatever is in front of it, roughly five times a second. When that distance drops to 20 cm or less, the Arduino drives an SG90 servo from 0° to 90°, which lifts the lid. After five seconds the servo returns to 0° and the sketch waits two more seconds before it starts watching again.

Full walkthrough in [docs/WORKING.md](docs/WORKING.md).

## Hardware

| Component | Qty |
|---|---|
| Arduino Uno R3 | 1 |
| HC-SR04 ultrasonic sensor | 1 |
| SG90 micro servo | 1 |
| Plastic dustbin with a hinged lid | 1 |
| Jumper wires, 9V battery or USB power | — |

Full list with specs and prices: [components/COMPONENT_LIST.md](components/COMPONENT_LIST.md).

## Wiring

| Arduino pin | Connects to |
|---|---|
| 9 | HC-SR04 TRIG |
| 10 | HC-SR04 ECHO |
| 6 | Servo signal (orange) |
| 5V | HC-SR04 VCC, servo VCC (red) |
| GND | HC-SR04 GND, servo GND (brown) |

Diagram and assembly notes: [docs/CONNECTION_DIAGRAM.md](docs/CONNECTION_DIAGRAM.md).

## Getting started

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Wire the circuit as above.
3. Open `src/Smart_Dustbin.ino`.
4. Select **Tools → Board → Arduino Uno** and pick the right port.
5. Upload, then open the Serial Monitor at **9600 baud** to watch distance readings.

## Tuning

The three constants at the top of the sketch are the ones worth changing:

```cpp
const int openAngle  = 90;   // how far the lid swings open
const int closeAngle = 0;    // resting position
const int detectDistance = 20; // trigger range in cm
```

If the lid does not close fully, adjust `closeAngle` a few degrees at a time rather than forcing the servo horn.

## Repository layout

```
src/          Arduino sketch
docs/         Wiring, working principle, full project write-up
hardware/     Circuit and wiring diagrams
components/   Bill of materials
images/       Build photos
video/        Demo link
```

## License

MIT — see [LICENSE](LICENSE).
