#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>
#include <cstring>
#include <algorithm>
#include <windows.h>
#include <mpi.h>
#include <chrono>
#include <unordered_map>
using namespace std::chrono;

struct PollutionData {
    
    std::string parameter;
    double concentration;
    
};

std::vector<PollutionData> loadData(const std::string& rootFolderPath) {
    std::vector<PollutionData> data;

    WIN32_FIND_DATAA findDateFolderData;
    HANDLE hDateFolderFind = INVALID_HANDLE_VALUE;
    std::string dateFolderPath = rootFolderPath + "\\*.*";
    hDateFolderFind = FindFirstFileA(dateFolderPath.c_str(), &findDateFolderData);
    if (hDateFolderFind != INVALID_HANDLE_VALUE) {
        do {
            if (findDateFolderData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                std::string dateFolderName = findDateFolderData.cFileName;
                if (std::regex_match(dateFolderName, std::regex("\\d{8}"))) {
                    std::string dateFolderFullPath = rootFolderPath + "\\" + dateFolderName;
                    WIN32_FIND_DATAA findCsvFileData;
                    HANDLE hCsvFileFind = INVALID_HANDLE_VALUE;
                    std::string csvFilesPath = dateFolderFullPath + "\\*.csv";
                    hCsvFileFind = FindFirstFileA(csvFilesPath.c_str(), &findCsvFileData);
                    if (hCsvFileFind != INVALID_HANDLE_VALUE) {
                        #pragma omp parallel
                        {
                            do {
                                if (!(findCsvFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                                    std::string fileName = findCsvFileData.cFileName;
                                    std::string csvFilePath = dateFolderFullPath + "\\" + fileName;
                                    std::ifstream file(csvFilePath);
                                    if (file.is_open()) {
                                        std::string line;
                                        while (std::getline(file, line)) {
                                            std::istringstream iss(line);
                                            std::string parameter, concentration_str, unit_str;

                                            // Skip first three columns (longitude, latitude, utcDate)
                                            std::string skip;
                                            for (int i = 0; i < 3; ++i) {
                                                std::getline(iss, skip, ',');
                                            }

                                            // Read pollutant, concentration, and unit from columns 4, 5, and 6 respectively
                                            if (std::getline(iss, parameter, ',') &&
                                                std::getline(iss, concentration_str, ',')
                                                ) {
                                                
                                                concentration_str.erase(std::remove(concentration_str.begin(), concentration_str.end(), '\"'), concentration_str.end());
                                                

                                                double concentration;
                                                if (std::stringstream(concentration_str) >> concentration) {
                                                    #pragma omp critical
                                                    data.push_back({ parameter, concentration });
                                                } else {
                                                    #pragma omp critical
                                                    std::cerr << "Error converting concentration to double from line: " << line << std::endl;
                                                }
                                            } else {
                                                #pragma omp critical
                                                std::cerr << "Error reading data from line: " << line << std::endl;
                                            }
                                        }
                                        file.close();
                                    } else {
                                        #pragma omp critical
                                        std::cerr << "Error opening file: " << csvFilePath << std::endl;
                                    }
                                }
                            } while (FindNextFileA(hCsvFileFind, &findCsvFileData) != 0);
                        }
                        FindClose(hCsvFileFind);
                    } else {
                        std::cerr << "No CSV files found in folder: " << dateFolderFullPath << std::endl;
                    }
                }
            }
        } while (FindNextFileA(hDateFolderFind, &findDateFolderData) != 0);
        FindClose(hDateFolderFind);
    } else {
        std::cerr << "Error finding date folders in directory: " << rootFolderPath << std::endl;
    }

    return data;
}


// ozone

    std::vector<PollutionData> analyzeDataSubsetforozone(const std::vector<PollutionData>& dataSubset
                                             ) {
    std::vector<PollutionData> ozoneData;
    // std::cout << "dataset size in analyze: " << dataSubset.size() << std::endl;

    // Count occurrences of each pollutant
    for (const auto& entry : dataSubset) {
        // Remove quotes if they exist in entry.parameter
        std::string parameter = entry.parameter;
        parameter.erase(std::remove(parameter.begin(), parameter.end(), '\"'), parameter.end());

        // If the parameter is "OZONE", add it to ozoneData
        if (parameter == "OZONE") {
            ozoneData.push_back(entry);
        }
        
    }
    

    // std::cout << "ozone dataset size: " << ozoneData.size() << std::endl;
    return ozoneData;
}
// no2
std::vector<PollutionData> analyzeDataSubsetforno2(const std::vector<PollutionData>& dataSubset
                                             ) {
    std::vector<PollutionData> no2Data;
    // std::cout << "dataset size in analyze: " << dataSubset.size() << std::endl;

    // Count occurrences of each pollutant
    for (const auto& entry : dataSubset) {
        // Remove quotes if they exist in entry.parameter
        std::string parameter = entry.parameter;
        parameter.erase(std::remove(parameter.begin(), parameter.end(), '\"'), parameter.end());

        // If the parameter is "NO2", add it to ozoneData
        if (parameter == "NO2") {
            no2Data.push_back(entry);
        }
        // Increment the count for the current parameter
        // numOccurrences.push_back({parameter, 1});
    }
    

    // std::cout << "ozone dataset size: " << no2Data.size() << std::endl;
    return no2Data;
}
// so2
std::vector<PollutionData> analyzeDataSubsetforso2(const std::vector<PollutionData>& dataSubset
                                             ) {
    std::vector<PollutionData> so2Data;
    // std::cout << "dataset size in analyze: " << dataSubset.size() << std::endl;

    // Count occurrences of each pollutant
    for (const auto& entry : dataSubset) {
        // Remove quotes if they exist in entry.parameter
        std::string parameter = entry.parameter;
        parameter.erase(std::remove(parameter.begin(), parameter.end(), '\"'), parameter.end());

        // If the parameter is "SO2", add it to ozoneData
        if (parameter == "SO2") {
            so2Data.push_back(entry);
        }
        // Increment the count for the current parameter
        // numOccurrences.push_back({parameter, 1});
    }
    

    // std::cout << "ozone dataset size: " << so2Data.size() << std::endl;
    return so2Data;
}
// pm2.5
std::vector<PollutionData> analyzeDataSubsetforpm(const std::vector<PollutionData>& dataSubset
                                             ) {
    std::vector<PollutionData> pmData;
    // std::cout << "dataset size in analyze: " << dataSubset.size() << std::endl;

    // Count occurrences of each pollutant
    for (const auto& entry : dataSubset) {
        // Remove quotes if they exist in entry.parameter
        std::string parameter = entry.parameter;
        parameter.erase(std::remove(parameter.begin(), parameter.end(), '\"'), parameter.end());

        // If the parameter is "PM2.5", add it to ozoneData
        if (parameter == "PM2.5") {
            pmData.push_back(entry);
        }
        
    }
    

    // std::cout << "ozone dataset size: " << pmData.size() << std::endl;
    return pmData;
}
// pm10
std::vector<PollutionData> analyzeDataSubsetforpm10(const std::vector<PollutionData>& dataSubset
                                             ) {
    std::vector<PollutionData> pm10Data;
    // std::cout << "dataset size in analyze: " << dataSubset.size() << std::endl;

    // Count occurrences of each pollutant
    for (const auto& entry : dataSubset) {
        // Remove quotes if they exist in entry.parameter
        std::string parameter = entry.parameter;
        parameter.erase(std::remove(parameter.begin(), parameter.end(), '\"'), parameter.end());

        // If the parameter is "PM10)", add it to ozoneData
        if (parameter == "PM10") {
            pm10Data.push_back(entry);
        }
        
    }
    

    // std::cout << "ozone dataset size: " << pm10Data.size() << std::endl;
    return pm10Data;
}
// co
std::vector<PollutionData> analyzeDataSubsetforco(const std::vector<PollutionData>& dataSubset
                                             ) {
    std::vector<PollutionData> coData;
    // std::cout << "dataset size in analyze: " << dataSubset.size() << std::endl;

    // Count occurrences of each pollutant
    for (const auto& entry : dataSubset) {
        // Remove quotes if they exist in entry.parameter
        std::string parameter = entry.parameter;
        parameter.erase(std::remove(parameter.begin(), parameter.end(), '\"'), parameter.end());

        // If the parameter is "CO", add it to ozoneData
        if (parameter == "CO") {
            coData.push_back(entry);
        }
       
    }
    

    // std::cout << "ozone dataset size: " << coData.size() << std::endl;
    return coData;
}




int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::string rootFolder = "C:/Users/016915509/Desktop/275-John_Gash/mini project 2/fire-2020-full-data.tar/fire-2020-full-data/data";
    std::vector<PollutionData> dataset = loadData(rootFolder);
    
    // Distribute data among MPI processes
    int subsetSize = dataset.size() / size;
    int startIndex = rank * subsetSize;
    int endIndex = (rank == size - 1) ? dataset.size() : (rank + 1) * subsetSize;

    std::vector<PollutionData> processSubset(dataset.begin() + startIndex, dataset.begin() + endIndex);

    // Record start time
    auto startTime = high_resolution_clock::now();

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
    
    // Reduce operation using MPI
    MPI_Reduce(&total_co_count, &total_co_global, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&total_so_count, &total_so_global, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&total_pm_count, &total_pm_global, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&total_pm10_count, &total_pm10_global, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&total_no_count, &total_no_global, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&total_ozone_count, &total_ozone_global, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

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
        std::cout << "Pollutant with the maximum number of wildfires: " << maxPollutant << " (" << maxCount << " wildfires)" << std::endl;
        std::cout << "Total time taken: " << duration.count() << " milliseconds" << std::endl;
    }

    MPI_Finalize();

    return 0;
}