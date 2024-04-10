#include "analyzeData.h"
#include <algorithm>

std::vector<PollutionData> analyzeDataSubsetforozone(const std::vector<PollutionData>& dataSubset) {
    std::vector<PollutionData> filteredData;
    for (const auto& item : dataSubset) {
        if (item.parameter == "OZONE") {
            filteredData.push_back(item);
        }
    }
    return filteredData;
}

std::vector<PollutionData> analyzeDataSubsetforno2(const std::vector<PollutionData>& dataSubset) {
    std::vector<PollutionData> filteredData;
    for (const auto& item : dataSubset) {
        if (item.parameter == "NO2") {
            filteredData.push_back(item);
        }
    }
    return filteredData;
}

std::vector<PollutionData> analyzeDataSubsetforso2(const std::vector<PollutionData>& dataSubset) {
    std::vector<PollutionData> filteredData;
    for (const auto& item : dataSubset) {
        if (item.parameter == "SO2") {
            filteredData.push_back(item);
        }
    }
    return filteredData;
}

std::vector<PollutionData> analyzeDataSubsetforpm(const std::vector<PollutionData>& dataSubset) {
    std::vector<PollutionData> filteredData;
    for (const auto& item : dataSubset) {
        if (item.parameter == "PM2.5") {
            filteredData.push_back(item);
        }
    }
    return filteredData;
}

std::vector<PollutionData> analyzeDataSubsetforpm10(const std::vector<PollutionData>& dataSubset) {
    std::vector<PollutionData> filteredData;
    for (const auto& item : dataSubset) {
        if (item.parameter == "PM10") {
            filteredData.push_back(item);
        }
    }
    return filteredData;
}

std::vector<PollutionData> analyzeDataSubsetforco(const std::vector<PollutionData>& dataSubset) {
    std::vector<PollutionData> filteredData;
    for (const auto& item : dataSubset) {
        if (item.parameter == "CO") {
            filteredData.push_back(item);
        }
    }
    return filteredData;
}

