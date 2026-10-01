# Project Progress Log

- Stage 1 complete: introduction documented and committed.
- Stage 2 complete: requirements and development plan documented and committed.
- Stage 3 in progress: system architecture and UML diagrams documented.
- Next: review and commit the design, then begin the Stage 4 prototype.

- Built the first Linux kernel module successfully.
- Loaded `smart_meter` and confirmed its kernel log message.
- Build warnings about optional BTF data and the unsigned development module did not prevent loading.
- Next: extend the driver to expose simulated meter readings.
- Built the first Linux kernel module successfully.
- Loaded `smart_meter` and confirmed its kernel log message.
- Build warnings about optional BTF data and the unsigned development module did not prevent loading.
- Next: extend the driver to expose simulated meter readings.


## Stage 4 — Simulated meter device
- Registered the virtual device at /dev/smart_meter.
- Read two simulated pulse counts: 10 and 20.
- Next: create the C++ application that reads the device and calculates energy.

## Stage 4 — C++ device reader
- Read simulated pulse counts from /dev/smart_meter using Linux system calls.
- Calculated energy using the default and a supplied pulses-per-kWh setting.
- Next: add a high-usage alert and save timestamped readings to CSV.

## Stage 4 — Prototype analytics and logging
- C++ application reads the virtual meter and calculates energy.
- Configurable pulse settings and high-usage thresholds work.
- Readings are timestamped and appended to data/readings.csv.
- Next: test normal, alert, and invalid-input cases; then improve the project.

## Stage 5 — Testing and improvement
- Manual calculation, input-validation, integration, and missing-device checks passed.
- Automated unit test for the calculation functions remains to be added.

## Stage 5 — Automated analytics unit tests
- Added shared energy and threshold functions used by both the app and unit tests.
- All six analytics unit checks passed.
- Rebuilt the app and confirmed it still reads the driver, logs CSV, and alerts at the threshold.
