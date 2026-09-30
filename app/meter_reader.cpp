#include <cerrno>
#include <cmath>
#include <cstring>
#include <ctime>
#include <filesystem>
#include <fcntl.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <system_error>
#include <unistd.h>

bool parsePositiveInteger(const char* text, unsigned long long& value)
{
    if (text[0] == '-')
        return false;

    try {
        std::size_t used = 0;
        value = std::stoull(text, &used);
        return used == std::strlen(text) && value > 0;
    } catch (...) {
        return false;
    }
}

bool parsePositiveNumber(const char* text, double& value)
{
    try {
        std::size_t used = 0;
        value = std::stod(text, &used);
        return used == std::strlen(text) &&
               std::isfinite(value) &&
               value > 0.0;
    } catch (...) {
        return false;
    }
}

bool readMeter(unsigned long long& pulseCount)
{
    int device = open("/dev/smart_meter", O_RDONLY);
    if (device == -1) {
        std::cerr << "Could not open /dev/smart_meter: "
                  << std::strerror(errno) << '\n';
        return false;
    }

    char buffer[64] = {};
    ssize_t bytesRead = read(device, buffer, sizeof(buffer) - 1);
    int readError = errno;

    if (close(device) == -1) {
        std::cerr << "Could not close the meter device: "
                  << std::strerror(errno) << '\n';
        return false;
    }

    if (bytesRead < 0) {
        std::cerr << "Could not read the meter device: "
                  << std::strerror(readError) << '\n';
        return false;
    }

    if (bytesRead == 0) {
        std::cerr << "The meter device returned no reading.\n";
        return false;
    }

    try {
        std::string text(buffer, static_cast<std::size_t>(bytesRead));
        std::size_t used = 0;
        pulseCount = std::stoull(text, &used);

        while (used < text.size() && (text[used] == '\n' || text[used] == '\r'))
            ++used;

        return used == text.size();
    } catch (...) {
        std::cerr << "The meter returned an invalid reading.\n";
        return false;
    }
}

int main(int argc, char* argv[])
{
    unsigned long long pulsesPerKwh = 1000;
    double thresholdKwh = 0.050;

    if (argc > 3) {
        std::cerr << "Usage: " << argv[0]
                  << " [pulses-per-kWh [alert-threshold-kWh]]\n";
        return 1;
    }

    if (argc >= 2 && !parsePositiveInteger(argv[1], pulsesPerKwh)) {
        std::cerr << "Pulse setting must be a positive whole number.\n";
        return 1;
    }

    if (argc == 3 && !parsePositiveNumber(argv[2], thresholdKwh)) {
        std::cerr << "Alert threshold must be a positive number.\n";
        return 1;
    }

    unsigned long long pulseCount = 0;
    if (!readMeter(pulseCount))
        return 1;

    double energyKwh =
        static_cast<double>(pulseCount) / pulsesPerKwh;
    bool highUsage = energyKwh >= thresholdKwh;

    std::time_t now = std::time(nullptr);
    std::tm localTime{};
    if (localtime_r(&now, &localTime) == nullptr) {
        std::cerr << "Could not create a timestamp.\n";
        return 1;
    }

    char timestamp[32] = {};
    if (std::strftime(timestamp, sizeof(timestamp),
                      "%Y-%m-%d %H:%M:%S", &localTime) == 0) {
        std::cerr << "Could not format the timestamp.\n";
        return 1;
    }

    std::error_code directoryError;
    std::filesystem::create_directories("data", directoryError);
    if (directoryError) {
        std::cerr << "Could not create the data folder: "
                  << directoryError.message() << '\n';
        return 1;
    }

    const std::string csvPath = "data/readings.csv";
    std::ifstream existingFile(csvPath);
    bool needsHeader = !existingFile.good();
    existingFile.close();

    std::ofstream csv(csvPath, std::ios::app);
    if (!csv) {
        std::cerr << "Could not open " << csvPath << " for writing.\n";
        return 1;
    }

    if (needsHeader)
        csv << "timestamp,pulse_count,pulses_per_kWh,energy_kWh,alert\n";

    csv << timestamp << ','
        << pulseCount << ','
        << pulsesPerKwh << ','
        << std::fixed << std::setprecision(3) << energyKwh << ','
        << (highUsage ? "HIGH_USAGE" : "normal") << '\n';

    if (!csv) {
        std::cerr << "Could not write the CSV reading.\n";
        return 1;
    }

    std::cout << "Timestamp: " << timestamp << '\n'
              << "Pulse count: " << pulseCount << '\n'
              << "Meter setting: " << pulsesPerKwh << " pulses/kWh\n"
              << "Energy used: " << std::fixed << std::setprecision(3)
              << energyKwh << " kWh\n"
              << "Alert threshold: " << thresholdKwh << " kWh\n";

    if (highUsage)
        std::cout << "ALERT: usage reached or exceeded the threshold.\n";
    else
        std::cout << "Usage is below the threshold.\n";

    std::cout << "Saved reading to " << csvPath << '\n';
    return 0;
}
