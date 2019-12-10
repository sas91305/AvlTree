/*
 * Experiment Main()
 *
 * Author: Seth Schaller
 */
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include "avl_tree.h"
using namespace std;

int main() {
	int treenum, keynum;
	double averageheight = 0, avgoptimal;
	cout << "Number of trees: ";
	cin >> treenum;
	cout << "Number of keys: ";
	cin >> keynum;

	cout << endl << "Building " << treenum << " random AVL trees with "
		<< keynum << " keys per tree..." << endl;

	//intializes array with n keys
	int* keys = new int[keynum];
	for (int j = 0; j < keynum; j++)
		keys[j] = j;

	//creates trees and computes average height
	for (int i = 0; i < treenum; i++) {
		AvlTree tree;
		random_shuffle(keys, keys + keynum);//shuffles array
		for (int g = 0; g < keynum; g++)
			tree.insert(keys[g]);
		averageheight += tree.height();
	}

	averageheight /= treenum;
	avgoptimal = averageheight / log2(keynum);
	cout << endl << "Average height: " << averageheight << endl;
	cout << endl << "average/optimal ration: " << avgoptimal << endl;

	char c;
	cin >> c;
	return 0;
}
