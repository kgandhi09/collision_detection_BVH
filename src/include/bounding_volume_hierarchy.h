/*
 * bounding_volume_hierarchy.h
 *
 *  Created on: Oct 7, 2021
 *      Author: gandhi
 */

#ifndef INCLUDE_BOUNDING_VOLUME_HIERARCHY_H_
#define INCLUDE_BOUNDING_VOLUME_HIERARCHY_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include "AABB_tree.h"
#include <limits>

using namespace std;

class BVH{
public:
	int obj_count;
	vector<int> vertex_count;
	vector<vector<float>> cube_vertices;
	vector<vector<float>> suzanne_vertices;
	vector<float> cube_location_info;
	vector<float> suzanne_location_info;
	vector<float> root_min_max_data;
	int collision_detected;
	int all_nodes_visited;
	AABB_tree* tree;

	BVH(int obj_count, vector<int> vertex_count, vector<vector<float>> cube_vertices, vector<vector<float>> suzanne_vertices, vector<float> cube_location_info, vector<float> suzanne_location_info);
	void obj_world_vert();
	vector<float> calc_min_xyz(vector<vector<float>> vec);
	vector<float> calc_max_xyz(vector<vector<float>> vec);
	vector<float> combine_min_max(vector<float> min, vector<float> max);
	vector<vector<float>> get_AABB_vertices(vector<float> min_max_data);
	void split_AABB(vector<vector<float>> data, AABB_tree::octree_node* node);
	void construct_BVH_root();
	int to_expand(vector<vector<float>> vertices);
	int collision_detection(vector<vector<float>> vertices);
	void split_all_nodes(AABB_tree::octree_node* node);
	void construct_BVH(AABB_tree::octree_node*);

};


#endif /* INCLUDE_BOUNDING_VOLUME_HIERARCHY_H_ */
