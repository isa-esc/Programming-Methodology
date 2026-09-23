/**
 * @file hash_table.cpp
 * @brief This file uses the deared files provided to implement a fully functional hash table
 * @date 09/22/2026
 * @author Isabela Escobedo Luna
 */

#include "hash_node.h"
#include "hash_table.h"
#include "milestone2.h"
#include <string>

/**
 * @brief Gets the internal array of bucket pointers.
 * @return A pointer to the array of HashNode pointers.
 */
HashNode** HashTable::getTable(){
  return table;
}

/**
 * @brief Gets the number of buckets in the hash table.
 * @return The number of buckets (table size).
 */
int HashTable::getSize(){
  return numberOfBuckets;
}

/**
 * @brief Calculates the hash code for a given key.
 * @param currentKey The key for which the hash code is to be calculated.
 * @return The computed hash code (bucket index).
 */
int HashTable::calculateHashCode(int currentKey){
  return currentKey % numberOfBuckets; //will return hash code
}

/**
 * @brief Checks whether the hash table is empty.
 * @return True if the table has no entries, false otherwise.
 */
bool HashTable::isEmpty(){ 
  return numberOfItems == 0; //evaluates and returns boolean in one line
}

/**
 * @brief Gets the number of items currently stored in teh table.
 * @return The number of items in the table.
 */
int HashTable::getNumberOfItems(){
  return numberOfItems;
}

/**
 * @brief Adds a new node to the table.
 * @param curKey The key associated with the node.
 * @param myNode Pointer to the node to be added.
 * @return True if insertion is successful
 */
bool HashTable::add(int curKey, HashNode* myNode){
  int index = calculateHashCode(curKey); //get index of curKey
  if(table[index] == nullptr){
    table[index] = myNode; //adds node to the empty bucket
    myNode->prev = nullptr;
    myNode->next = nullptr;
  }
  else{ //adds new node at the front of the chain
    myNode->next = table[index];
    myNode->prev = nullptr;
    table[index]->prev = myNode;
    table[index] = myNode;
  }

  numberOfItems++;
  return true; //successfully added
}

/**
 * @brief Removes a node with the specified key from the table.
 * @param curKey The key of the node to remove.
 * @return True if the node was successfully removed; false if not found.
 */
bool HashTable::remove(int curKey){
  int index = calculateHashCode(curKey);
  if(table[index] == nullptr){
    return false; //did not exist
  }

  HashNode* currentNode = table[index]; //point to first node in bucket
  while(currentNode != nullptr){ //runs through the whole bucket
    if(currentNode->key == curKey){ //will be true when we find curKey
      if(currentNode->prev == nullptr){
        table[index] = currentNode->next; //next node becomes the firts node

        if(table[index] != nullptr){
          table[index]->prev = nullptr;
        }
      }
      else{
        //previous node becomes connected to next node, skipping current
        currentNode->prev->next = currentNode->next;

        //in case there is another node
        if(currentNode->next != nullptr){
          currentNode->next->prev = currentNode->prev;
        }
      }
      delete currentNode; //current node gets deleted
      numberOfItems--;
      return true; //node got succesfully deleted, exits
    }
    currentNode = currentNode->next; //continues searching
  }
  return false; //node not found, return false

}

/**
 * @brief Clears the entire hash table by deleting all entries.
 */
void HashTable::clear(){
  //delete node by node
  for(int i = 0; i <numberOfBuckets; i++){
    HashNode* currentNode = table[i];
    while(currentNode != nullptr){
      HashNode* nextNode = currentNode->next;
      delete currentNode;
      currentNode = nextNode; //move to next node
    }
    table[i] = nullptr; //eventually empties the bucket
  }
  numberOfItems = 0;
}

/**
 * @brief Retrieves the node associaeted with a given key.
 * @param curKey The key to look up.
 * @return Pointer to the corresponding HashNode, or nullptr if not found.
 */
HashNode* HashTable::getItem(int curKey){
  //calculate bucket to search in
  int index = calculateHashCode(curKey);
  HashNode* currentNode = table[index];
  
  //search for node
  while(currentNode != nullptr){
    if(currentNode->key == curKey){
      return currentNode; //found, return
    }
    currentNode = currentNode->next; //move on to next node
  }

  return nullptr; //nothing was found
}

/**
 * @brief Checks if a node with the given key exists in the table.
 * @param curKey The key to search for.
 * @return True if the key is found; false otherwise.
 */
bool HashTable::contains(int curKey){
  //use getItem's search feature to check if item exists
  if(getItem(curKey) != nullptr){
    return true; //getItem did not return a nullptr
  }
  else return false;  //not found
}

/**
 * @brief Prints the contents of the hash table.
 * 
 * Outputs each bucket and the nodes it contains to both the console
 * and the output log (via logToFileAndConsole).
 */
void HashTable::printTable(){
  //goes through all buckets
  for(int i = 0; i < numberOfBuckets; i++){
    HashNode* currentNode = table[i];

    while(currentNode != nullptr){
      currentNode->printNode(true);
      currentNode = currentNode->next;
    }
  }
}