#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <unistd.h>

int main(int argc, char* argv[])
{
    unsigned long long pulsesPerKwh = 1000;

    if (argc > 2) {
        std::cerr << "Usage: " << argv[0] << " [pulses-per-kWh]\n";
        return 1;
    }

    if (argc == 2) {
        try {
            std::size_t charactersUsed = 0;
            pulsesPerKwh = std::stoull(argv[1], &charactersUsed);

            if (charactersUsed != std::strlen(argv[1]) ||
                argv[1][0] == '-' ||
                pulsesPerKwh == 0) {
                std::cerr << "Pulse setting must be a positive whole number.\n";
                return 1;
            }
        } catch (...) {
            std::cerr << "Pulse setting must be a positive whole number.\n";
            return 1;
        }
    }

    int device = open("/dev/smart_meter", O_RDONLY);
    if (device == -1) {
        std::cerr << "Could not open /dev/smart_meter: "
                  << std::strerror(errno) << '\n';
        return 1;
    }

    char buffer[64] = {};
    ssize_t bytesRead = read(device, buffer, sizeof(buffer) - 1);
    int readError = errno;

    if (close(device) == -1) {
        std::cerr << "Could not close the meter device: "
                  << std::strerror(errno) << '\n';
        return 1;
    }

    if (bytesRead < 0) {
        std::cerr << "Could not read the meter device: "
                  << std::strerror(readError) << '\n';
        return 1;
    }

    if (bytesRead == 0) {
        std::cerr << "The meter device returned no reading.\n";
        return 1;
    }

    try {
        std::string pulseText(buffer, static_cast<std::size_t>(bytesRead));
        std::size_t charactersUsed = 0;
        unsigned long long pulseCount = std::stoull(pulseText, &charactersUsed);

        if (charactersUsed == 0 ||
            (charactersUsed < pulseText.size() &&
             pulseText[charactersUsed] != '\n')) {
            std::cerr << "The meter returned an invalid reading.\n";
            return 1;
        }

        double energyKwh =
            static_cast<double>(pulseCount) / pulsesPerKwh;

        std::cout << "Pulse count: " << pulseCount << '\n'
                  << "Meter setting: " << pulsesPerKwh << " pulses/kWh\n"
                  << "Energy used: " << std::fixed << std::setprecision(3)
                  << energyKwh << " kWh\n";
    } catch (...) {
        std::cerr << "The meter returned an invalid reading.\n";
        return 1;
    }

    return 0;
}
