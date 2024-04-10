#ifndef DATA_LOADING_H
#define DATA_LOADING_H

#include "../models/PollutionData.h" 
#include <vector>
#include <string>

std::vector<PollutionData> loadData(const std::string& rootFolderPath);

#endif