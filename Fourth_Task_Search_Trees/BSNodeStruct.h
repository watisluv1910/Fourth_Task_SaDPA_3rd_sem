#pragma once

#include "DataStruct.h"

// Binary search tree 
struct Node
{
	string key;
	TestData value;
	Node* left;
	Node* right;

	Node() : key(""), value(), left(nullptr), right(nullptr) {};
	
	Node(TestData value) : value(value), left(nullptr), right(nullptr)
	{
		key = value.key_number;
	}

	// Copy constructor
	Node(const Node& other) :
		key(other.key),
		value(other.value),
		left(other.left),
		right(other.right)
	{};
};