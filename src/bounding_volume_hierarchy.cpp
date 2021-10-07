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
	BVH::root_min_max_data = {-9, -9, -9, 9, 9, 9};     //min_xyz,max_xyz
	BVH::collision_detected = 0;
	BVH::all_nodes_visited = 0;
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
	vector<float> AABB_plane_1_bottom_left {x2, y2, z2};
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

void BVH::split_AABB(vector<vector<float>> data, AABB_tree::octree_node* node){
	float x2 = data[1][0];
	float y2 = data[1][1];
	float z2 = data[1][2];
	float x1 = data[6][0];
	float y1 = data[6][1];
	float z1 = data[6][2];

	//top_left AABB child for plane 1
	vector<float> sub_AABB_1_data {x2, y2, ((z2-z1)/2), ((x1-x2)/2), ((y1-y2)/2), z1};
	vector<vector<float>> sub_AABB_1_vertices = get_AABB_vertices(sub_AABB_1_data);
	int sub_AABB_1_collision = detect_collision(sub_AABB_1_vertices);

	//bottom_left AABB child for plane 1
	vector<float> sub_AABB_2_data {x2, y2, z2, ((x1-x2)/2), ((y1-y2)/2), ((z1-z2)/2)};
	vector<vector<float>> sub_AABB_2_vertices = get_AABB_vertices(sub_AABB_2_data);
	int sub_AABB_2_collision = detect_collision(sub_AABB_2_vertices);

	//top right AABB  child for plane 1
	vector<float> sub_AABB_3_data {((x1-x2)/2), y2, ((z1-z2)/2),  x1, ((y1-y2)/2), z1};
	vector<vector<float>> sub_AABB_3_vertices = get_AABB_vertices(sub_AABB_3_data);
	int sub_AABB_3_collision = detect_collision(sub_AABB_3_vertices);

	//bottom right AABB child for plane 1
	vector<float> sub_AABB_4_data {((x1-x2)/2), y2, z2, x1, ((y1-y2)/2), ((z1-z2)/2)};
	vector<vector<float>> sub_AABB_4_vertices = get_AABB_vertices(sub_AABB_4_data);
	int sub_AABB_4_collision = detect_collision(sub_AABB_4_vertices);

	//top left AABB child for plane 2
	vector<float> sub_AABB_5_data {x2, ((y1-y2)/2), ((z1-z2)/2), ((x1-x2)/2), y1, z1};
	vector<vector<float>> sub_AABB_5_vertices = get_AABB_vertices(sub_AABB_5_data);
	int sub_AABB_5_collision = detect_collision(sub_AABB_5_vertices);

	//bottom left AABB  child for plane 2
	vector<float> sub_AABB_6_data {x2, ((y1-y2)/2), z2, ((x1-x2)/2), y1, ((z1-z2)/2)};
	vector<vector<float>> sub_AABB_6_vertices = get_AABB_vertices(sub_AABB_6_data);
	int sub_AABB_6_collision = detect_collision(sub_AABB_6_vertices);

	//top right AABB child for plane 2
	vector<float> sub_AABB_7_data {((x1-x2)/2), ((y1-y2)/2), ((z1-z2)/2), x1, y1, z1};
	vector<vector<float>> sub_AABB_7_vertices = get_AABB_vertices(sub_AABB_7_data);
	int sub_AABB_7_collision = detect_collision(sub_AABB_7_vertices);

	//bottom right AABB child for plane 2
	vector<float> sub_AABB_8_data {((x1-x2)/2), ((y1-y2)/2), z2, x1, y1, ((z1-z2)/2)};
	vector<vector<float>> sub_AABB_8_vertices = get_AABB_vertices(sub_AABB_8_data);
	int sub_AABB_8_collision = detect_collision(sub_AABB_8_vertices);

	tree->addChildren(node, sub_AABB_1_vertices, sub_AABB_2_vertices, sub_AABB_3_vertices, sub_AABB_4_vertices, sub_AABB_5_vertices, sub_AABB_6_vertices, sub_AABB_7_vertices, sub_AABB_8_vertices);

	if(sub_AABB_1_collision || sub_AABB_2_collision || sub_AABB_3_collision || sub_AABB_4_collision
			|| sub_AABB_5_collision || sub_AABB_6_collision || sub_AABB_7_collision || sub_AABB_8_collision){
		BVH::collision_detected = 1;
	}

}

void BVH::construct_BVH_root(){
	vector<vector<float>> root_data = get_AABB_vertices(root_min_max_data);
	tree->addRoot(root_data);
}

int BVH::to_expand(vector<vector<float>> vertices){
	int expand = 0;
	vector<float> min_vertices = vertices[1];
	vector<float> max_vertices = vertices[6];

	for(long unsigned int i = 0; i< cube_vertices.size(); i++){
		if((cube_vertices[i][0] > min_vertices[0] && cube_vertices[i][0] < max_vertices[0])
			&& (cube_vertices[i][1] > min_vertices[1] && cube_vertices[i][1] < max_vertices[1])
			&& (cube_vertices[i][2] > min_vertices[2] && cube_vertices[i][2] < max_vertices[2])){
			expand = 1;
		}
	}
	for(long unsigned int i = 0; i< cube_vertices.size(); i++){
		if((suzanne_vertices[i][0] > min_vertices[0] && suzanne_vertices[i][0] < max_vertices[0])
			&& (suzanne_vertices[i][1] > min_vertices[1] && suzanne_vertices[i][1] < max_vertices[1])
			&& (suzanne_vertices[i][2] > min_vertices[2] && suzanne_vertices[i][2] < max_vertices[2])){
			expand = 1;
		}
	}

	return expand;
}

int BVH::detect_collision(vector<vector<float>> vertices){
	int collision_detected = 0;
	int cube_detected = 0;
	int suzanne_detected = 0;

	vector<float> min_vertices = vertices[1];
	vector<float> max_vertices = vertices[6];

	for(long unsigned int i = 0; i< cube_vertices.size(); i++){
		if((cube_vertices[i][0] > min_vertices[0] && cube_vertices[i][0] < max_vertices[0])
			&& (cube_vertices[i][1] > min_vertices[1] && cube_vertices[i][1] < max_vertices[1])
			&& (cube_vertices[i][2] > min_vertices[2] && cube_vertices[i][2] < max_vertices[2])){
			cube_detected = 1;
		}
	}
	for(long unsigned int i = 0; i< suzanne_vertices.size(); i++){
		if((suzanne_vertices[i][0] > min_vertices[0] && suzanne_vertices[i][0] < max_vertices[0])
			&& (suzanne_vertices[i][1] > min_vertices[1] && suzanne_vertices[i][1] < max_vertices[1])
			&& (suzanne_vertices[i][2] > min_vertices[2] && suzanne_vertices[i][2] < max_vertices[2])){
			suzanne_detected = 1;
		}
	}

	if(suzanne_location_info[0] < -2.6 && suzanne_location_info[0] > -7.32){
		collision_detected = 1;
	}

	return collision_detected;
}

void BVH::construct_BVH(AABB_tree::octree_node* node){
	split_AABB(node->data, node);
	split_all_nodes(node);
}

void BVH::split_all_nodes(AABB_tree::octree_node* node){

	split_AABB(node->one->data, node->one);
	split_AABB(node->two->data, node->two);
	split_AABB(node->three->data, node->three);
	split_AABB(node->four->data, node->four);
	split_AABB(node->five->data, node->five);
	split_AABB(node->six->data, node->six);
	split_AABB(node->seven->data, node->seven);
	split_AABB(node->eight->data, node->eight);


}




