/**
 * @file binary_search_tree.cpp
 * @brief Implementation of Binary Search Tree operations
 * @date 11/04/2026 - Created and implemented BST methods
 * @author Isabela Escobedo Luna
*/

#include "binary_search_tree.h"
#include "milestone4.h"
#include "tree_node.h"
#include <algorithm>
#include <queue>
#include <string>
#include <vector>

/**
* @brief Constructor
*/
BinarySearchTree::BinarySearchTree() : root(nullptr) {}

/**
* @brief Destructor
*/
BinarySearchTree::~BinarySearchTree() {
  deleteTree(root);
  root = nullptr;
}

/**
* @brief Add a key to the tree
* @param key Key to be added
*/
void BinarySearchTree::addToTree(int key) {
  std::vector<TreeNode*> path; //nodes passed on the way down
  TreeNode* cur = root;

  //walks down to the empty spot
  while (cur != nullptr) {
    if (key == cur->key) {
      return; //was already in the tree
    }
    path.push_back(cur);
    cur = (key < cur->key) ? cur->left : cur->right;
  }

  TreeNode* newNode = new TreeNode(key, 1, 1, nullptr, nullptr);
  if (path.empty()) {
    root = newNode;
  }
  else if (key < path.back()->key) {
    path.back()->left = newNode;
  }
  else {
    path.back()->right = newNode;
  }

  //update height and node count from the parent up to the root
  for (int i = (int)path.size() - 1; i >= 0; i--) {
    TreeNode* n = path[i];
    n->height = 1 + std::max(getHeight(n->left), getHeight(n->right));
    n->numberOfNodes = 1 + (n->left ? n->left->numberOfNodes : 0)
                         + (n->right ? n->right->numberOfNodes : 0);
  }
}

/**
* @brief Remove a specific key from the BST
* @param key Key to be removed
* @return True if removed, false if the key not found
*/
bool BinarySearchTree::removeNode(int key) {
  std::vector<TreeNode*> path; //ancestors of the node being deleted
  TreeNode* cur = root;

  //find the key
  while (cur != nullptr && cur->key != key) {
    path.push_back(cur);
    cur = (key < cur->key) ? cur->left : cur->right;
  }
  if (cur == nullptr) {
    return false; //key not in tree
  }

  TreeNode* target = cur; //node that will be deleted
  if (cur->left != nullptr && cur->right != nullptr) {
    //two children, smallest key on the right
    path.push_back(cur);
    target = cur->right;
    while (target->left != nullptr) {
      path.push_back(target);
      target = target->left;
    }
    cur->key = target->key; //copy successor key
  }

  //target one child, will connect to parent
  TreeNode* child = (target->left != nullptr) ? target->left : target->right;
  if (path.empty()) {
    root = child;
  }
  else if (path.back()->left == target) {
    path.back()->left = child;
  }
  else {
    path.back()->right = child;
  }
  delete target;

  //update height and node count from parent to root
  for (int i = (int)path.size() - 1; i >= 0; i--) {
    TreeNode* n = path[i];
    n->height = 1 + std::max(getHeight(n->left), getHeight(n->right));
    n->numberOfNodes = 1 + (n->left ? n->left->numberOfNodes : 0)
                         + (n->right ? n->right->numberOfNodes : 0);
  }
  return true;
}

/**
* @brief Get the height of the tree
* @return Height of the tree
*/
int BinarySearchTree::getHeightOfTree() const {
  return getHeight(root);
}

/**
* @brief Get the total number of nodes in the tree
* @return Number of nodes
*/
int BinarySearchTree::getNumberOfTreeNodes() const {
  return root ? root->numberOfNodes : 0; //root already kept count
}

/**
* @brief Check if a key is in the BST
* @param key Key to look for
* @return Whether it was found or not
*/
bool BinarySearchTree::contains(int key) const {
  TreeNode* cur = root;
  while (cur != nullptr) {
    if (key == cur->key) {
      return true;
    }
    cur = (key < cur->key) ? cur->left : cur->right;
  }
  return false;
}

