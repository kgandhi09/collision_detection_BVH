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

using namespace std;

class BVH{
public:
	int obj_count;
	vector<int> vertex_count;
	int frames_count;
	vector<vector<float>> vertices_info;
	vector<float> frame_location_info;

	BVH(int obj_count, vector<int> vertex_count, int frames_count, vector<vector<float>> vertices_info, vector<float> frame_location_info);
};


#endif /* INCLUDE_BOUNDING_VOLUME_HIERARCHY_H_ */
