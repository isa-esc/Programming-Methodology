/**
 * @file cache_manager.h
 * @author Hugh Hui
 * @brief Declares the CacheManager class used for managing a cache with a hash table and FIFO list.
 *
 * @date 2024-09-23 Created by ChatGPT
 * @date 2024-10-17 Modified by jhui
 * @date 2025-01-11 Modified by hhui; added calculateHashCode and updated method signatures
 * @date 2025-01-16 Modified by hhui; created separate node structure file
 * @date 2025-01-27 Modified by hhui; added getMaxCacheSize
 * @date 2025-06-05 Modified by hhui; added additional doxygen style comments
 * @date 05/25/26 - added destructor for CacheManager
 */

#ifndef _CACHE_MANAGER
#define _CACHE_MANAGER

#include "hash_table.h"
#include "doubly_linked_list.h"

/**
 * @class CacheManager
 * @brief Manages a cache using a hash table and FIFO list (DoublyLinkedList).
 */
class CacheManager {
private:
    HashTable* hashTable;               /**< Internal hash table for fast key access. */
    DoublyLinkedList* doublyLinkedList; /**< FIFO list to maintain insertion order. */
    int maxCacheSize;                   /**< Maximum number of entries allowed in the cache. */

public:
    /**
     * @brief Constructs a CacheManager with the specified cache and hash table sizes.
     * @param myMaxCacheSize Maximum size of the cache.
     * @param myHashTableSize Size of the hash table (number of buckets).
     */
    CacheManager(int myMaxCacheSize, int myHashTableSize) {
        hashTable = new HashTable(myHashTableSize);
        doublyLinkedList = new DoublyLinkedList();
        maxCacheSize = myMaxCacheSize;
    }

    /**
    * @brief Destructor for CacheManager.
    *
    * Releases all dynamically allocated memory associated with the cache manager.
    */
    ~CacheManager() {
        clear();
        delete hashTable;
        delete doublyLinkedList;
    }

    /**
     * @brief Returns a pointer to the internal hash table.
     * @return Pointer to the HashTable object.
     */
    HashTable* getTable();

    /**
     * @brief Returns a pointer to the internal FIFO list.
     * @return Pointer to the DoublyLinkedList object.
     */
    DoublyLinkedList* getList();

    /**
     * @brief Gets the current number of items in the cache.
     * @return Number of items in the cache.
     */
    int getSize();

    /**
     * @brief Checks whether the cache is empty.
     * @return True if the cache has no entries, false otherwise.
     */
    bool isEmpty();

    /**
     * @brief Adds a node to the cache, evicting the least recently used if >= Max Cache Size
     * @param curKey Key associated with the node.
     * @param myNode Pointer to the node to be added.
     * @return True if the operation succeeds, false otherwise.
     */
    bool add(int curKey, DllNode* myNode);

    /**
     * @brief Removes a node from the cache based on the key.
     * @param curKey Key of the node to be removed.
     * @return True if the operation succeeds, false otherwise.
     */
    bool remove(int curKey);

    /**
     * @brief Clears all entries from the cache.
     */
    void clear();

    /**
     * @brief Retrieves a node from the cache.
     * @param curKey Key of the node to retrieve.
     * @return Pointer to the DllNode if found, nullptr otherwise.
     */
    DllNode* getItem(int curKey);

    /**
     * @brief Gets the maximum cache size.
     * @return Maximum number of entries the cache can hold.
     */
    int getMaxCacheSize();

    /**
     * @brief Checks if a specific key exists in the cache.
     * @param curKey Key to check.
     * @return True if the key exists in the cache, false otherwise.
     */
    bool contains(int curKey);

    /**
     * @brief Prints the current contents of the cache to console and output file.
     */
    void printCache();
};

#endif // _CACHE_MANAGER
