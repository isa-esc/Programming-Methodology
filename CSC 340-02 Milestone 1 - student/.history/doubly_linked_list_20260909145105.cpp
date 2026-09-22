/**
 * @file doubly_linked_list.cpp
 * @brief Implementation of the DoublyLinkedList class.
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

/**
 * @brief Searches for a node with a specific value and deletes it from the list.
 *
 * Traverses the list from head to tail looking for the first node whose
 * key matches the given value. If found, the node is unlinked from the
 * list (updating head/tail pointers as necessary) and its memory is freed.
 * If no matching node is found, the list is left unchanged.
 *
 * @param key Value to search for and remove.
 */
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

/**
 * @brief Removes the head node of the list.
 *
 * If the list is empty, this function does nothing. Otherwise the
 * current head is deleted and the new head becomes the node that
 * followed it (or nullptr, and tail is also set to nullptr, if the
 * list becomes empty).
 */
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

/**
 * @brief Removes the tail node of the list.
 *
 * If the list is empty, this function does nothing. Otherwise the
 * current tail is deleted and the new tail becomes the node that
 * preceded it (or nullptr, and head is also set to nullptr, if the
 * list becomes empty).
 */
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

/**
 * @brief Moves a specific node to the front of the list.
 *
 * Searches for the node with the given key. If found and it is not
 * already the head, the node is unlinked from its current position and
 * re-inserted at the head of the list. If the key is not found, the
 * list is left unchanged.
 *
 * @param key Value identifying the node to move.
 */
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

/**
 * @brief Moves a specific node to the end of the list.
 *
 * Searches for the node with the given key. If found and it is not
 * already the tail, the node is unlinked from its current position and
 * re-inserted at the tail of the list. If the key is not found, the
 * list is left unchanged.
 *
 * @param key Value identifying the node to move.
 */
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

/**
 * @brief Clears the list, deleting all nodes.
 *
 * Traverses the list from head to tail, deleting each node, and resets
 * head and tail to nullptr, leaving the list empty.
 */
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

/**
 * @brief Prints the doubly linked list from head to tail.
 *
 * Output is written to both the console and the output file (via
 * logToFileAndConsole/DllNode::printNode), matching the format used in
 * the sample output file.
 */
void DoublyLinkedList::printList() {
  logToFileAndConsole("\nHere are the List contents:");

  DllNode* current = head;
  while (current != nullptr) {
    current->printNode();
    current = current->next;
  }

  logToFileAndConsole("End of List");
}

/**
 * @brief Prints the doubly linked list from tail to head.
 *
 * Output is written to both the console and the output file (via
 * logToFileAndConsole/DllNode::printNode), matching the format used in
 * the sample output file.
 */
void DoublyLinkedList::reversePrintList() {
  logToFileAndConsole("\nHere are the List contents reversed:");

  DllNode* current = tail;
  while (current != nullptr) {
    current->printNode();
    current = current->prev;
  }

  logToFileAndConsole("End of List");
}