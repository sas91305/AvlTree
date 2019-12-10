/*
 * Implementation file for avl_tree.h
 *
 * Author: Seth Schaller
 */

#include <iostream>
#include <algorithm>
#include "avl_tree.h"
using namespace std;

//Helper functions
int max(int a, int b) {
	return a > b ? a : b;
}

Node* newNode(int key) {
	Node* node = new Node();
	node->key = key;
	node->height = 0;
	node->left = nullptr;
	node->right = nullptr;
	return node;
}

//Constructs empty tree
//if no nodes then height should be -1, if node exists but no childered height is 0
AvlTree::AvlTree() { root = nullptr; }

//Destructor; calls private remove with root as perameter
AvlTree::~AvlTree() { remove(root); }

//Public inorder_print; calls private inorder_print with root as perameter
void AvlTree::inorder_print() { inorder_print(root); }

//Public height; calls private height with root as the peramter
int AvlTree::height() { return height(root); }

//Public insert; calls private insert with root and key as perameters
void AvlTree::insert(int key) { root = insert(root, key); }

//Private remove; recursivly deletes subtrees of p, then deletes itself
void AvlTree::remove(Node* p) {
	if (p == nullptr)
		return;
	remove(p->left);
	remove(p->right);
	delete p;
	p = nullptr;
}

//Private inorder_print; in_order print of tree rooted at p
void AvlTree::inorder_print(Node* p) {
	if (p == nullptr)
		return;
	inorder_print(p->left);
	cout << p->key << "-" << p->height << " ";
	inorder_print(p->right);
}

//Private height; returns height of p
int AvlTree::height(Node* p) {
	if (p == nullptr)
		return -1;
	else
		return p->height;
}

//Private insert; inserts key into tree rooted at p
Node* AvlTree::insert(Node* p, int key) {
	if (p == nullptr) {
		p = newNode(key);
		return p;
	}

	//Recursive binary search
	if (key <= p->key) //if key wanting to be inserted is less than peramter node->key
		p->left = insert(p->left, key);//Recursive call with left child
	else //is key wanting to be inserted is greater than perameter node->key
		p->right = insert(p->right, key); //Recursive call with right child

	//Updating height
	p->height = max(height(p->left), height(p->right)) + 1;

	if (!balanced(p)) {
		Node* child = trinode_successor(p, key);
		Node* grandchild = trinode_successor(child, key);
		return trinode_restructure(p, child, grandchild);
	}
	return p;
}

//Private balanced; returns true if p is null or its children differ by at most 1
bool AvlTree::balanced(Node* p) {
	if (p == nullptr)
		return true;
	else {
		int left_height = height(p->left);
		int right_height = height(p->right);
		int heightdiff = (left_height - right_height);
		if (heightdiff < -1 || heightdiff > 1)
			return false;
	}
	return true;
}

Node* AvlTree::trinode_successor(Node* p, int key) {
	//returns left child if left height is greater
	if (height(p->left) > height(p->right))
		return p->left;
	//returns right child if right height is greater
	else if (height(p->right) > height(p->left))
		return p->right;
	//uses key to determine node to return
	else
		return (key <= p->key) ? p->left : p->right;
}

/*
 * Called by insert method. Rearranges related nodes and their subtrees.
 *
 *     x              y
 *     |             / \
 *     y     =>     x   z
 *     |
 *     z
 *
 * Returns root of the entire tree after restructuring.
 */
Node* AvlTree::trinode_restructure(Node* x, Node* y, Node* z) {
	int heightdiff = height(x->left) - height(x->right);
	Node* temp;

	if (heightdiff > 1) {
		//LL case
		if (height(y->left) > height(y->right)) {
			//right rotate
			temp = y->right; //save y right child
			y->right = x; //set y right child to x
			x->left = temp; //set y original right child to x left child
			x->height = 1+ max(height(x->left), height(x->right));
			y->height = 1+ max(height(y->left), height(y->right));
			return y;
		}
		//LR case
		else {
			//set left rotate with y,z to y
			temp = z->left; //save z left child
			z->left = y; //set z left to y
			y->right = temp; //set z original left to y right child
			y->height = 1 + max(height(y->left), height(y->right));
			z->height = 1 + max(height(z->left), height(z->right));
			y = z; //set y node to z node
			//return right rotate with current x,y
			temp = y->right; //save y right child
			y->right = x; //set y right child to x
			x->left = temp; //set y original right child to x left child
			x->height = 1 + max(height(x->left), height(x->right));
			y->height = 1 + max(height(y->left), height(y->right));
			return y;
		}
	}
	else {
		//RR case
		if (height(y->right) > height(y->left)) {
			temp = y->left; //save y left child
			y->left = x; //set y left to x
			x->right = temp; //set y original left to x right child
			x->height = 1 + max(height(x->left), height(x->right));
			y->height = 1 + max(height(y->left), height(y->right));
			return y;
		}
		//RL case
		else {
			//set y to right rotate with y,z
			temp = z->right; //save z right child
			z->right = y; //set z right child to y
			y->left = temp; //set z original right child to y left child
			y->height = 1 + max(height(y->left), height(y->right));
			z->height = 1 + max(height(z->left), height(z->right));
			y = z;
			//return left rotate of x,y
			temp = y->left; //save y left child
			y->left = x; //set y left to x
			x->right = temp; //set y original left to x right child
			x->height = 1 + max(height(x->left), height(x->right));
			y->height = 1 + max(height(y->left), height(y->right));
			return y;
		}
	}
}