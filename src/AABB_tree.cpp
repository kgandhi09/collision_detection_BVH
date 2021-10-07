/*
 * AABB_tree.cpp
 *
 *  Created on: Oct 7, 2021
 *      Author: gandhi
 */

#include "include/AABB_tree.h"

AABB_tree::AABB_tree(){
	root = NULL;
}


AABB_tree::octree_node* AABB_tree::createLeaf(vector<vector<float>> data){
	octree_node* currRoot = new octree_node;
	currRoot->data = data;
	currRoot->one = NULL;
	currRoot->two = NULL;
	currRoot->three = NULL;
	currRoot->four  = NULL;
	currRoot->five = NULL;
	currRoot->six = NULL;
	currRoot->seven = NULL;
	currRoot->eight = NULL;

	return currRoot;
}

void AABB_tree::addRoot(vector<vector<float>> data_root){
	root = createLeaf(data_root);
}


void AABB_tree::addChildren(octree_node* node,
		vector<vector<float>> data_child_1,
		vector<vector<float>> data_child_2,
		vector<vector<float>> data_child_3,
		vector<vector<float>> data_child_4,
		vector<vector<float>> data_child_5,
		vector<vector<float>> data_child_6,
		vector<vector<float>> data_child_7,
		vector<vector<float>> data_child_8)
{
	node->one = createLeaf(data_child_1);
	node->two = createLeaf(data_child_2);
	node->three = createLeaf(data_child_3);
	node->four = createLeaf(data_child_4);
	node->five = createLeaf(data_child_5);
	node->six = createLeaf(data_child_6);
	node->seven = createLeaf(data_child_7);
	node->eight = createLeaf(data_child_8);
}

