/**
 * @file dll_node.cpp
 * @author Hugh Hui
 * @brief This file implements the constructors and print method for the DllNode class.
 * @date 2024-12-30 Initial creation
 * @date 2025-06-05 Modified by hhui; added additional doxygen style comments
 * @date 2026-06-03 modified by hhui; added printNode
 */

#include <string>
#include "dll_node.h"
#include "milestone3.h"

/**
 * @brief Constructs a DllNode with the given key and initializes pointers to nullptr.
 *
 * @param value Integer key to store in the node.
 */
DllNode::DllNode(int value)
    : key(value), prev(nullptr), next(nullptr) {}

/**
 * @brief Constructs a DllNode with full contact information and initializes pointers to nullptr.
 *
 * @param myValue     Integer key for the node.
 * @param myFullName  Full name associated with the node.
 * @param myAddress   Address string.
 * @param myCity      City name.
 * @param myState     State name.
 * @param myZip       ZIP code string.
 */
DllNode::DllNode(int myValue, std::string myFullName, std::string myAddress, std::string myCity, std::string myState, std::string myZip)
    : key(myValue),
    fullName(myFullName),
    address(myAddress),
    city(myCity),
    state(myState),
    zip(myZip),
    prev(nullptr),
    next(nullptr) {}

/**
 * @brief Prints the node information to console and/or file.
 *        If verbose mode is enabled, prints full details; otherwise, just the key.
 */
void DllNode::printNode() {
    bool verbose = false;

    if (verbose) {
        logToFileAndConsole("FIFO info from cacheManager.  Node key: " + std::to_string(key) +
            "; name: " + fullName +
            "; address: " + address +
            "; city: " + city +
            "; state: " + state +
            "; zip: " + zip);
    }
    else {
        logToFileAndConsole("FIFO info from cacheManager:  Node key: " + std::to_string(key));
    }
}
