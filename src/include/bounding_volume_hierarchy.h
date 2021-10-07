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

using namespace std;

class BVH{
public:
	int obj_count;
	vector<int> vertex_count;
	vector<vector<float>> cube_vertices;
	vector<vector<float>> suzanne_vertices;
	vector<float> cube_location_info;
	vector<float> suzanne_location_info;
	AABB_tree* tree;

	BVH(int obj_count, vector<int> vertex_count, vector<vector<float>> cube_vertices, vector<vector<float>> suzanne_vertices, vector<float> cube_location_info, vector<float> suzanne_location_info);
	void obj_world_vert();

};


#endif /* INCLUDE_BOUNDING_VOLUME_HIERARCHY_H_ */
