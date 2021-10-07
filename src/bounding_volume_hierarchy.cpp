/*
 * bounding_volume_hierarchy.cpp
 *
 *  Created on: Oct 7, 2021
 *      Author: gandhi
 */


#include "include/bounding_volume_hierarchy.h"

BVH::BVH(int obj_count, vector<int> vertex_count, int frames_count, vector<vector<float>> vertices_info, vector<float> frame_location_info){
	BVH::obj_count = obj_count;
	BVH::vertex_count = vertex_count;
	BVH::frames_count = frames_count;
	BVH::vertices_info = vertices_info;
	BVH::frame_location_info = frame_location_info;
	BVH::tree = new AABB_tree();
}





