#include "analyzeData.h"
#include <algorithm>
#include <iostream>

std::vector<PollutionData> analyzeDataSubsetforozone(const std::vector<PollutionData>& dataSubset) {
    std::vector<PollutionData> filteredData;
    for (const auto& item : dataSubset) {
        std::string parameter = item.parameter;
        parameter.erase(std::remove(parameter.begin(), parameter.end(), '\"'), parameter.end());

        if (parameter == "OZONE") {
            filteredData.push_back(item);
        }
    }
    return filteredData;
}

std::vector<PollutionData> analyzeDataSubsetforno2(const std::vector<PollutionData>& dataSubset) {
    std::vector<PollutionData> filteredData;
    for (const auto& item : dataSubset) {
        std::string parameter = item.parameter;
        parameter.erase(std::remove(parameter.begin(), parameter.end(), '\"'), parameter.end());

        if (parameter == "NO2") {
            filteredData.push_back(item);
        }
    }
   
    return filteredData;
}

std::vector<PollutionData> analyzeDataSubsetforso2(const std::vector<PollutionData>& dataSubset) {
    std::vector<PollutionData> filteredData;
    for (const auto& item : dataSubset) {
        std::string parameter = item.parameter;
        parameter.erase(std::remove(parameter.begin(), parameter.end(), '\"'), parameter.end());

        if (parameter == "SO2") {
            filteredData.push_back(item);
        }
    }
    return filteredData;
}

std::vector<PollutionData> analyzeDataSubsetforpm(const std::vector<PollutionData>& dataSubset) {
    std::vector<PollutionData> filteredData;
    for (const auto& item : dataSubset) {
        std::string parameter = item.parameter;
        parameter.erase(std::remove(parameter.begin(), parameter.end(), '\"'), parameter.end());

        if (parameter == "PM2.5") {
            filteredData.push_back(item);
        }
    }
    return filteredData;
}

std::vector<PollutionData> analyzeDataSubsetforpm10(const std::vector<PollutionData>& dataSubset) {
    std::vector<PollutionData> filteredData;
    for (const auto& item : dataSubset) {
        std::string parameter = item.parameter;
        parameter.erase(std::remove(parameter.begin(), parameter.end(), '\"'), parameter.end());

        if (parameter == "PM10") {
            filteredData.push_back(item);
        }
    }
    return filteredData;
}

std::vector<PollutionData> analyzeDataSubsetforco(const std::vector<PollutionData>& dataSubset) {
    std::vector<PollutionData> filteredData;
    for (const auto& item : dataSubset) {
        std::string parameter = item.parameter;
        parameter.erase(std::remove(parameter.begin(), parameter.end(), '\"'), parameter.end());

        if (parameter == "CO") {
            filteredData.push_back(item);
        }
    }
    return filteredData;
}

