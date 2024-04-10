#include <iostream>
#include <vector>
#include <chrono>
#include <mpi.h>
#include "../models/pollutionData.h"
#include "../data_loading/loadData.h"
#include "../data_analysis/analyzeData.h"
#include "../data_analysis/analyzeHotspot.h"
#include <unordered_set>




using namespace std;
using namespace std::chrono;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Assuming rootFolder path might come from command line arguments or hardcoded
    std::string rootFolder = "C:\\Users\\016915509\\Desktop\\275-John_Gash\\mini project 2\\fire-2020-full-data.tar\\fire-2020-full-data\\data";
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
    std::vector<PollutionData> ozone, co, so, pm, pm10, no;

    // Parallelize the data analysis loop using OpenMP
    #pragma omp parallel sections
    {
        #pragma omp section
        ozone = analyzeDataSubsetforozone(processSubset);

        #pragma omp section
        co = analyzeDataSubsetforco(processSubset);

        #pragma omp section
        so = analyzeDataSubsetforso2(processSubset);

        #pragma omp section
        pm = analyzeDataSubsetforpm(processSubset);

        #pragma omp section
        pm10 = analyzeDataSubsetforpm10(processSubset);

        #pragma omp section
        no = analyzeDataSubsetforno2(processSubset);
    }

    int total_co_count = co.size();
    int total_so_count = so.size();
    int total_pm_count = pm.size();
    int total_pm10_count = pm10.size();
    int total_no_count = no.size();
    int total_ozone_count = ozone.size();
    int total_co_global;
    int total_so_global;
    int total_pm_global;
    int total_pm10_global;
    int total_no_global;
    int total_ozone_global;
    
    // Assuming there's some form of reduction or collection of results across MPI processes
    // For example, summing up the counts of each pollutant type found by each process

    // Reduce operation using MPI
    MPI_Reduce(&total_co_count, &total_co_global, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&total_so_count, &total_so_global, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&total_pm_count, &total_pm_global, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&total_pm10_count, &total_pm10_global, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&total_no_count, &total_no_global, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&total_ozone_count, &total_ozone_global, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
   
    // Record end time


    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(endTime - startTime);

    if (rank == 0) {
        std::cout << "Total number of wildfires occurred: " << dataset.size() << std::endl;
        std::cout << "Total number of wildfires from pollutant OZONE: " << total_ozone_global << std::endl;
        std::cout << "Total number of wildfires from pollutant CO: " << total_co_global << std::endl;
        std::cout << "Total number of wildfires from pollutant NO: " << total_no_global << std::endl;
        std::cout << "Total number of wildfires from pollutant PM2.5: " << total_pm_global << std::endl;
        std::cout << "Total number of wildfires from pollutant PM10: " << total_pm10_global << std::endl;
        std::cout << "Total number of wildfires from pollutant SO2: " << total_so_global << std::endl;

        // Determine the pollutant with the maximum number of wildfires
        std::string maxPollutant;
        int maxCount = -1;
        if (total_ozone_count > maxCount) {
            maxCount = total_ozone_global;
            maxPollutant = "OZONE";
        }
        if (total_co_count > maxCount) {
            maxCount = total_co_global;
            maxPollutant = "CO";
        }
        if (total_no_count > maxCount) {
            maxCount = total_no_global;
            maxPollutant = "NO";
        }
        if (total_pm_count > maxCount) {
            maxCount = total_pm_global;
            maxPollutant = "PM2.5";
        }
        if (total_pm10_count > maxCount) {
            maxCount = total_pm10_global;
            maxPollutant = "PM10";
        }
        if (total_so_count > maxCount) {
            maxCount = total_so_global;
            maxPollutant = "SO2";
        }

        // Print the pollutant with the maximum number of wildfires
        std::cout << "Analysis complete.\n";
        std::cout << "Total time taken: " << duration.count() << " milliseconds\n";
        std::cout << "Pollutant with the maximum number of wildfires: " << maxPollutant << " (" << maxCount << " wildfires)" << std::endl;
        
    }

 

    MPI_Finalize();
    return 0;
}
