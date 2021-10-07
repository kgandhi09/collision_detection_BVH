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

vector<float> BVH::calc_min_xyz(vector<vector<float>> vec){
	vector<float> min;
	int min_x = numeric_limits<int>::max();
	int min_y = numeric_limits<int>::max();
	int min_z = numeric_limits<int>::max();
	for(long unsigned int i = 0; i < vec.size(); i++){
		//calculating min x
		if(vec[i][0] < min_x){
			min_x = vec[i][0];
		}
		//calculating min y
		if(vec[i][1] < min_y){
			min_y = vec[i][1];
		}
		//calculating min z
		if(vec[i][2] < min_z){
			min_z = vec[i][2];
		}
	}
	min.push_back(min_x);
	min.push_back(min_y);
	min.push_back(min_z);

	return min;
}

vector<float> BVH::calc_max_xvyz(vector<vector<float>> vec){
	int max_x = numeric_limits<int>::min();
	int max_y = numeric_limits<int>::min();
	int max_z = numeric_limits<int>::min();
	vector<float> max;
	for(long unsigned int i = 0; i < vec.size(); i++){

		//calculating max x
		if(vec[i][0] > max_x){
			max_x = vec[i][0];
		}

		//calculating max y
		if(vec[i][1] > max_y){
			max_y = vec[i][1];
		}

		//calculating max z
		if(vec[i][2] > max_z){
			max_z = vec[i][2];
		}
	}
	max.push_back(max_x);
	max.push_back(max_y);
	max.push_back(max_z);

	return max;
}

void BVH::create_BVH(){

}





