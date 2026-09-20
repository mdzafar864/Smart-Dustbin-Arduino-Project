# Changelog

All notable changes to this project are documented here.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/), and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Planned
- Non-blocking `millis()` timing so the bin responds during the open cycle
- Second ultrasonic sensor for fill-level detection
- ESP8266 variant reporting fill level over Wi-Fi

## [1.1.0] - 2026-09-20

### Added
- GitHub Actions: sketch compiled for Uno and Nano on every push, plus `arduino-lint` and a Markdown link check
- Issue forms, pull request template and Dependabot configuration
- `CONTRIBUTING.md`, `CODE_OF_CONDUCT.md`, `SECURITY.md`, `CHANGELOG.md`, `CITATION.cff`
- `.gitignore` and `.gitattributes` with Linguist rules so the repository reads as C++, not Markdown

### Changed
- Sketch moved from `src/` to `firmware/Smart_Dustbin/` so the folder name matches the `.ino` file, which the Arduino IDE requires in order to open it
- README restructured with badges, a specification table and a corrected repository layout

## [1.0.0] - 2026-09-19

### Added
- Initial working sketch: HC-SR04 distance sensing, 20 cm threshold, servo lid at 0°/90°, five second hold, two second cooldown
- Echo timeout handling returning `-1` so the lid does not open on a missing echo
- Documentation: working principle, connection diagram, full project write-up, bill of materials
- Circuit diagram and build photo
- MIT licence

[Unreleased]: https://github.com/USERNAME/Smart-Dustbin/compare/v1.1.0...HEAD
[1.1.0]: https://github.com/USERNAME/Smart-Dustbin/compare/v1.0.0...v1.1.0
[1.0.0]: https://github.com/USERNAME/Smart-Dustbin/releases/tag/v1.0.0
