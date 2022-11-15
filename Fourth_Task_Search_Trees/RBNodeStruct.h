#pragma once

#include "DataStruct.h"

enum Color { RED, BLACK };

// Red-black tree node
struct RBNode 
{
	string key;
	TestData value;
	RBNode* left;
	RBNode* right;
	RBNode* parent;
	bool color;

	RBNode() : 
		key(""), 
		value(), 
		left(nullptr), 
		right(nullptr), 
		parent(nullptr), 
		color(RED) 
	{};

	RBNode(TestData value) : 
		value(value), 
		left(nullptr), 
		right(nullptr), 
		parent(nullptr), 
		color(RED)
	{
		key = value.key_number;
	}

	// Copy constructor
	RBNode(const RBNode& other) :
		key(other.key),
		value(other.value),
		left(other.left),
		right(other.right),
		parent(other.parent),
		color(other.color)
	{};

	// Find node uncle
	RBNode* uncle()
	{
		if (parent == nullptr || parent->parent == nullptr)
		{
			return nullptr;
		}
		else if (parent == parent->parent->left)
		{
			return parent->parent->right;
		}
		else
		{
			return parent->parent->left;
		}
	}

	// Find node grandparent
	RBNode* grandparent()
	{
		if (parent == nullptr)
		{
			return nullptr;
		}
		else
		{
			return parent->parent;
		}
	}
};