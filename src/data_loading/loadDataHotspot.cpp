#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <mpi.h>
#include <regex>
#include <fstream>
#include <chrono>
#include <windows.h>
#include <omp.h>
#include <sstream> // Add this line for std::istringstream
#include <algorithm>
#include <unordered_set>
#include "../models/LonLatData.h"

std::vector<LonLatPair> loadData(const std::string& rootFolderPath) {
    std::vector<LonLatPair> data;

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
                        do {
                            if (!(findCsvFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                                std::string fileName = findCsvFileData.cFileName;
                                std::string csvFilePath = dateFolderFullPath + "\\" + fileName;
                                std::ifstream file(csvFilePath);
                                if (file.is_open()) {
                                    double longitude, latitude;
                                    std::string line;
                                    while (std::getline(file, line)) {
                                        std::istringstream iss(line);
                                        std::string longitude_str, latitude_str;

                                        if (std::getline(iss, longitude_str, ',') &&
                                            std::getline(iss, latitude_str, ',')) {
                                            
                                            longitude_str.erase(std::remove(longitude_str.begin(), longitude_str.end(), '\"'), longitude_str.end());
                                            latitude_str.erase(std::remove(latitude_str.begin(), latitude_str.end(), '\"'), latitude_str.end());

                                            if (std::stringstream(longitude_str) >> longitude &&
                                                std::stringstream(latitude_str) >> latitude) {
                                                data.push_back({longitude, latitude});
                                            } else {
                                                std::cerr << "Error converting latitude or longitude to double from line: " << line << std::endl;
                                            }
                                        } else {
                                            std::cerr << "Error reading longitude or latitude from line: " << line << std::endl;
                                        }
                                    }
                                    file.close();
                                } else {
                                    std::cerr << "Error opening file: " << csvFilePath << std::endl;
                                }
                            }
                        } while (FindNextFileA(hCsvFileFind, &findCsvFileData) != 0);
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
