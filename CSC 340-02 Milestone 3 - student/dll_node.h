/**
 * @file dll_node.h
 * @author Hugh Hui
 * @brief This header file defines the DllNode (Doubly Linked List Node) structure.
 *
 * @date 2024-12-30 Initial creation
 * @date 2025-06-05 Modified by hhui; added additional doxygen style comments
 * @date 2026-06-03 Modified by hhui; added printNode
 */

#ifndef DLL_NODE_H
#define DLL_NODE_H

#include <string>

 /**
  * @class DllNode
  * @brief Represents a node in a doubly linked list, containing key-value data and links to neighboring nodes.
  */
class DllNode {
public:
    int key;                 /**< Integer key of the node. */

    std::string fullName;    /**< Full name associated with the node. */
    std::string address;     /**< Address associated with the node. */
    std::string city;        /**< City of the address. */
    std::string state;       /**< State of the address. */
    std::string zip;         /**< ZIP code of the address. */

    DllNode* prev;           /**< Pointer to the previous node in the list. */
    DllNode* next;           /**< Pointer to the next node in the list. */

    /**
     * @brief Constructs a node with the given key.
     * @param value Integer key for the node.
     */
    DllNode(int value);

    /**
     * @brief Constructs a node with full data including key and personal information.
     * @param value Integer key for the node.
     * @param fullName Full name string.
     * @param address Address string.
     * @param city City string.
     * @param state State string.
     * @param zip ZIP code string.
     */
    DllNode(int value, std::string fullName, std::string address, std::string city, std::string state, std::string zip);

    /**
     * @brief Prints the contents of the node to the console.
     */
    void printNode();
};

#endif // DLL_NODE_H
