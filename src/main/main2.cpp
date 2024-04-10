#include <iostream>
#include <vector>
#include <chrono>
#include <mpi.h>

#include "../data_loading/loadDataHotspot.h"

#include "../models/LonLatData.h"
#include "../data_analysis/analyzeHotspot.h"
#include <unordered_set>




using namespace std;
using namespace std::chrono;

int main(int argc, char** argv) {
     // Initialize MPI
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::string folderPath = "C:\\Users\\016915509\\Desktop\\275-John_Gash\\mini project 2\\fire-2020-full-data.tar\\fire-2020-full-data\\data";

    // Load data assigned to this process
    std::vector<LonLatPair> data = loadData(folderPath);
    

    // Record start time
    auto startTime = high_resolution_clock::now();

    // Distribute data among MPI processes
    std::vector<LonLatPair> local_data(data.size() / size);
    MPI_Scatter(data.data(), data.size() / size, MPI_DOUBLE, local_data.data(), data.size() / size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Detect hotspots for local data
    std::vector<LonLatPair> local_hotspots = detectHotspots(local_data, 0.01);

    // Use unordered_set to store distinct hotspots
    std::unordered_set<LonLatPair> distinct_hotspots(local_hotspots.begin(), local_hotspots.end());
    

    // Calculate the total number of distinct hotspots across all processes
    int total_hotspot_count = distinct_hotspots.size();
    int total_hotspot_count_global;
    MPI_Reduce(&total_hotspot_count, &total_hotspot_count_global, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    std::cout << "Total number of distinct hotspots foe each local process: " << total_hotspot_count << std::endl;
    // Record end time
    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(endTime - startTime);

    // Finalize MPI
    MPI_Finalize();

    // Output the total number of distinct hotspots on rank 0
    if (rank == 0) {
        std::cout << "Total number of distinct hotspots: " << total_hotspot_count_global << std::endl;
        std::cout << "Total time taken: " << duration.count() << " milliseconds" << std::endl;
    }

    return 0;

    MPI_Finalize();
    return 0;
}
