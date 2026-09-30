# Stage 2 — Project Requirements

## Project
Software-Only Smart-Meter Pulse Counter and Analytics System

## Purpose
Build an educational Linux project that simulates electricity-meter pulses and processes them without physical meter hardware.

## Functional requirements
- FR-1: A Linux kernel module provides a virtual smart-meter device.
- FR-2: The virtual device produces or reports simulated pulse readings.
- FR-3: A C++ application reads data from the virtual device using Linux system programming.
- FR-4: The application converts pulses to energy using a configurable pulses-per-kWh value.
- FR-5: The application displays pulse counts and calculated energy.
- FR-6: The application identifies readings above a configurable usage threshold.
- FR-7: The application saves timestamped readings to a CSV file.
- FR-8: The project includes instructions to build, run, and demonstrate the software.

## Non-functional requirements
- NFR-1: The project runs in the Ubuntu Linux virtual machine.
- NFR-2: The code is organized into clear driver, application, documentation, and data areas.
- NFR-3: The program reports invalid input and device errors clearly.
- NFR-4: The project uses Git to record development milestones.
- NFR-5: The project is software-only and does not require a physical meter.
- NFR-6: The project is an educational prototype, not a billing or safety-critical system.

## Main modules
- Virtual meter driver: simulates and exposes meter readings.
- C++ reader: opens and reads from the virtual device.
- Analytics: converts pulses to energy and checks thresholds.
- CSV storage: records readings for later review.
- Documentation: records requirements, design, progress, tests, and presentation material.

## Scope boundaries
Included: simulated readings, Linux device-driver concepts, C++ system programming, energy calculations, a basic alert, and CSV output.

Excluded: physical meter connections, electrical control, cloud services, mobile apps, and real billing.

## Deliverables
- Linux kernel module source and build instructions.
- C++ application source.
- Project documentation for all six stages.
- Architecture and UML diagrams.
- Test evidence and sample CSV output.
- Git history showing project milestones.
- Final demonstration and presentation.
