#pragma once

#include "BSNodeStruct.h"
#include "BinaryFile.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

// Binary search tree
class BSTree
{
public:
	BSTree() : root(nullptr) {};

	BSTree(BinaryFile file);

	// Insert a new node into the tree
	void insert(string key, TestData value);

	// Search for a node in the tree
	Node* search(string key);

	// Delete a node from the tree
	void remove(string key);

	// Print the tree
	void print();
	
private:	
	// Root node of the tree
	Node* root;

	// Insert a new node into the binary search tree
	void insert(Node* node, string key, TestData value);

	// Search for a node in the tree
	Node* search(Node* node, string key);

	// Delete a node from the tree
	void remove(Node*& node, string key);

	// Print the tree
	void print(Node* node, size_t level);

	// Keys comparator
	bool compare(string key1, string key2);

	// Delete the tree
	void deleteTree(Node* node);
};