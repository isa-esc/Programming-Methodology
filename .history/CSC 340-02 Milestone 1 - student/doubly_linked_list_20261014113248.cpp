/**
 * @file doubly_linked_list.cpp
 * @brief Implements DoublyLinkedList methods.
 * @date 09/09/2026
 * @author Isabela Escobedo Luna
*/

#include "doubly_linked_list.h"
#include "milestone1.h"
#include <string>

// Constructor
DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

// Destructor
DoublyLinkedList::~DoublyLinkedList() {
  clear();
}

// isEmpty - Check if the list if empty
bool DoublyLinkedList::isEmpty() {
  return head == nullptr;
}

// insertAtHead - Adds a new node at the beginning of the list
void DoublyLinkedList::insertAtHead(int key) {
  DllNode* newNode = new DllNode(key);

  if (isEmpty()) {
    // list is empty: new node becomes both head and tail
    head = newNode;
    tail = newNode;
  } else {
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
  }
}

// insertAtTail - Adds a new node at the end of the list
void DoublyLinkedList::insertAtTail(int key) {
  DllNode* newNode = new DllNode(key);

  if (isEmpty()) {
    // list is empty: new node becomes both head and tail
    head = newNode;
    tail = newNode;
  } else {
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
  }
}

// remove - searches for a node with a specific value and deletes it from the list
void DoublyLinkedList::remove(int key) {
  DllNode* current = head;

  while (current != nullptr) {
    if (current->key == key) {
      // unlink current from its neighbors
      if (current->prev != nullptr) {
        current->prev->next = current->next;
      } else {
        // current was the head
        head = current->next;
      }

      if (current->next != nullptr) {
        current->next->prev = current->prev;
      } else {
        // current was the tail
        tail = current->prev;
      }

      delete current;
      return; // remove only the first match found
    }
    current = current->next;
  }
}

// removeHeaderNode - removes header node
void DoublyLinkedList::removeHeaderNode() {
  if (isEmpty()) {
    return;
  }

  DllNode* oldHead = head;
  head = head->next;

  if (head != nullptr) {
    head->prev = nullptr;
  } else {
    // list is now empty
    tail = nullptr;
  }

  delete oldHead;
}

//removeTailNode - removes tail node
void DoublyLinkedList::removeTailNode() {
  if (isEmpty()) {
    return;
  }

  DllNode* oldTail = tail;
  tail = tail->prev;

  if (tail != nullptr) {
    tail->next = nullptr;
  } else {
    // list is now empty
    head = nullptr;
  }

  delete oldTail;
}

// moveNodeToHead - moves a specific node to the front
void DoublyLinkedList::moveNodeToHead(int key) {
  DllNode* current = head;

  while (current != nullptr) {
    if (current->key == key) {
      // already at head; nothing to do
      if (current == head) {
        return;
      }

      // unlink current from its current position
      if (current->prev != nullptr) {
        current->prev->next = current->next;
      }
      if (current->next != nullptr) {
        current->next->prev = current->prev;
      } else {
        // current was the tail
        tail = current->prev;
      }

      // insert current at the head
      current->prev = nullptr;
      current->next = head;
      if (head != nullptr) {
        head->prev = current;
      }
      head = current;
      return;
    }
    current = current->next;
  }
}

// moveNodeToTail - moves a specific node to the end
void DoublyLinkedList::moveNodeToTail(int key) {
  DllNode* current = head;

  while (current != nullptr) {
    if (current->key == key) {
      // already at tail; nothing to do
      if (current == tail) {
        return;
      }

      // unlink current from its current position
      if (current->prev != nullptr) {
        current->prev->next = current->next;
      } else {
        // current was the head
        head = current->next;
      }
      if (current->next != nullptr) {
        current->next->prev = current->prev;
      }

      // insert current at the tail
      current->next = nullptr;
      current->prev = tail;
      if (tail != nullptr) {
        tail->next = current;
      }
      tail = current;
      return;
    }
    current = current->next;
  }
}

// clear - clear the list
void DoublyLinkedList::clear() {
  DllNode* current = head;

  while (current != nullptr) {
    DllNode* next = current->next;
    delete current;
    current = next;
  }

  head = nullptr;
  tail = nullptr;
}

// printList - print the doubly linked list
void DoublyLinkedList::printList() {
  logToFileAndConsole("\nHere are the List contents:");

  DllNode* current = head;
  while (current != nullptr) {
    current->printNode();
    current = current->next;
  }

  logToFileAndConsole("End of List");
}

// reversePrintList - reverse print the doubly linked list
void DoublyLinkedList::reversePrintList() {
  logToFileAndConsole("\nHere are the List contents reversed:");

  DllNode* current = tail;
  while (current != nullptr) {
    current->printNode();
    current = current->prev;
  }

  logToFileAndConsole("End of List");
}