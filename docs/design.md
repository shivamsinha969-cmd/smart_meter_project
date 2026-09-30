# Stage 3 — System Design and Architecture

## Design goal
The Linux kernel module simulates a meter and exposes readings through a virtual character device. The C++ program reads the device, calculates energy, checks a threshold, and saves each reading as a CSV row.

## Architecture

```mermaid
flowchart LR
    Driver[Linux kernel module] --> Device["Virtual character device"]
    Device --> Reader["C++ system-programming reader"]
    Reader --> Analytics["Energy and threshold analytics"]
    Analytics --> Display["Terminal output"]
    Analytics --> CSV["CSV file in data/"]

