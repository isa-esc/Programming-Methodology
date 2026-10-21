/**
 * @file doubly_linked_list.cpp
 * @brief Implements DoublyLinkedList methods.
 * @date 09/09/2026 - Created and implemented doubly linked list methods
 * @date 10/14/2026 - Added getSize() and size tracking; insertAtHead/insertAtTail
 *                    now take a DllNode*; changed include to milestone3.h;
 *                    printList output now matches the expected FIFO format.
 * @author Isabela Escobedo Luna
*/

#include "doubly_linked_list.h"
#include "milestone3.h"
#include <string>

/**
 * @brief Constructs an empty doubly linked list.
 */
DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

/**
 * @brief Destroys the doubly linked list.
 */
DoublyLinkedList::~DoublyLinkedList() {
  clear();
}

/**
 * @brief Gets the size of the doubly linked list.
 * @return The number of nodes in the list.
 */
int DoublyLinkedList::getSize() {
  return size;
}

/**
 * @brief Check if the list is empty.
 * @return True if the list is empty.
 */
bool DoublyLinkedList::isEmpty() {
  return head == nullptr;
}

/**
 * @brief Adds a new node at the beginning of the list.
 * @param key The key of the node to be added.
 * @param newNode Pointer to the node to insert (created if nullptr).
 */
void DoublyLinkedList::insertAtHead(int key, DllNode* newNode) {
  //if no node was passed in, make one with just the key
  if (newNode == nullptr) {
    newNode = new DllNode(key);
  }
  newNode->key = key;
  newNode->prev = nullptr; //clears old links
  newNode->next = nullptr;

  if (isEmpty()) {
    // list is empty
    head = newNode;
    tail = newNode;
  } else {
    // new node becomes first node
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
  }
  size++;
}

/**
 * @brief Adds a new node at the end of the list.
 * @param key The key of the node to be added.
 * @param newNode Pointer to the node to insert (created if nullptr).
 */
void DoublyLinkedList::insertAtTail(int key, DllNode* newNode) {
  //if no node was passed in, make one with just the key
  if (newNode == nullptr) {
    newNode = new DllNode(key);
  }
  newNode->key = key;
  newNode->prev = nullptr; //clears old links
  newNode->next = nullptr;

  if (isEmpty()) {
    // list is empty
    head = newNode;
    tail = newNode;
  } else {
    // new node becomes last node
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
  }
  size++;
}

/**
 * @brief Searches for a node with a specific value and deletes it from the list.
 * @param key The key of the node to remove.
 */
void DoublyLinkedList::remove(int key) {
  DllNode* current = head;

  //goes through entire list
  while (current != nullptr) {
    if (current->key == key) {
      // unlinks current node
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
      size--;
      return;
    }
    current = current->next;
  }
}

/**
 * @brief Removes header node.
 */
void DoublyLinkedList::removeHeaderNode() {
  if (isEmpty()) {
    return; //nothing in list
  }

  DllNode* oldHead = head;
  head = head->next; //next node becomes the new head

  if (head != nullptr) {
    head->prev = nullptr;
  } else {
    // list is empty
    tail = nullptr;
  }

  delete oldHead;
  size--;
}

/**
 * @brief Removes tail node.
 */
void DoublyLinkedList::removeTailNode() {
  if (isEmpty()) {
    return; //nothing in list
  }

  DllNode* oldTail = tail;
  tail = tail->prev; //previous node becomes the new tail

  if (tail != nullptr) {
    tail->next = nullptr;
  } else {
    // list is empty
    head = nullptr;
  }

  delete oldTail;
  size--;
}

/**
 * @brief Moves a specific node to the front.
 * @param key The key of the node to be moved.
 */
void DoublyLinkedList::moveNodeToHead(int key) {
  DllNode* current = head;

  while (current != nullptr) {
    if (current->key == key) {
      // node already in head
      if (current == head) {
        return;
      }

      // unlink node
      if (current->prev != nullptr) {
        current->prev->next = current->next;
      }
      if (current->next != nullptr) {
        current->next->prev = current->prev;
      } else {
        // current was the tail
        tail = current->prev;
      }

      // insert current at head
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
      // node was already at tail
      if (current == tail) {
        return;
      }

      // unlink node
      if (current->prev != nullptr) {
        current->prev->next = current->next;
      } else {
        // current was the head
        head = current->next;
      }
      if (current->next != nullptr) {
        current->next->prev = current->prev;
      }

      // insert current at tail
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
 * @brief Clear the list (delete all nodes).
 */
void DoublyLinkedList::clear() {
  DllNode* current = head;

  //delete node by node
  while (current != nullptr) {
    DllNode* next = current->next;
    delete current;
    current = next; // moves to next node
  }

  // empty
  head = nullptr;
  tail = nullptr;
  size = 0;
}

/**
 * @brief Prints the list from head to tail to the console and output file.
 */
void DoublyLinkedList::printList() {
  logToFileAndConsole("\nHere are the FIFO List contents:");

  //starts at head
  DllNode* current = head;
  while (current != nullptr) {
    logToFileAndConsole("FIFO Node key: " + std::to_string(current->key));
    current = current->next;
  }

  logToFileAndConsole("End of FIFO List");
}

/**
 * @brief Prints the list from tail to head to the console and output file.
 */
void DoublyLinkedList::reversePrintList() {
  logToFileAndConsole("\nHere are the FIFO List contents reversed:");

  //starts at tail
  DllNode* current = tail;
  while (current != nullptr) {
    logToFileAndConsole("FIFO Node key: " + std::to_string(current->key));
    current = current->prev;
  }

  logToFileAndConsole("End of FIFO List reversed");
}