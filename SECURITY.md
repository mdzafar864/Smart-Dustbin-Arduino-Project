# Security Policy

This project is a self-contained Arduino sketch with no network stack, no credentials and no user data. The realistic risk surface is physical rather than digital.

## Supported versions

The latest release on `main` is the only supported version.

## Reporting a concern

Open a normal issue for anything routine. For something you would rather not disclose publicly, use GitHub's **Report a vulnerability** button under the Security tab.

## Safety notes

These matter more here than software vulnerabilities:

- Powering an SG90 from the Arduino's 5V regulator can brown out the board when the servo stalls. Use a separate 5V supply for anything heavier than a light plastic lid, with a common ground.
- Do not exceed 6V on the servo or 5.5V on the HC-SR04.
- A servo with enough torque to lift a heavy lid also has enough torque to pinch fingers. Keep `openAngle` and `closeAngle` within the lid's actual travel.
- A 9V battery wired directly to the 5V rail will destroy the sensor and the servo. It goes to the barrel jack or `VIN`, never to `5V`.

## Future scope

If the Wi-Fi reporting described in `docs/PROJECT_DOCUMENTATION.md` is ever added, this file needs a real threat model: credentials on the device, unauthenticated MQTT topics and OTA update integrity.