/**
* @brief Getter for the root node of the tree
* @return A pointer to the root
*/
TreeNode* BinarySearchTree::getRoot() const {
  return root;
}

/**
* @brief Check if a BST is empty
* @return True if empty
*/
bool BinarySearchTree::isEmpty() const {
  return root == nullptr;
}

/**
* @brief Removes tree
*/
void BinarySearchTree::clear() {
  deleteTree(root);
  root = nullptr;
}

/**
* @brief Print the node from the binary search tree
* @param node Pointer to the node that is to be printed
*/
void BinarySearchTree::printNodeFromTree(TreeNode* node) const {
  if (node == nullptr) {
    return;
  }
  logToFileAndConsole("Node key: " + std::to_string(node->key) +
                      ", number of nodes: " + std::to_string(node->numberOfNodes) +
                      ", height: " + std::to_string(node->height));
}

/**
* @brief Print the binary search tree in an in-order traversal
*/
void BinarySearchTree::printInOrder() const {
  logToFileAndConsole("Performing In-order traversal");
  printInOrderHelper(root);
}

/**
* @brief print the binary search tree in a pre-order traversal
*/
void BinarySearchTree::printPreOrder() const {
  logToFileAndConsole("Performing Pre-order traversal");
  printPreOrderHelper(root);
}

/**
* @brief Print the tree in a post-order traversal
*/
void BinarySearchTree::printPostOrder() const {
  logToFileAndConsole("Performing Post-order traversal");
  printPostOrderHelper(root);
}

/**
* @brief Print the binary search tree in a depth-first-order traversal
*/
void BinarySearchTree::printDepthFirst() const {
  logToFileAndConsole("Performing Depth First via PreOrder traversal");
  printPreOrder();
}

/**
* @brief Print the binary search tree in a breadth-first-order traversal
*/
void BinarySearchTree::printBreadthFirst() const {
  logToFileAndConsole("Performing Breadth First traversal");
  if (root == nullptr) {
    return;
  }

  std::queue<TreeNode*> q;
  q.push(root);
  while (!q.empty()) {
    TreeNode* cur = q.front();
    q.pop();
    logToFileAndConsole("Node key: " + std::to_string(cur->key));
    if (cur->left != nullptr) {
      q.push(cur->left);
    }
    if (cur->right != nullptr) {
      q.push(cur->right);
    }
  }
}

/**
* @brief Deletes the tree starting from the specified node
* @param node Node to start deleting from
*/
void BinarySearchTree::deleteTree(TreeNode* node) {
  if (node == nullptr) {
    return;
  }
  deleteTree(node->left);
  deleteTree(node->right);
  delete node;
}

/**
* @brief Helper function to calculate the height of a node
* @param node Node to be checked
* @return Height of the node, 0 if nullptr
*/
int BinarySearchTree::getHeight(TreeNode* node) const {
  return node ? node->height : 0;
}

/**
* @brief Helper function for recursive in-order traversal
* @param node Current node
*/
void BinarySearchTree::printInOrderHelper(TreeNode* node) const {
  if (node == nullptr) {
    return;
  }
  printInOrderHelper(node->left);
  logToFileAndConsole("Node key: " + std::to_string(node->key));
  printInOrderHelper(node->right);
}

/**
* @brief Helper function for recursive pre-order traversal
* @param node Current node
*/
void BinarySearchTree::printPreOrderHelper(TreeNode* node) const {
  if (node == nullptr) {
    return;
  }
  logToFileAndConsole("Node key: " + std::to_string(node->key));
  printPreOrderHelper(node->left);
  printPreOrderHelper(node->right);
}

/**
* @brief Helper function for recursive post-order traversal
* @param node Current node
*/
void BinarySearchTree::printPostOrderHelper(TreeNode* node) const {
  if (node == nullptr) {
    return;
  }
  printPostOrderHelper(node->left);
  printPostOrderHelper(node->right);
  logToFileAndConsole("Node key: " + std::to_string(node->key));
}