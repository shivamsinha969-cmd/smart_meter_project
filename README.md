# Smart-Meter Pulse Counter and Analytics System

## Overview
This educational project uses a C Linux kernel module to simulate meter pulses and a C++ application to read them, calculate energy, check a usage threshold, and save timestamped readings to CSV. It uses no physical meter or other hardware.

## Requirements
- Ubuntu Linux with kernel headers matching the running kernel
- GCC and G++ (`build-essential`)
- Git

## Project files
- `driver/smart_meter.c` — simulated Linux character-device driver
- `driver/Makefile` — builds the driver against the running kernel
- `app/meter_reader.cpp` — reads the device and handles display, alerts, and CSV logging
- `app/analytics.hpp` — energy calculation and threshold functions
- `tests/test_analytics.cpp` — automated analytics unit checks
- `docs/` — stage documents, progress, and test results
- `data/readings.csv` — generated readings

## Build and run
From the project folder, build the driver with `make -C driver`. Load it with `sudo insmod driver/smart_meter.ko`. If you see `File exists`, it is already loaded. The device should appear at `/dev/smart_meter`.

Build the C++ application with `g++ -std=c++17 -Wall -Wextra -o app/meter_reader app/meter_reader.cpp`. Run it with `./app/meter_reader`. Optional settings are `./app/meter_reader pulses-per-kWh alert-threshold-kWh`, for example `./app/meter_reader 500 0.100`.

Readings are appended to `data/readings.csv`.

## Run the unit checks
Build with `g++ -std=c++17 -Wall -Wextra -o tests/test_analytics tests/test_analytics.cpp` and run with `./tests/test_analytics`.

## Unload the driver
Run `sudo rmmod smart_meter`.

## Limitations
Each device read adds 10 simulated pulses. The count resets when the module is unloaded. The threshold checks the calculated cumulative energy for that reading; this prototype does not measure real-time power or real electricity use. It is for learning and demonstration only.

