
#ifndef DATALOAD_HOTSPOT_H
#define DATALOAD_HOTSPOT_H


#include "../models/LonLatData.h"
#include <vector>
#include <string>

std::vector<LonLatPair> loadData(const std::string& rootFolderPath);

#endif