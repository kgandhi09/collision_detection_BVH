/*
 * bounding_volume_hierarchy.cpp
 *
 *  Created on: Oct 7, 2021
 *      Author: gandhi
 */
//Creates a bounding volume hierarchy for each frame

#include "include/bounding_volume_hierarchy.h"

BVH::BVH(int obj_count, vector<int> vertex_count, vector<vector<float>> cube_vertices, vector<vector<float>> suzanne_vertices, vector<float> cube_location_info, vector<float> suzanne_location_info){
	BVH::obj_count = obj_count;
	BVH::vertex_count = vertex_count;
	BVH::cube_vertices = cube_vertices;
	BVH::suzanne_vertices = suzanne_vertices;
	BVH::cube_location_info = cube_location_info;
	BVH::suzanne_location_info = suzanne_location_info;
	BVH::tree = new AABB_tree();
}

void BVH::obj_world_vert(){
	//converting cube vertices from obj to world coords
	for(long unsigned int i = 0; i < cube_vertices.size(); i++){
		BVH::cube_vertices[i][0] += BVH::cube_location_info[0];
		BVH::cube_vertices[i][1] += BVH::cube_location_info[1];
		BVH::cube_vertices[i][2] += BVH::cube_location_info[2];
	}

	//converting suzanne vertices from obj to world coords
	for(long unsigned int i = 0; i < suzanne_vertices.size(); i++){
		BVH::suzanne_vertices[i][0] += BVH::suzanne_location_info[0];
		BVH::suzanne_vertices[i][1] += BVH::suzanne_location_info[1];
		BVH::suzanne_vertices[i][2] += BVH::suzanne_location_info[2];
	}
}







