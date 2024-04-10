#include <iostream>
#include <vector>
#include <chrono>
#include <mpi.h>
#include "../models/pollutionData.h"
#include "../data_loading/loadData.h"
#include "../data_analysis/analyzeData.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Assuming rootFolder path might come from command line arguments or hardcoded
    std::string rootFolder = "C:/path/to/your/data";
    std::vector<PollutionData> dataset = loadData(rootFolder);
    
    // Distribute data among MPI processes
    int subsetSize = dataset.size() / size;
    int startIndex = rank * subsetSize;
    int endIndex = (rank == size - 1) ? dataset.size() : (rank + 1) * subsetSize;
    std::vector<PollutionData> processSubset(dataset.begin() + startIndex, dataset.begin() + endIndex);

    // Record start time
    auto startTime = high_resolution_clock::now();

    // Parallelize the data analysis loop using OpenMP (if you've set it up)
    // Call your analysis functions here, for example:
    std::vector<PollutionData> ozone = analyzeDataSubsetforozone(processSubset);
    // Repeat for other pollutants as needed...

    // Assuming there's some form of reduction or collection of results across MPI processes
    // For example, summing up the counts of each pollutant type found by each process

    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(endTime - startTime);

    // Output results
    if (rank == 0) {
        std::cout << "Analysis complete.\n";
        std::cout << "Total time taken: " << duration.count() << " milliseconds\n";
        // Display more results as needed...
    }

    MPI_Finalize();
    return 0;
}
