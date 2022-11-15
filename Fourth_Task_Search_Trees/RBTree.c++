#include "RBTree.h"

#include <iostream>

RBTree::RBTree(BinaryFile file) : root(nullptr)
{
	vector<TestData> data = file.read();

	for (TestData data_cell : data)
	{
		insert(data_cell.key_number, data_cell);
	}
}

RBNode* RBTree::search(string key)
{
	return search(root, key);
}

// Search element in red-black tree
RBNode* RBTree::search(RBNode* node, string key)
{
	if (node == nullptr)
	{
		return nullptr;
	}
	else if (compare(key, node->key))
	{
		return search(node->left, key);
	}
	else if (compare(node->key, key))
	{
		return search(node->right, key);
	}
	else
	{
		return node;
	}
}

// Compare two strings
bool RBTree::compare(string key1, string key2)
{
	return stoi(key1) < stoi(key2);
}

// Rotate the red-black tree to the left
void RBTree::rotateLeft(RBNode*& node)
{
	RBNode* node_right = node->right;

	node->right = node_right->left;

	if (node->right != nullptr)
		node->right->parent = node;

	node_right->parent = node->parent;

	if (node->parent == nullptr)
		root = node_right;

	else if (node == node->parent->left)
		node->parent->left = node_right;

	else
		node->parent->right = node_right;

	node_right->left = node;
	node->parent = node_right;
	
	rotations_count++;
}

// Rotate the red-black tree to the right
void RBTree::rotateRight(RBNode*& node)
{
	RBNode* node_left = node->left;

	node->left = node_left->right;

	if (node->left != nullptr)
		node->left->parent = node;

	node_left->parent = node->parent;

	if (node->parent == nullptr)
		root = node_left;

	else if (node == node->parent->left)
		node->parent->left = node_left;

	else
		node->parent->right = node_left;

	node_left->right = node;
	node->parent = node_left;

	rotations_count++;
}

// fix the tree after insertion
void RBTree::insertFixUp(RBNode* node)
{
	RBNode* parent = nullptr;
	RBNode* grandparent = nullptr;

	while ((node != root) 
		&& (node->color != BLACK) 
		&& (node->parent->color == RED))
	{
		parent = node->parent;
		grandparent = node->grandparent();

		/*  Case : A 
			Parent of node is left child of Grand-parent of node */
		if (parent == grandparent->left)
		{
			RBNode* uncle = grandparent->right;

			/* Case : 1 
			   The uncle of node is also red 
			   Only Recoloring required */
			if (uncle != nullptr && uncle->color == RED)
			{
				grandparent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				node = grandparent;
			}

			else
			{
				/* Case : 2 
				   node is right child of its parent 
				   Left-rotation required */
				if (node == parent->right)
				{
					rotateLeft(parent);
					node = parent;
					parent = node->parent;
				}
				else
				{
					/* Case : 3
						node is left child of its parent
						Right-rotation required */
					rotateRight(grandparent);
					std::swap(parent->color, grandparent->color);
					node = parent;
				}
			}
		}

		/* Case : B 
		   Parent of node is right child of Grand-parent of node */
		else
		{
			RBNode* uncle = grandparent->left;

			/*  Case : 1 
				The uncle of node is also red 
				Only Recoloring required */
			if ((uncle != nullptr) && (uncle->color == RED))
			{
				grandparent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				node = grandparent;
			}
			else
			{
				/* Case : 2 
				   node is left child of its parent 
				   Right-rotation required */
				if (node == parent->left)
				{
					rotateRight(parent);
					node = parent;
					parent = node->parent;
				}
				else
				{
					/* Case : 3
					   node is right child of its parent
					   Left-rotation required */
					rotateLeft(grandparent);
					std::swap(parent->color, grandparent->color);
					node = parent;
				}
			}
		}
	}	
	root->color = BLACK;
}

// Function to insert a new node with given data
void RBTree::insert(string key, TestData value)
{
	RBNode* node = new RBNode(value);
	RBNode* y = nullptr;
	RBNode* x = this->root;

	while (x != nullptr)
	{
		y = x;
		if (compare(key, x->key))
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}

	node->parent = y;
	if (y == nullptr)
	{
		root = node;
	}
	else if (compare(key, y->key))
	{
		y->left = node;
	}
	else
	{
		y->right = node;
	}

	insertFixUp(node);
}

