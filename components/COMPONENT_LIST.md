# Component List

<!-- Add images/components.jpg, then uncomment:
![Components](../images/components.jpg)
-->

## Bill of materials

| # | Component | Qty | Approx. cost (INR) | Notes |
|---|---|---|---|---|
| 1 | Arduino Uno R3 | 1 | 450 | A Nano works too; pin numbers are identical |
| 2 | HC-SR04 ultrasonic sensor | 1 | 80 | The four-pin version |
| 3 | SG90 micro servo | 1 | 120 | Comes with horns and screws |
| 4 | Jumper wires (M–F) | 10 | 40 | For sensor and servo to board |
| 5 | Plastic dustbin with hinged lid | 1 | 200 | Lighter the lid, the better |
| 6 | 9V battery + barrel connector | 1 | 60 | Or a 5V USB adapter |
| 7 | Breadboard (half size) | 1 | 70 | Optional, for shared 5V and GND rails |
| 8 | Double-sided tape / hot glue | — | 50 | Mounting |

**Approximate total: ₹1070** (₹850 if you already have a bin)

## Specifications

### Arduino Uno R3
- Microcontroller: ATmega328P
- Operating voltage: 5V
- Input voltage: 7–12V via barrel jack
- Digital I/O: 14 pins, 6 of them PWM capable
- Flash: 32 KB
- Clock: 16 MHz

### HC-SR04 ultrasonic sensor
- Operating voltage: 5V DC
- Quiescent current: ~2 mA
- Working current: ~15 mA
- Frequency: 40 kHz
- Range: 2 cm to 400 cm
- Resolution: ~3 mm
- Measuring angle: ~15°
- Trigger pulse: 10 µs TTL

### SG90 micro servo
- Operating voltage: 4.8–6V
- Stall torque: ~1.8 kg·cm at 4.8V
- Rotation: 0–180°
- Speed: ~0.1 s per 60°
- Weight: 9 g
- Current: ~10 mA idle, 100–250 mA moving

## Tools

- Computer with the Arduino IDE installed
- USB Type-B cable for uploading
- Small screwdriver
- Craft knife or drill for the sensor window
- Hot glue gun

## Substitutions

| Instead of | You can use | Caveat |
|---|---|---|
| Arduino Uno | Arduino Nano, Pro Mini | Same code, smaller footprint |
| HC-SR04 | HC-SR04P, JSN-SR04T | The SR04T is waterproof, good for outdoor bins |
| SG90 | MG90S | Metal gears, more torque, higher current draw |
| 9V battery | 5V USB adapter or power bank | Better for continuous use |
