/**
 * @file doubly_linked_list.cpp
 * @brief Implements DoublyLinkedList methods.
 * @date 09/09/2026 - Created adn implemented doubly linked list methods
   @date 10/14/2026 - Added getSize() method, added correct documentation
 * @author Isabela Escobedo Luna
*/

#include "doubly_linked_list.h"
#include "milestone3.h"
#include <string>

/**
 * @brief Constructs an empty doubly linked list.
 *
 * Initializes the head and tail pointers to nullptr.
 */
DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

/**
 * @brief Destroys the doubly linked list.
 *
 * Releases all nodes owned by the list by calling clear().
 */
DoublyLinkedList::~DoublyLinkedList() {
  clear();
}

/**
 * @brief Check if the list is empty.
 * @return True if node is emmpty.
 */
bool DoublyLinkedList::isEmpty() {
  return head == nullptr;
}

/**
 * @brief Adds a new node at the beginning of the list
 * @param key The key of the node to be added.
 */
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

/**
 * @brief Adds a new node at the end of the list.
 * @param key The key of the node to be added.
 */
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
 * @param key The key of the node to remove
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
 * @brief Removes header node.
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
 * @brief Removes tail node.
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
 * @brief Moves a specific node to the front.
 * @param key The key of the node to be moved.
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
 * @brief Moves a specific node to the end.
 * @param key The key of the node to be moved.
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
 * @brief Clear the list.
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
 * @brief Print the doubly linked list
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
 * @brief Reverse print the double linked list.
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

//ADD!!!!
//getSize() and its documentation
/**
 * @brief Gets the size of the soubly linked list
 * @return The number of nodes in the list
 */
int DoublyLinkedList::getSize(){
  return size;
}