// Remove red-black tree node
void RBTree::remove(string key)
{
	RBNode* node = search(key);

	if (node != nullptr)
	{
		remove(node);
	}
}

// Remove red-black tree node
void RBTree::remove(RBNode* node)
{
	RBNode* child = nullptr;
	RBNode* parent = nullptr;
	bool color;

	/* node has two children */
	if ((node->left != nullptr) && (node->right != nullptr))
	{
		/* get node's successor */
		RBNode* replace = node;

		/* find successor */
		replace = replace->right;
		while (replace->left != nullptr)
		{
			replace = replace->left;
		}

		/* node's child is replace's child */
		if (node->parent)
		{
			if (node->parent->left == node)
			{
				node->parent->left = replace;
			}
			else
			{
				node->parent->right = replace;
			}
		}
		else
		{
			root = replace;
		}

		/* replace's left child is node's left child */
		child = replace->right;
		parent = replace->parent;
		color = replace->color;

		if (parent == node)
		{
			parent = replace;
		}
		else
		{
			if (child)
			{
				child->parent = parent;
			}
			parent->left = child;

			replace->right = node->right;
			node->right->parent = replace;
		}

		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;

		if (color == BLACK)
		{
			removeFixUp(child, parent);
		}

		delete node;
		return;
	}

	if (node->left != nullptr)
	{
		child = node->left;
	}
	else
	{
		child = node->right;
	}

	parent = node->parent;
	color = node->color;

	if (child)
	{
		child->parent = parent;
	}

	if (parent)
	{
		if (parent->left == node)
		{
			parent->left = child;
		}
		else
		{
			parent->right = child;
		}
	}
	else
	{
		root = child;
	}

	if (color == BLACK)
	{
		removeFixUp(child, parent);
	}

	delete node;
}

// fix the tree after removal
void RBTree::removeFixUp(RBNode* node, RBNode* parent)
{
	RBNode* other = nullptr;

	while ((node == nullptr || node->color == BLACK) && (node != root))
	{
		if (parent->left == node)
		{
			other = parent->right;
			if (other->color == RED)
			{
				other->color = BLACK;
				parent->color = RED;
				rotateLeft(parent);
				other = parent->right;
			}
			if ((other->left == nullptr || other->left->color == BLACK) &&
				(other->right == nullptr || other->right->color == BLACK))
			{
				other->color = RED;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (other->right == nullptr || other->right->color == BLACK)
				{
					other->left->color = BLACK;
					other->color = RED;
					rotateRight(other);
					other = parent->right;
				}
				other->color = parent->color;
				parent->color = BLACK;
				other->right->color = BLACK;
				rotateLeft(parent);
				node = root;
				break;
			}
		}
		else
		{
			other = parent->left;
			if (other->color == RED)
			{
				other->color = BLACK;
				parent->color = RED;
				rotateRight(parent);
				other = parent->left;
			}
			if ((other->left == nullptr || other->left->color == BLACK) &&
				(other->right == nullptr || other->right->color == BLACK))
			{
				other->color = RED;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (other->left == nullptr || other->left->color == BLACK)
				{
					other->right->color = BLACK;
					other->color = RED;
					rotateLeft(other);
					other = parent->left;
				}
				other->color = parent->color;
				parent->color = BLACK;
				other->left->color = BLACK;
				rotateRight(parent);
				node = root;
				break;
			}
		}
	}
	if (node)
	{
		node->color = BLACK;
	}	
}

void RBTree::print()
{
	print(root, 0);
}

// Print the tree
void RBTree::print(RBNode* node, size_t level)
{
	if (node != nullptr)
	{
		print(node->right, level + 1);
		for (size_t i = 0; i < level; i++)
		{
			std::cout << "   ";
		}
		std::cout << node->key << '\n';
		print(node->left, level + 1);
	}
}

// Delete the tree
void RBTree::deleteTree(RBNode* node)
{
	if (node != nullptr)
	{
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}
}