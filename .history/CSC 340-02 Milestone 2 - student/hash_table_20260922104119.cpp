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

  numberOfItems++;
  return true; //successfully added
}

//remove
bool HashTable::remove(int curKey){
  int index = calculateHashCode(curKey);
  if(table[index] == nullptr){
    return false; //did not exist
  }

  HashNode* current = table[index]; //point to current bucket
  while(current != nullptr){ //runs through the whole bucket
    if(current->key == curKey){ //will be true when we find curKey
      table[index] = current->next;
      if(current->prev == nullptr){
        table[index] = current->next; //next node becomes the firts node

        if(table[index] != nullptr){
          table[index]->prev = nullptr;
        }
      }
    }
    else{
      //previous node becomes connected to next node, skipping current
      current->prev->next = current->next;

    }
  }
}

//clear


//getItem


//contains


//printTable
