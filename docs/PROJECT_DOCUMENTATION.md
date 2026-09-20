# Project Documentation

## 1. Abstract

The Smart Dustbin is a contactless waste bin that opens its own lid when a hand approaches. It uses an Arduino Uno, an HC-SR04 ultrasonic sensor and an SG90 servo motor. The goal is to remove the one hygienic weak point of an ordinary bin — the lid you have to touch — using low-cost, widely available components and a sketch short enough to read in a single sitting.

## 2. Objectives

- Detect an approaching hand without physical contact.
- Open the lid automatically and hold it open long enough for waste to be dropped in.
- Close the lid on its own so the bin is not left open.
- Keep the build under ₹1000 and buildable without soldering.

## 3. System overview

```
   Hand  ──►  HC-SR04  ──►  Arduino Uno  ──►  SG90 Servo  ──►  Lid
            (sense)         (decide)          (actuate)
```

Three stages: the sensor converts a physical distance into a pulse width, the microcontroller decides whether that distance counts as a hand, and the servo converts the decision into mechanical motion.

## 4. Hardware description

**Arduino Uno R3.** ATmega328P microcontroller, 16 MHz, 14 digital I/O pins. Chosen for its 5V logic, which matches the HC-SR04 directly, and for the size of its community and documentation.

**HC-SR04 ultrasonic sensor.** Range 2–400 cm, accuracy around 3 mm, operating voltage 5V. Uses 40 kHz sound rather than light, so unlike an IR sensor it is unaffected by ambient lighting or the colour of the object in front of it.

**SG90 micro servo.** 180° rotation, roughly 1.8 kg·cm torque at 4.8V, weighs 9 g. Enough to lift a light plastic lid, and it holds position without power being continuously varied.

Full specifications and costs are in [../components/COMPONENT_LIST.md](../components/COMPONENT_LIST.md).

## 5. Software description

The sketch is a single file, `firmware/Smart_Dustbin/Smart_Dustbin.ino`, depending only on the `Servo` library bundled with the Arduino IDE.

**Constants**

| Name | Value | Purpose |
|---|---|---|
| `trigPin` | 9 | Ultrasonic trigger output |
| `echoPin` | 10 | Ultrasonic echo input |
| `servoPin` | 6 | Servo PWM output |
| `openAngle` | 90 | Lid open position |
| `closeAngle` | 0 | Lid closed position |
| `detectDistance` | 20 | Trigger threshold in cm |

**`getDistance()`** sends the trigger pulse, times the echo with a 30 ms timeout, and returns centimetres or `-1` if no echo came back.

**`setup()`** starts serial at 9600 baud, configures the sensor pins, attaches the servo and drives the lid to the closed position, then waits a second for the servo to settle before the loop begins.

**`loop()`** takes a reading, skips the cycle on a timeout, prints the distance, and opens the lid if the reading is at or below the threshold.

The mechanism is explained line by line in [WORKING.md](WORKING.md).

## 6. Testing

| Test | Method | Expected | Result |
|---|---|---|---|
| Sensor accuracy | Ruler at 10, 20, 30, 50 cm | Within ±1 cm | Pass |
| Trigger threshold | Hand approached slowly | Lid opens at ~20 cm | Pass |
| Timeout handling | Sensor aimed at open room | `No Echo`, lid stays shut | Pass |
| Lid cycle timing | Stopwatch from open to close | ~5 s open, ~7 s total | Pass |
| Repeat triggering | Ten successive waves | Opens every time | Pass |
| Power stability | Servo actuated on USB power | No board reset | Pass with light lid |

## 7. Results

The bin reliably opens for a hand presented within about 20 cm and closes without intervention. Response is effectively immediate at the 200 ms sampling rate. Measured current draw is roughly 20 mA idle and around 150 mA during the brief servo movement, which is comfortable for a 9V battery in intermittent household use, though a USB adapter is a better choice for a bin that is used all day.

## 8. Limitations

- Blocking `delay()` calls make the sketch unresponsive while the lid is open.
- The sensor detects any object, not specifically a hand, so nearby obstacles cause repeated cycling.
- No feedback on how full the bin is.
- A 9V battery is a poor long-term power source for a servo.

## 9. Future scope

- Replace `delay()` with `millis()` timing so the bin stays responsive throughout the cycle.
- Add a second ultrasonic sensor inside the bin to measure fill level, with an LED or buzzer when it is full.
- Add an ESP8266 or ESP32 so the fill level can be reported over Wi-Fi, which is the basis of city-scale smart waste collection.
- Add a solar panel and rechargeable cell for outdoor deployment.
- Use a metal detector coil or capacitive plate for basic segregation of metallic waste.

## 10. Conclusion

The project achieves contactless operation with three inexpensive components and a sketch under seventy lines. Its main engineering lesson is in the failure handling rather than the happy path: the `-1` sentinel returned on echo timeout is what separates a bin that works from one that flaps its lid at an empty room.

## 11. References

- HC-SR04 datasheet, Elec Freaks
- Arduino Servo library reference — https://www.arduino.cc/reference/en/libraries/servo/
- Arduino `pulseIn()` reference — https://www.arduino.cc/reference/en/language/functions/advanced-io/pulsein/
- SG90 servo datasheet, TowerPro
