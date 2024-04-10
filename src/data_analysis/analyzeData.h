#ifndef ANALYZE_DATA_H
#define ANALYZE_DATA_H

#include "../models/pollutionData.h"
#include <vector>

std::vector<PollutionData> analyzeDataSubsetforozone(const std::vector<PollutionData>& dataSubset);
std::vector<PollutionData> analyzeDataSubsetforno2(const std::vector<PollutionData>& dataSubset);
std::vector<PollutionData> analyzeDataSubsetforso2(const std::vector<PollutionData>& dataSubset);
std::vector<PollutionData> analyzeDataSubsetforpm(const std::vector<PollutionData>& dataSubset);
std::vector<PollutionData> analyzeDataSubsetforpm10(const std::vector<PollutionData>& dataSubset);
std::vector<PollutionData> analyzeDataSubsetforco(const std::vector<PollutionData>& dataSubset);

#endif
