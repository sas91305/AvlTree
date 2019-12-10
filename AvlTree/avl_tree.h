/*
 * Header file for AVL tree
 *
 * Author: Seth Schaller
 */

#ifndef AVL_TREE_H_INCLUDED
#define AVL_TREE_H_INCLUDED

struct Node {
	int key;
	int height;
	Node* parent;
	Node* left;
	Node* right;
};

class AvlTree {

public:
	AvlTree();
	~AvlTree();
	void inorder_print();
	int height();
	void insert(int key);

private:
	Node* root;
	void remove(Node* p);
	void inorder_print(Node* p);
	int height(Node* p);
	Node* insert(Node* p, int key);
	bool balanced(Node* p);
	Node* trinode_successor(Node* p, int key);
	Node* trinode_restructure(Node* x, Node* y, Node* z);
};
#endif
