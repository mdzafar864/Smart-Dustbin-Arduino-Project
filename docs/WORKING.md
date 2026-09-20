# Working Principle

## The idea in one line

Measure how far away the nearest object is; if it is close enough to be a hand, swing the lid open for five seconds.

## How the HC-SR04 measures distance

The sensor has a transmitter and a receiver. Sending a 10 microsecond HIGH pulse to TRIG makes it emit eight 40 kHz bursts. The ECHO pin then goes HIGH and stays HIGH until the reflected sound comes back, so the width of that pulse is the round-trip flight time.

```cpp
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH, 30000);
```

`pulseIn` measures that width in microseconds. Converting it to centimetres:

```cpp
return duration * 0.0343 / 2;
```

Sound travels about 343 m/s, which is 0.0343 cm per microsecond. The division by two is because the burst travelled to the object and back, and only half that path is the distance we want.

The `30000` passed to `pulseIn` is a timeout. Without it, a burst that never returns — nothing in range, or a soft or angled surface that scatters the sound — would block the sketch. Thirty milliseconds corresponds to roughly five metres, well past the sensor's useful range. On timeout `pulseIn` returns 0, and `getDistance()` converts that to `-1` as a sentinel:

```cpp
if (duration == 0) {
  return -1;
}
```

## Why `-1` matters

Without that check, a timeout would compute a distance of 0 cm, which is less than the 20 cm threshold, and the lid would flap open every time the sensor saw nothing at all. The main loop bails out early on a negative reading:

```cpp
if (distance < 0) {
  Serial.println("No Echo");
  delay(200);
  return;
}
```

## The decision

```cpp
if (distance <= detectDistance && distance > 0) {
  lidServo.write(openAngle);   // 0° → 90°
  delay(5000);                 // stay open
  lidServo.write(closeAngle);  // back to 0°
  delay(2000);                 // cooldown
}
```

The five second hold is generous on purpose — long enough to drop something in without the lid closing on your hand. The two second cooldown afterwards stops the bin from immediately re-triggering on the arm that is still withdrawing.

At the end of every pass, open or not, there is a `delay(200)`. That sets the sampling rate to about five readings per second, which is responsive enough for a hand but slow enough that consecutive ultrasonic bursts do not interfere with each other.

## Timing summary

| Phase | Duration |
|---|---|
| Idle sampling interval | 200 ms |
| Lid held open | 5000 ms |
| Cooldown after closing | 2000 ms |
| Total cycle once triggered | ~7.2 s |

## Flow

```
        ┌─────────────────┐
        │  Measure range  │
        └────────┬────────┘
                 ↓
         ┌───────────────┐   yes   ┌──────────────────┐
         │  Echo timed   ├────────►│ Print "No Echo"  │
         │     out?      │         │  wait 200 ms     │
         └───────┬───────┘         └────────┬─────────┘
                 │ no                       │
                 ↓                          │
         ┌───────────────┐   no             │
         │ distance ≤ 20 ├──────────┐       │
         │      cm?      │          │       │
         └───────┬───────┘          │       │
                 │ yes              │       │
                 ↓                  │       │
        ┌─────────────────┐         │       │
        │ Servo → 90°     │         │       │
        │ hold 5 s        │         │       │
        │ Servo → 0°      │         │       │
        │ wait 2 s        │         │       │
        └────────┬────────┘         │       │
                 │                  │       │
                 └──────────────────┴───────┘
                          ↓
                    (loop repeats)
```

## Known limitations

- **Blocking delays.** While the lid is open the sketch does nothing else. That is fine here, but it means the bin cannot respond to a second person during those seven seconds. Rewriting the loop around `millis()` instead of `delay()` would fix it and is the natural next upgrade.
- **The sensor cannot tell a hand from a wall.** Anything parked within 20 cm holds the bin in a repeating open/close cycle. Keep the bin clear of furniture.
- **Soft or angled surfaces absorb the burst.** A sleeve or a loose cloth may read as `No Echo`. An open palm works best.
- **Temperature affects the speed of sound.** The constant 0.0343 assumes about 20°C. At 40°C the real figure is nearer 0.0355, an error of roughly 3% — about 0.6 cm at the trigger threshold, which does not matter for this application.
