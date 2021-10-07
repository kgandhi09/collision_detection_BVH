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

vector<float> BVH::calc_max_xyz(vector<vector<float>> vec){
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

vector<float> BVH::combine_min_max(vector<float> min, vector<float> max){
	vector<float> combined;
	for(long unsigned int i = 0; i < min.size(); i++){
		combined.push_back(min[i]);
	}
	for(long unsigned int i = 0; i < max.size(); i++){
		combined.push_back(max[i]);
	}
	return combined;
}

vector<vector<float>> BVH::get_AABB_vertices(vector<float> data){
	vector<vector<float>> AABB_vertices;
	float x2 = data[0];
	float y2 = data[1];
	float z2 = data[2];
	float x1 = data[3];
	float y1 = data[4];
	float z1 = data[5];

	vector<float> AABB_plane_1_top_left {x2, y2, z1};
	vector<float> AABB_plane_1_bottom_left {x2, y1, z2};
	vector<float> AABB_plane_1_top_right {x1, y2, z1};
	vector<float> AABB_plane_1_bottom_right {x1, y2, z2};

	vector<float> AABB_plane_2_top_left {x2, y1, z1};
	vector<float> AABB_plane_2_bottom_left {x2, y1, z2};
	vector<float> AABB_plane_2_top_right {x1, y1, z1};
	vector<float> AABB_plane_2_bottom_right {x1, y1, z2};

	AABB_vertices.push_back(AABB_plane_1_top_left);
	AABB_vertices.push_back(AABB_plane_1_bottom_left);
	AABB_vertices.push_back(AABB_plane_1_top_right);
	AABB_vertices.push_back(AABB_plane_1_bottom_right);

	AABB_vertices.push_back(AABB_plane_2_top_left);
	AABB_vertices.push_back(AABB_plane_2_bottom_left);
	AABB_vertices.push_back(AABB_plane_2_top_right);
	AABB_vertices.push_back(AABB_plane_2_bottom_right);

	return AABB_vertices;
}

void BVH::split_AABB(vector<vector<float>> data){
	float x2 = data[1][0];
	float y2 = data[1][1];
	float z2 = data[1][2];
	float x1 = data[6][0];
	float y1 = data[6][1];
	float z1 = data[6][2];

	//top_left AABB child for plane 1
	vector<float> sub_AABB_1_data {x2, y2, ((z2-z1)/2), ((x1-x2)/2), ((y1-y2)/2), z1};
	vector<vector<float>> sub_AABB_1_vertices = get_AABB_vertices(sub_AABB_1_data);

	//bottom_left AABB child for plane 1
	vector<float> sub_AABB_2_data {x2, y2, z2, ((x1-x2)/2), ((y1-y2)/2), ((z1-z2)/2)};
	vector<vector<float>> sub_AABB_2_vertices = get_AABB_vertices(sub_AABB_2_data);

	//top right AABB  child for plane 1
	vector<float> sub_AABB_3_data {((x1-x2)/2), y2, ((z1-z2)/2),  x1, ((y1-y2)/2), z1};
	vector<vector<float>> sub_AABB_3_vertices = get_AABB_vertices(sub_AABB_3_data);

	//bottom right AABB child for plane 1
	vector<float> sub_AABB_4_data {((x1-x2)/2), y2, z2, x1, ((y1-y2)/2), ((z1-z2)/2)};
	vector<vector<float>> sub_AABB_4_vertices = get_AABB_vertices(sub_AABB_4_data);

	//top left AABB child for plane 2
	vector<float> sub_AABB_5_data {x2, ((y1-y2)/2), ((z1-z2)/2), ((x1-x2)/2), y1, z1};
	vector<vector<float>> sub_AABB_5_vertices = get_AABB_vertices(sub_AABB_5_data);

	//bottom left AABB  child for plane 2
	vector<float> sub_AABB_6_data {x2, ((y1-y2)/2), z2, ((x1-x2)/2), y1, ((z1-z2)/2)};
	vector<vector<float>> sub_AABB_6_vertices = get_AABB_vertices(sub_AABB_6_data);

	//top right AABB child for plane 2
	vector<float> sub_AABB_7_data {((x1-x2)/2), ((y1-y2)/2), ((z1-z2)/2), x1, y1, z1};
	vector<vector<float>> sub_AABB_7_vertices = get_AABB_vertices(sub_AABB_7_data);

	//bottom right AABB child for plane 2
	vector<float> sub_AABB_8_data {((x1-x2)/2), ((y1-y2)/2), z2, x1, y1, ((z1-z2)/2)};
	vector<vector<float>> sub_AABB_8_vertices = get_AABB_vertices(sub_AABB_8_data);

}

void BVH::construct_BVH_root(){
	vector<vector<float>> root_data {{0, 0, 0, 0, 0, 0}};
	tree->addRoot(root_data);

	//calculating min vertex for cube -> Left child
	vector<float> left_min = calc_min_xyz(BVH::cube_vertices);
	vector<float> left_max = calc_max_xyz(BVH::cube_vertices);
	vector<float> left_combined = combine_min_max(left_min, left_max);
	vector<vector<float>> root_left_data = get_AABB_vertices(left_combined);

	//calculating min vertex for Suzanne -> Right child
	vector<float> right_min = calc_min_xyz(BVH::suzanne_vertices);
	vector<float> right_max = calc_max_xyz(BVH::suzanne_vertices);
	vector<float> right_combined = combine_min_max(right_min, right_max);
	vector<vector<float>> root_right_data = get_AABB_vertices(right_combined);

	tree->addChildrenRoot(tree->root, root_left_data, root_right_data);

}

void BVH::construct_BVH_octree(){
	int depth_limit = 5; //leaf condition


}




