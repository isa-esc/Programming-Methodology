/**
 * @file hash_table.hpp
 * @author Hugh Hui
 * @brief Declares the HashTable class used for managing key-node mappings with collision handling.
 *
 * @date 2024-09-23 Created by ChatGPT
 * @date 2024-10-17 Modified by jhui
 * @date 2025-01-11 Modified by hhui; added calculateHashCode, updated method signatures
 * @date 2025-01-16 Modified by hhui; created separate node structure file
 * @date 2025-06-05 Modified by H. Hui; added additional doxygen style comments
 * @date 05/25/26 - added destructor for HashTable
 */

#ifndef _HASH_TABLE
#define _HASH_TABLE

#include "hash_node.h"
#include <iostream>

 /**
  * @class HashTable
  * @brief A hash table data structure supporting chaining for collision handling.
  */
class HashTable {
private:
    HashNode** table;       /**< Array of pointers to HashNode (buckets). */
    int numberOfItems;      /**< Current number of items in the table. */
    int numberOfBuckets;    /**< Total number of buckets (size of the table). */

public:
    /**
     * @brief Default constructor.
     */
    HashTable();

    /**
     * @brief Constructs a HashTable with a specific size.
     * @param hashTableSize Number of buckets in the hash table.
     */
    HashTable(int hashTableSize) : numberOfBuckets(hashTableSize), numberOfItems(0) {
        table = new HashNode * [hashTableSize];
        std::cout << "hashTableSize: " << hashTableSize << std::endl;
        for (int i = 0; i < hashTableSize; i++) {
            table[i] = nullptr;
        }
    }

    /**
    * @brief Destructor for HashTable.
    *
    * Clears all entries in the hash table and releases
    * dynamically allocated memory used by the bucket array.
    */
    ~HashTable() {
        clear();          // delete all nodes in the chains
        delete[] table;   // delete bucket array
    }

    /**
     * @brief Returns the internal hash table array.
     * @return Pointer to the hash table array.
     */
    HashNode** getTable();

    /**
     * @brief Returns the total number of buckets in the hash table.
     * @return The number of buckets.
     */
    int getSize();

    /**
     * @brief Calculates a hash code for the given key.
     * @param currentKey The key to hash.
     * @return The hash code (bucket index).
     */
    int calculateHashCode(int currentKey);

    /**
     * @brief Checks if the hash table is empty.
     * @return true if the table has no items; false otherwise.
     */
    bool isEmpty();

    /**
     * @brief Returns the number of items in the hash table.
     * @return The number of items.
     */
    int getNumberOfItems();

    /**
     * @brief Adds a HashNode to the table using a specified key.
     * @param curKey The key associated with the node.
     * @param myNode Pointer to the node to add.
     * @return true if successfully added; false otherwise.
     */
    bool add(int curKey, HashNode* myNode);

    /**
     * @brief Removes a node from the table using a specified key.
     * @param curKey The key of the node to remove.
     * @return true if successfully removed; false otherwise.
     */
    bool remove(int curKey);

    /**
     * @brief Removes all entries from the hash table.
     */
    void clear();

    /**
     * @brief Retrieves a node from the table based on key.
     * @param curKey The key to search for.
     * @return Pointer to the corresponding HashNode if found; nullptr otherwise.
     */
    HashNode* getItem(int curKey);

    /**
     * @brief Checks if a key exists in the table.
     * @param curKey The key to check.
     * @return true if found; false otherwise.
     */
    bool contains(int curKey);

    /**
     * @brief Prints the contents of the hash table to the console and output file.
     */
    void printTable();
};

#endif // _HASH_TABLE
