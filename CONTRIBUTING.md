# Contributing

Thanks for taking an interest. This is a small hardware project, so the rules are short.

## The one rule that matters

**Anything that changes `firmware/Smart_Dustbin/Smart_Dustbin.ino` must be tested on real hardware before it is opened as a pull request.** A sketch that compiles is not a bin that works. Timing, servo travel and sensor behaviour only show up on the bench.

## Getting set up

1. Install the [Arduino IDE](https://www.arduino.cc/en/software) 2.x, or [arduino-cli](https://arduino.github.io/arduino-cli/).
2. Clone the repository.
3. Open `firmware/Smart_Dustbin/Smart_Dustbin.ino`. The folder name must stay `Smart_Dustbin` — the Arduino IDE requires the sketch folder and the `.ino` file to share a name.
4. Wire the circuit as in [docs/CONNECTION_DIAGRAM.md](docs/CONNECTION_DIAGRAM.md).
5. Upload and open the Serial Monitor at 9600 baud.

Compiling from the command line:

```bash
arduino-cli core install arduino:avr
arduino-cli lib install Servo
arduino-cli compile --fqbn arduino:avr:uno firmware/Smart_Dustbin
arduino-cli upload  --fqbn arduino:avr:uno -p /dev/ttyACM0 firmware/Smart_Dustbin
```

## Code style

- Two-space indent, no tabs.
- `camelCase` for variables and functions, as the Arduino examples do.
- Pin assignments and tuning values go in the `const int` block at the top of the sketch. Never a bare number inside `loop()`.
- Comment the *why*, not the *what*. `// half the round trip` is useful; `// divide by two` is not.
- Keep the sketch dependent only on the bundled `Servo` library. A new dependency needs a good reason and a line in the bill of materials.

## Documentation

Docs are part of the change, not a follow-up. If you alter a pin or a constant, update all three places it appears:

| File | What it holds |
|---|---|
| `README.md` | Wiring table, tuning constants |
| `docs/CONNECTION_DIAGRAM.md` | Pin map, schematic |
| `docs/PROJECT_DOCUMENTATION.md` | Constants table |

## Commits

Conventional Commits, so the changelog writes itself:

```
feat(firmware): replace blocking delays with millis() timing
fix(firmware): reject echo readings below 2 cm
docs(wiring): add separate servo supply diagram
chore(ci): pin compile-sketches to v1
```

Scopes in use: `firmware`, `hardware`, `docs`, `ci`.

## Pull requests

- Branch from `main`, one topic per branch.
- Fill in the hardware table in the PR template.
- CI must be green: the sketch compiles for Uno and Nano and passes `arduino-lint`.
- A photo or a short clip is worth a paragraph for anything mechanical.

## Good first contributions

- Rewrite `loop()` around `millis()` instead of `delay()` so the bin stays responsive.
- Add a debounce so a single slow hand does not count as two triggers.
- Add a Fritzing source file alongside the exported circuit diagram.
- Photograph the build at each assembly step for `images/`.
