#pragma once

#include "RBNodeStruct.h"
#include "BinaryFile.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

// Red-black tree
class RBTree
{
public:
	RBTree() : root(nullptr) {};

	RBTree(BinaryFile file);

	// Insert a new node into the tree
	void insert(string key, TestData value);

	// Search for a node in the tree
	RBNode* search(string key);

	// Delete a node from the tree
	void remove(string key);

	// Print the tree
	void print();

	// Getter for rotations_count
	size_t get_rotations_count() { return rotations_count; }
	
private:

	// Root node of the tree
	RBNode* root;

	size_t rotations_count;
	
	void insertFixUp(RBNode* node);

	// Search for a node in the tree
	RBNode* search(RBNode* node, string key);

	void remove(RBNode* node);
	
	void removeFixUp(RBNode* node, RBNode* parent);

	// Print the tree
	void print(RBNode* node, size_t level);

	// Keys comparator
	bool compare(string key1, string key2);

	// Delete the tree
	void deleteTree(RBNode* node);

	// Rotate the tree to the left
	void rotateLeft(RBNode*& node);

	// Rotate the tree to the right
	void rotateRight(RBNode*& node);

};