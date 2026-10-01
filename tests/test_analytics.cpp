#include "../app/analytics.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>

void check(bool passed, const char* name, int& failures)
{
    if (passed) {
        std::cout << "PASS: " << name << '\n';
    } else {
        std::cout << "FAIL: " << name << '\n';
        ++failures;
    }
}

int main()
{
    int failures = 0;

    check(std::abs(calculateEnergy(500, 1000) - 0.5) < 0.000001,
          "500 pulses at 1000 pulses/kWh equals 0.5 kWh", failures);

    check(std::abs(calculateEnergy(500, 500) - 1.0) < 0.000001,
          "500 pulses at 500 pulses/kWh equals 1.0 kWh", failures);

    check(!isHighUsage(0.050, 0.060),
          "usage below threshold does not alert", failures);

    check(isHighUsage(0.120, 0.100),
          "usage above threshold alerts", failures);

    check(isHighUsage(0.070, 0.070),
          "usage equal to threshold alerts", failures);

    bool rejectedZeroSetting = false;
    try {
        calculateEnergy(10, 0);
    } catch (const std::invalid_argument&) {
        rejectedZeroSetting = true;
    }
    check(rejectedZeroSetting,
          "zero pulses-per-kWh setting is rejected", failures);

    if (failures != 0)
        return 1;

    std::cout << "All analytics unit checks passed.\n";
    return 0;
}
