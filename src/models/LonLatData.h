#include <functional>
#ifndef LONLAT_DATA_H
#define LONLAT_DATA_H


// Structure to hold longitude-latitude pair
struct LonLatPair {
    double longitude;
    double latitude;
    
    // Overload the equality operator to use LonLatPair as a key in unordered_set
    bool operator==(const LonLatPair& other) const {
        return longitude == other.longitude && latitude == other.latitude;
    }
};
// Hash function for LonLatPair to be used in unordered_set
namespace std {
    template <>
    struct hash<LonLatPair> {
        size_t operator()(const LonLatPair& pair) const {
            // Combine hash of longitude and latitude
            return hash<double>()(pair.longitude) ^ hash<double>()(pair.latitude);
        }
    };
}
#endif
