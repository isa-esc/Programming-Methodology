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
  return numberOfItems == 0; //evaluates and returns boolean in one line
}

//getNumberOfItems
int HashTable::getNumberOfItems(){
  return numberOfItems;
}

//add
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
}


//remove


//clear


//getItem


//contains


//printTable
