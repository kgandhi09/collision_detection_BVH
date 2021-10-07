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

AABB_tree::node* AABB_tree::createLeafRoot(vector<float> data){
	node* currRoot = new node;
	currRoot->data = data;
	currRoot->left = NULL;
	currRoot->right = NULL;

	return currRoot;
}

AABB_tree::octree_node* AABB_tree::createLeaf(vector<float> data){
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

void AABB_tree::addRoot(vector<float> data_root){
	root = createLeafRoot(data_root);
}

void AABB_tree::addChildrenRoot(node* node, vector<float> data_child_left, vector<float> data_child_right){
	if(node != NULL){
		node->left = createLeaf(data_child_left);
		node->right = createLeaf(data_child_right);
	}
}

void AABB_tree::addChildren(octree_node* node,
							vector<float> data_child_1,
							vector<float> data_child_2,
							vector<float> data_child_3,
							vector<float> data_child_4,
							vector<float> data_child_5,
							vector<float> data_child_6,
							vector<float> data_child_7,
							vector<float> data_child_8)
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

void AABB_tree::delNode(node* node){
	node->left = NULL;
	node->right = NULL;
	delete node;
}

void AABB_tree::printNode(node* node){
	if(node != NULL){
		cout << "Parent: ";
		AABB_tree::printVector(node->data);
		if(node->left != NULL){
			cout << "Left Child: ";
			AABB_tree::printVector(node->left->data);
		}
		if(node->right != NULL){
			cout << "Right Child: ";
			AABB_tree::printVector(node->right->data);
		}
	}
}

void AABB_tree::printVector(vector<float >vec){
	for(long unsigned int i = 0; i < vec.size(); i++){
		cout << vec[i] << " ";
	}
	cout << endl;
}
