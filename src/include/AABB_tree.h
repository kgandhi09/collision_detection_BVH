/*
 * AABB_tree.h
 *
 *  Created on: Oct 7, 2021
 *      Author: gandhi
 */

#ifndef INCLUDE_AABB_TREE_H_
#define INCLUDE_AABB_TREE_H_

#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class AABB_tree{
public:
	struct node{
		vector<float> data; //include the information of minx, miny, minz, maxx, maxy, maxz
		node* left;
		node* right;
	};
	node* root;

	AABB_tree();
	node* createLeaf(vector<float> data);
	void addRoot(vector<float> data);
	void addChildren(node* node, vector<float> data_child_left, vector<float> data_child_right);
	void delNode(node* node);
	void printNode(node* node);
	void printVector(vector<float> vec);

};


#endif /* INCLUDE_AABB_TREE_H_ */
