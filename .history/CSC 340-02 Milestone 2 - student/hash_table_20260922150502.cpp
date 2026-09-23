/**
 * @file hash_table.cpp
 * @brief This file uses the deared files provided to implement a fully functional hash table
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

//clear
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

//getItem
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

//contains
bool HashTable::contains(int curKey){
  //use getItem's search feature to check if item exists
  if(getItem(curKey) != nullptr){
    return true; //getItem did not return a nullptr
  }
  else return false;  //not found
}

//printTable
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