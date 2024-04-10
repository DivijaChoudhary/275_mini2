#ifndef ANALYZE_LATLON_H
#define ANALYZE_LATLON_H

#include "../models/LonLatData.h"
#include <vector>
std::vector<LonLatPair> detectHotspots(const std::vector<LonLatPair>& data, double threshold);
double calculateDistance(const LonLatPair& coord1, const LonLatPair& coord2);

#endif