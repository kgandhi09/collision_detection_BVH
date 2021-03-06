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
		vector<vector<float>> data; //include the information of minx, miny, minz, maxx, maxy, maxz
		octree_node* one;
		octree_node* two;
		octree_node* three;
		octree_node* four;
		octree_node* five;
		octree_node* six;
		octree_node* seven;
		octree_node* eight;
	};


	octree_node* root;

	AABB_tree();
	octree_node* createLeaf(vector<vector<float>> data);
	void addRoot(vector<vector<float>> data);
	void addChildren(octree_node* node,
			vector<vector<float>> data_child_1,
			vector<vector<float>> data_child_2,
			vector<vector<float>> data_child_3,
			vector<vector<float>> data_child_4,
			vector<vector<float>> data_child_5,
			vector<vector<float>> data_child_6,
			vector<vector<float>> data_child_7,
			vector<vector<float>> data_child_8);
};


#endif /* INCLUDE_AABB_TREE_H_ */
