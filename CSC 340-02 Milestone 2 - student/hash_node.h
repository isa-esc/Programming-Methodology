/**
 * @author Hugh Hui
 * @file hash_node.h
 * @brief Node struct header file for HashTable, used in hash_table.cpp
 * @date 2025-01-16 - initial creation and comments
 * @date 2025-05-31 - H. Hui added additional doxygen style comments
 * @date 2026-06-03 - H. Hui added boolean parameter for printNode
  */

#ifndef _HASH_NODE
#define _HASH_NODE

#include <string>

/**
 * @brief Structure representing a node in the hash table.
 */
struct HashNode {
	int key;               ///< The key for this node
	int hashCode;          ///< Hash code computed using the key

	std::string fullName;  ///< Full name associated with the key
	std::string address;   ///< Address
	std::string city;      ///< City
	std::string state;     ///< State
	std::string zip;       ///< Zip code

	HashNode* prev;        ///< Pointer to previous node in list
	HashNode* next;        ///< Pointer to next node in list

	/**
	 * @brief Constructs a new HashNode with given data.
	 *
	 * @param val Key value
	 * @param myFullName Full name
	 * @param myAddress Address
	 * @param myCity City
	 * @param myState State
	 * @param myZip Zip code
	 */
	HashNode(int val, std::string myFullName, std::string myAddress, std::string myCity, std::string myState, std::string myZip);

	/**
	 * @brief Logs node information to console and file.
	 */
	void printNode(bool verbose);
};

#endif
