#ifndef POLLUTION_DATA_H
#define POLLUTION_DATA_H

#include <string>

struct PollutionData {
    std::string parameter;   // Type of pollutant
    double concentration;    // Measured concentration of the pollutant
};

#endif
