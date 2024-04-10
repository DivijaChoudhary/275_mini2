#include "loadData.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>

std::vector<PollutionData> loadData(const std::string& rootFolderPath) {
    std::vector<PollutionData> data;

    WIN32_FIND_DATAA findData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    std::string path = rootFolderPath + "\\*.*"; // Search pattern
    hFind = FindFirstFileA(path.c_str(), &findData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                std::string folderName = findData.cFileName;
                // Check if the folder name matches the expected format (e.g., date)
                if (std::regex_match(folderName, std::regex("\\d{8}"))) {
                    std::string folderPath = rootFolderPath + "\\" + folderName;
                    // Process each CSV file in the folder
                    WIN32_FIND_DATAA csvFindData;
                    HANDLE hCsvFind = INVALID_HANDLE_VALUE;
                    std::string csvPath = folderPath + "\\*.csv";
                    hCsvFind = FindFirstFileA(csvPath.c_str(), &csvFindData);

                    if (hCsvFind != INVALID_HANDLE_VALUE) {
                        do {
                            if (!(csvFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                                std::string csvFilePath = folderPath + "\\" + csvFindData.cFileName;
                                std::ifstream file(csvFilePath);
                                if (file.is_open()) {
                                    std::string line;
                                    while (std::getline(file, line)) {
                                        std::istringstream iss(line);
                                        std::string parameter, concentration_str;
                                        // Parse CSV line here and populate PollutionData
                                        // This is simplified; you should adapt it based on your CSV structure
                                    }
                                    file.close();
                                }
                            }
                        } while (FindNextFileA(hCsvFind, &csvFindData) != 0);
                        FindClose(hCsvFind);
                    }
                }
            }
        } while (FindNextFileA(hFind, &findData) != 0);
        FindClose(hFind);
    }
    return data;
}
