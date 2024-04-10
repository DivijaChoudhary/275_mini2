#include "analyzeHotspot.h"
#include <algorithm>
#include <iostream>
#include <cmath>


double calculateDistance(const LonLatPair& coord1, const LonLatPair& coord2) {
    double dx = coord1.longitude - coord2.longitude;
    double dy = coord1.latitude - coord2.latitude;
    return std::sqrt(dx * dx + dy * dy);
}
std::vector<LonLatPair> detectHotspots(const std::vector<LonLatPair>& data, double threshold) {
    std::vector<LonLatPair> hotspots;

    #pragma omp parallel for shared(hotspots)
    for (size_t i = 0; i < data.size(); ++i) {
        bool addToExistingHotspot = false;
        for (const auto& hotspot : hotspots) {
            if (calculateDistance(data[i], hotspot) <= threshold) {
                addToExistingHotspot = true;
                break;
            }
        }
        if (!addToExistingHotspot) {
            #pragma omp critical
            hotspots.push_back(data[i]);
        }
    }

    return hotspots;
}
