/**
 * @file hash_node.cpp
 * @author Hugh Hui
 * @brief This implementation file defines the methods declared in the hash_node.h file.
 *
 * @date 2024-09-23 Created by ChatGPT
 * @date 2024-10-17 Modified by jhui
 * @date 2025-01-11 Modified by H. Hui: added support for hash table integration with FIFO nodes
 * @date 2025-06-05 Modified by H. Hui; added additional doxygen style comments
 */

#include "hash_node.h"
#include "dll_node.h"
#include "milestone3.h"

 /**
  * @brief Constructs a HashNode with a given key and associated FIFO node.
  *
  * @param myKeyValue The key value for this hash node.
  * @param myFifoNode Pointer to the associated node in the doubly linked list (FIFO).
  */
HashNode::HashNode(int myKeyValue, DllNode* myFifoNode) {
    key = myKeyValue;
    fifoNode = myFifoNode;
}

/**
 * @brief Retrieves the associated FIFO node.
 *
 * @return Pointer to the DllNode object.
 */
DllNode* HashNode::getFifoNode() {
    return fifoNode;
}

/**
 * @brief Prints the contents of the HashNode.
 *
 * This method logs the node's key to the console and output file. If the `verbose` flag is set to true,
 * it logs the full details (name, address, city, state, zip). This function is primarily used for debugging
 * and inspecting the contents of the node.
 */

void HashNode::printNode(bool verbose) {
    if (verbose && fifoNode != nullptr) {
        logToFileAndConsole(
            "FIFO info from cacheManager. Node key: "
            + std::to_string(key)
            + "; name: " + fifoNode->fullName
            + "; address: " + fifoNode->address
            + "; city: " + fifoNode->city
            + "; state: " + fifoNode->state
            + "; zip: " + fifoNode->zip
        );
    }
    else {
        logToFileAndConsole(
            "FIFO info from cacheManager. Node key: "
            + std::to_string(key)
        );
    }
}