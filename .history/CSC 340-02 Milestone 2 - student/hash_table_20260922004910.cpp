/**
 * @file hash_table.cpp
 * @brief ADD A DESCRIPTION
 * @date 09/21/2026
 * @author Isabela Escobedo Luna
*/

#include "hash_node.h"
#include "hash_table.h"
#include "milestone2.h"
#include <string>

//getTable
HashNode** HashTable::getTable(){
  return table;
}

//getSize
int HashTable::getSize(){
  return numberOfBuckets;
}

//calculateHashCode
int HashTable::calculateHashCode(int currentKey){
  return currentKey % numberOfBuckets; //will return hash code
}

//isEmpty
bool HashTable::isEmpty(){
  return numberOfItems == 0;
}

//getNumberOfItems


//add


//remove


//clear


//getItem


//contains


//printTable
