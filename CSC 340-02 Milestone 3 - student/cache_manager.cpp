/**
 * @file cache_manager.cpp
 * @brief Implements the CacheManager methods. The cache uses a hash table
 *        (fast lookup by key) and a FIFO doubly linked list (insertion order).
 *        Newest entry is at the head of the list, oldest is at the tail.
 * @date 10/14/2026 - Created and implemented cache manager methods.
 * @author Isabela Escobedo Luna
*/

#include "cache_manager.h"
#include "dll_node.h"
#include "doubly_linked_list.h"
#include "hash_node.h"
#include "hash_table.h"
#include "milestone3.h"
#include <string>

/**
* @brief Return the hash table.
* @return Pointer to the internal HashTable.
*/
HashTable* CacheManager::getTable() {
  return hashTable;
}

/**
* @brief Return the FIFO list.
* @return Pointer to the internal DoublyLinkedList.
*/
DoublyLinkedList* CacheManager::getList() {
  return doublyLinkedList;
}

/**
* @brief Return the number of items in the CacheManager.
* @return Number of items currently cached.
*/
int CacheManager::getSize() {
  return hashTable->getNumberOfItems(); //hash table already kept count
}

/**
* @brief Check if the HashTable is empty.
* @return True if the cache has no entries, false otherwise.
*/
bool CacheManager::isEmpty() {
  return hashTable->isEmpty();
}

/**
* @brief Adds a new node to the CacheManager; if number of items >=
*        FIFOListSize, then remove the oldest entry.
* @param curKey Key associated with the node.
* @param myNode Pointer to the DllNode to store.
* @return True if the node was added.
*/
bool CacheManager::add(int curKey, DllNode* myNode) {
  if (myNode == nullptr) {
    return false; //no node to add
  }

  //if key is already in cache, remove old one first
  if (contains(curKey)) {
    remove(curKey);
  }

  //cache full, remove tail
  if (getSize() >= maxCacheSize) {
    DllNode* oldest = doublyLinkedList->tail;
    if (oldest != nullptr) {
      int oldestKey = oldest->key; //save key before deletion
      hashTable->remove(oldestKey); //deletes HashNode
      doublyLinkedList->removeTailNode(); //deletes DllNode
    }
  }

  //newest entry in head
  doublyLinkedList->insertAtHead(curKey, myNode);

  //hash only points to the list node
  HashNode* newHashNode = new HashNode(curKey, myNode);
  newHashNode->hashCode = hashTable->calculateHashCode(curKey);
  return hashTable->add(curKey, newHashNode);
}

/**
* @brief Remove node with key value.
* @param curKey Key of the node to remove.
* @return True if removed, false if the key was not found.
*/
bool CacheManager::remove(int curKey) {
  //key not in cache
  if (!hashTable->contains(curKey)) {
    return false;
  }

  hashTable->remove(curKey); //deletes the HashNode
  doublyLinkedList->remove(curKey); //deletes the DllNode
  return true;
}

/**
* @brief Remove all entries from the CacheManager.
*/
void CacheManager::clear() {
  hashTable->clear(); //only deletes HashNodes
  doublyLinkedList->clear(); //deletes the DllNodes
}

/**
* @brief Retrieve an item from the CacheManager.
* @param curKey Key of the item to retrieve.
* @return Pointer to the DllNode, or nullptr if not found.
*/
DllNode* CacheManager::getItem(int curKey) {
  HashNode* found = hashTable->getItem(curKey); //fast lookup through the table
  if (found == nullptr) {
    return nullptr; //not in the cache
  }
  return found->getFifoNode(); //hash node points to the list node with the data
}

/**
* @brief Retrieve the max size of the cache.
* @return Maximum number of entries the cache can hold.
*/
int CacheManager::getMaxCacheSize() {
  return maxCacheSize;
}

/**
* @brief Check if a node with the key exists in the cache.
* @param curKey Key to look for.
* @return True if the key exists, false otherwise.
*/
bool CacheManager::contains(int curKey) {
  return hashTable->contains(curKey);
}

/**
* @brief Prints the current contents of the cache to console and output file.
*/
void CacheManager::printCache() {
  logToFileAndConsole("\n\nPrinting out the cache contents");
  doublyLinkedList->printList(); //prints FIFO list
  hashTable->printTable(); //prints every bucket
  logToFileAndConsole("\nEnd of cache contents");
}