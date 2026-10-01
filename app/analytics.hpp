#ifndef SMART_METER_ANALYTICS_HPP
#define SMART_METER_ANALYTICS_HPP

#include <stdexcept>

inline double calculateEnergy(unsigned long long pulseCount,
                              unsigned long long pulsesPerKwh)
{
    if (pulsesPerKwh == 0)
        throw std::invalid_argument("pulsesPerKwh must be greater than zero");

    return static_cast<double>(pulseCount) / pulsesPerKwh;
}

inline bool isHighUsage(double energyKwh, double thresholdKwh)
{
    return energyKwh >= thresholdKwh;
}

#endif
