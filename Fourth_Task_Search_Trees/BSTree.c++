#include <iostream>

#include "BSTree.h"

BSTree::BSTree(BinaryFile file) : root(nullptr)
{
	vector<TestData> data = file.read();

	for (TestData data_cell : data)
	{
		insert(data_cell.key_number, data_cell);
	}
}

// Insert a new node into the binary search tree
void BSTree::insert(string key, TestData value)
{
	if (root == nullptr)
	{
		root = new Node(value);
	}
	else
	{
		insert(root, key, value);
	}
}

// Insert a node into the binary search tree
void BSTree::insert(Node* node, string key, TestData value)
{
	if (compare(key, node->key))
	{
		if (node->left == nullptr)
		{
			node->left = new Node(value);
		}
		else
		{
			insert(node->left, key, value);
		}
	}
	else if (compare(node->key, key))
	{
		if (node->right == nullptr)
		{
			node->right = new Node(value);
		}
		else
		{
			insert(node->right, key, value);
		}
	}
}

Node* BSTree::search(string key)
{
	return search(root, key);
}

Node* BSTree::search(Node* node, string key)
{
	if (node == nullptr)
	{
		return nullptr;
	}
	else if (compare(node->key, key))
	{
		return search(node->right, key);
	}
	else if (compare(key, node->key))
	{
		return search(node->left, key);
	}
	else
	{
		return node;
	}
}

void BSTree::remove(string key)
{
	remove(root, key);
}

void BSTree::remove(Node*& node, string key)
{
	if (node == nullptr)
	{
		return;
	}
	else if (compare(key, node->key))
	{
		remove(node->left, key);
	}
	else if (compare(node->key, key))
	{
		remove(node->right, key);
	}
	else
	{
		if (node->left == nullptr && node->right == nullptr)
		{
			delete node;
			node = nullptr;
		}
		else if (node->left == nullptr)
		{
			Node* temp = node;
			node = node->right;
			delete temp;
		}
		else if (node->right == nullptr)
		{
			Node* temp = node;
			node = node->left;
			delete temp;
		}
		else
		{
			Node* temp = node->right;
			while (temp->left != nullptr)
			{
				temp = temp->left;
			}
			node->key = temp->key;
			node->value = temp->value;
			remove(node->right, temp->key);
		}
	}
}

void BSTree::print()
{
	print(root, 0);
}

void BSTree::print(Node* node, size_t level)
{
	if (node != nullptr)
	{
		print(node->right, level + 1);
		for (size_t i = 0; i < level; i++)
		{
			std::cout << "    ";
		}
		std::cout << node->key << std::endl;
		print(node->left, level + 1);
	}
}

bool BSTree::compare(string key1, string key2)
{
	return stoi(key1) < stoi(key2);
}

void BSTree::deleteTree(Node* node)
{
	if (node == nullptr)
	{
		return;
	}
	deleteTree(node->left);
	deleteTree(node->right);
	delete node;
}