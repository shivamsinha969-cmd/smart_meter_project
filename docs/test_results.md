# Stage 5 — Test Results

Date: 2026-10-01

## Manual calculation and input checks
- 30 pulses at 1000 pulses/kWh produced 0.030 kWh.
- 40 pulses at 500 pulses/kWh produced 0.080 kWh.
- 50 pulses at 1000 pulses/kWh stayed below a 0.060 kWh threshold.
- 60 pulses at 500 pulses/kWh triggered a 0.100 kWh threshold alert.
- 70 pulses at 1000 pulses/kWh triggered an alert at the exact 0.070 kWh boundary.
- Zero and non-numeric pulse settings and a zero threshold were rejected.

## Integration and system checks
- The C++ program read simulated counts from the C kernel driver and appended timestamped CSV rows.
- With the driver unloaded, the app reported that /dev/smart_meter could not be opened.
- Reloading the module recreated /dev/smart_meter.

## Remaining Stage 5 work
- Added automated unit tests for energy and threshold calculations; all six checks passed.
- Rebuilt the C++ app and confirmed exact-threshold alerting after the refactor.
