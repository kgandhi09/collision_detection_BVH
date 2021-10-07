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
	struct octree_node{
		vector<float> data; //include the information of minx, miny, minz, maxx, maxy, maxz
		octree_node* one;
		octree_node* two;
		octree_node* three;
		octree_node* four;
		octree_node* five;
		octree_node* six;
		octree_node* seven;
		octree_node* eight;
	};
	struct node{
		vector<float> data; //include the information of minx, miny, minz, maxx, maxy, maxz
		octree_node* left;
		octree_node* right;
	};

	node* root;

	AABB_tree();
	node* createLeafRoot(vector<float> data);
	octree_node* createLeaf(vector<float> data);
	void addRoot(vector<float> data);
	void addChildrenRoot(node* node, vector<float> data_child_left, vector<float> data_child_right);
	void addChildren(octree_node* node,
					vector<float> data_child_1,
					vector<float> data_child_2,
					vector<float> data_child_3,
					vector<float> data_child_4,
					vector<float> data_child_5,
					vector<float> data_child_6,
					vector<float> data_child_7,
					vector<float> data_child_8);
	void delNode(node* node);
	void printNode(node* node);
	void printVector(vector<float> vec);

};


#endif /* INCLUDE_AABB_TREE_H_ */
