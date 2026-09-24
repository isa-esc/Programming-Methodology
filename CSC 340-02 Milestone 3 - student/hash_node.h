/**
 * @file hash_node.h
 * @author Hugh Hui
 * @brief Defines the HashNode class used in the hash table implementation.
 *
 * @date 2025-01-16 Created by H. Hui
 * @date 2025-06-05 Modified by H. Hui; added additional doxygen style comments
 */

#ifndef _HASH_NODE
#define _HASH_NODE

#include "dll_node.h"

 /**
  * @class HashNode
  * @brief Represents a node in the hash table, linking to a corresponding FIFO list node.
  */
class HashNode {
public:
    int key;              /**< The key associated with this node. */
    int hashCode;         /**< Hash code derived from the key and table size. */
    HashNode* next;       /**< Pointer to the next HashNode in the chain (for collision resolution). */
    HashNode* prev;       /**< Pointer to the previous HashNode in the chain. */
    DllNode* fifoNode;    /**< Pointer to the corresponding node in the FIFO list. */

    /**
     * @brief Constructs a HashNode with the given key and associated FIFO node.
     * @param myKey The key for this hash node.
     * @param myFifoNode Pointer to the associated FIFO (doubly linked list) node.
     */
    HashNode(int myKey, DllNode* myFifoNode);

    /**
     * @brief Retrieves the associated FIFO list node.
     * @return Pointer to the corresponding DllNode.
     */
    DllNode* getFifoNode();

    /**
     * @brief Logs node information to console and file.
    */
    void printNode(bool verbose);


};

#endif // _HASH_NODE
