/**
 * @author - Hugh Hui
 * @file milestone3.cpp
 * @brief Main program to read config, parse JSON test cases, and manage cache via CacheManager.
 *
 * The program reads configuration from "milestone3_config.json" which defines input/output files
 * and parameters for hash table and FIFO sizes. It processes test cases described in JSON,
 * executing cache operations and logging results.
 *
 * @date 2024-09-23 Created by ChatGPT with JSON parsing for milestone3_config.json
 * @date 2025-01-10 Modified by H. Hui; added separate files, DEFINE and comments
 * @date 2025-01-13 Modified by H. Hui; moved DoublyLinkedList print methods, added node removal on FIFO size limit
 * @date 2025-01-14 Modified by H. Hui; improved print functions to include detailed node fields
 */

#define _CRT_SECURE_NO_WARNINGS
#define CONFIG_FILE "milestone3_config.json"

#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"
#include "cache_manager.h"
#include "hash_table.h"


using json = nlohmann::json;

// Global output file stream for logging
std::ofstream _outFile;

/**
 * @brief Returns a reference to the global output file stream.
 *
 * @return std::ofstream& Reference to the output file stream.
 */
std::ofstream& getOutFile() {
    return _outFile;
}

/**
 * @brief Opens an output file at the specified path, closing any previously open file.
 *
 * @param filePath The path to the output file.
 */
void setOutFile(const std::string& filePath) {
    if (_outFile.is_open()) {
        _outFile.close();
    }

    _outFile.open(filePath);
    if (!_outFile.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
    }
}

/**
 * @brief Logs a message to both the console and the output file.
 *
 * @param message The message to log.
 */
void logToFileAndConsole(const std::string& message) {
    std::ofstream& outFile = getOutFile();
    std::cout << message << std::endl;
    outFile << message << std::endl;
}

/**
 * @brief Processes a single test case on the given CacheManager using data from JSON.
 *
 * For each action in the test case, the corresponding CacheManager method is called,
 * and results are logged to console and output file.
 *
 * @param cacheManager Pointer to the CacheManager instance.
 * @param testCaseName Name of the test case.
 * @param testCaseArray JSON array describing the actions to perform.
 */
void processTestCase(CacheManager* cacheManager, const std::string& testCaseName, const json& testCaseArray) {
    std::ofstream& outFile = getOutFile();

    std::cout << "Processing " << testCaseName << ":\n\n";
    outFile << "Processing " << testCaseName << ":\n\n";

    for (const auto& entry : testCaseArray) {
        for (auto it = entry.begin(); it != entry.end(); ++it) {
            const std::string& actionName = it.key();
            const json& details = it.value();

            if (actionName == "isEmpty") {
                logToFileAndConsole("isEmpty returned: " + std::to_string(cacheManager->isEmpty()));
            }
            else if (actionName == "contains") {
                int key = details["key"];
                logToFileAndConsole("contains key " + std::to_string(key) + ": " + std::to_string(cacheManager->contains(details["key"])));
            }
            else if (actionName == "getSize") {
                logToFileAndConsole("getSize: " + std::to_string(cacheManager->getSize()));
            }
            else if (actionName == "add") {
                DllNode* newDllNode = new DllNode(details["key"], details["fullName"], details["address"],
                    details["city"], details["state"], details["zip"]);
                cacheManager->add(details["key"], newDllNode);
                int key = details["key"];
                logToFileAndConsole("add key to cacheManager: " + std::to_string(key));
            }
            else if (actionName == "remove") {
                int key = details["key"];
                cacheManager->remove(key);
                logToFileAndConsole("remove key: " + std::to_string(key) + " from cacheManager");
            }
            else if (actionName == "printCache") {
                cacheManager->printCache();
            }
            else if (actionName == "getItem") {
                int key = details["key"];
                HashNode* result = cacheManager->getTable()->getItem(key);
                if (result) {
                    bool verbose = true;
                    std::cout << "getItem key: " << key << " has the following -> ";
                    outFile << "getItem key: " << key << " has the following -> ";
                    result->printNode(verbose);
                }
                else {
                    std::cout << "getItem(" << key << "): " << " does not exist" << std::endl;
                    outFile << "getItem(" << key << "): " << " does not exist" << std::endl;
                }
            }
            else if (actionName == "clear") {
                cacheManager->clear();
                std::cout << "clear cacheManager" << std::endl;
                outFile << "clear cacheManager" << std::endl;
            }
        }
    }
}

/**
 * @brief Entry point of the program.
 *
 * Reads configuration and input JSON files, sets up cache manager, processes test cases,
 * logs output, and manages resources.
 *
 * @return int Exit status code.
 */
int main() {
    // Load configuration file
    std::ifstream configFile(CONFIG_FILE);
    if (!configFile.is_open()) {
        std::cerr << "Error opening config file!" << std::endl;
        return 1;
    }

    json config;
    configFile >> config;

    // Retrieve file paths and parameters from config
    std::string inputFilePath = config["Milestone3"][0]["files"][0]["inputFile"];
    std::string outputFilePath = config["Milestone3"][0]["files"][0]["outputFile"];
    std::string errorFilePath = config["Milestone3"][0]["files"][0]["errorLogFile"];
    int HASH_SIZE = config["Milestone3"][0]["defaultVariables"][0]["hashTableSize"];
    int FIFO_SIZE = config["Milestone3"][0]["defaultVariables"][0]["FIFOListSize"];

    // Create cache manager
    CacheManager* cacheManager = new CacheManager(FIFO_SIZE, HASH_SIZE);

    // Create the hash table
    HashTable* hashTable = new HashTable(HASH_SIZE);


    // Load input JSON file
    std::ifstream inputFile(inputFilePath);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file: " << inputFilePath << std::endl;
        return 1;
    }

    // Set output file for logging
    setOutFile(outputFilePath);
    std::ofstream& outFile = getOutFile();

    // Read input JSON data
    json data;
    inputFile >> data;

    // Process test cases
    for (const auto& testCase : data["cacheManager"]) {
        for (auto it = testCase.begin(); it != testCase.end(); ++it) {
            const std::string& testCaseName = it.key();
            const json& testCaseArray = it.value();

            processTestCase(cacheManager, testCaseName, testCaseArray);

            cacheManager->clear();
        }
    }

    // Cleanup
    configFile.close();
    inputFile.close();
    outFile.close();
    delete cacheManager;

    return 0;
}
