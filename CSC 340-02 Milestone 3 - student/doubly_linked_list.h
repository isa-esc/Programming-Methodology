/**
 * @file doubly_linked_list.h
 * @author Hugh Hui
 * @brief Declares the DoublyLinkedList class and its operations.
 *
 * @date 2024-12-30 Created by H. Hui
 * @date 2025-06-05 Modified by H. Hui; added additional doxygen style comments
 */

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>
#include <fstream>
#include <string>

#include "dll_node.h"

 /**
  * @class DoublyLinkedList
  * @brief Implements a doubly linked list structure for managing a collection of DllNode elements.
  */
class DoublyLinkedList {
public:
    DllNode* head;  /**< Pointer to the first node in the list. */
    DllNode* tail;  /**< Pointer to the last node in the list. */
    int size;       /**< Current number of nodes in the list. */

    /**
     * @brief Constructs an empty doubly linked list.
     */
    DoublyLinkedList();

    /**
     * @brief Destroys the list and releases all memory.
     */
    ~DoublyLinkedList();

    /**
     * @brief Returns the number of entries in the list.
     * @return Number of nodes in the list.
     */
    int getSize();

    /**
     * @brief Checks whether the list is empty.
     * @return True if the list is empty, false otherwise.
     */
    bool isEmpty();

    /**
     * @brief Inserts a new node at the head of the list.
     * @param key Integer key for the new node.
     * @param newNode Pointer to the node to insert.
     */
    void insertAtHead(int key, DllNode* newNode);

    /**
     * @brief Inserts a new node at the tail of the list.
     * @param key Integer key for the new node.
     * @param newNode Pointer to the node to insert.
     */
    void insertAtTail(int key, DllNode* newNode);

    /**
     * @brief Removes the node with the given key from the list.
     * @param key The key of the node to remove.
     */
    void remove(int key);

    /**
     * @brief Removes the first node (head) of the list.
     */
    void removeHeaderNode();

    /**
     * @brief Removes the last node (tail) of the list.
     */
    void removeTailNode();

    /**
     * @brief Moves the node with the given key to the head of the list.
     * @param key Key of the node to move.
     */
    void moveNodeToHead(int key);

    /**
     * @brief Moves the node with the given key to the tail of the list.
     * @param key Key of the node to move.
     */
    void moveNodeToTail(int key);

    /**
     * @brief Clears the list by deleting all nodes.
     */
    void clear();

    /**
     * @brief Prints the list from head to tail to the console and output file.
     */
    void printList();

    /**
     * @brief Prints the list from tail to head to the console and output file.
     */
    void reversePrintList();
};

#endif // DOUBLY_LINKED_LIST_H
