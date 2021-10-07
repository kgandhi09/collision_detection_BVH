//============================================================================
// Name        : collision_detection.cpp
// Author      : Kushal Gandhi
// Version     :
// Copyright   : Your copyright notice
// Description : Collision Detection in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

int obj_count;
vector<int> vertex_count;
int frames_count;
vector<vector<float>> vertices_info;
vector<vector<float>> location_info;

//individual vertices and location info for each object
vector<vector<float>> cube_vertices;
vector<vector<float>> suzanne_vertices;
vector<vector<float>> cube_locations;
vector<vector<float>> suzanne_locations;

void print_2d_vector(vector<vector<float>> vec){
	for(long unsigned int i = 0; i < vec.size(); i++){
		for(long unsigned int j = 0; j < vec[i].size(); j++){
			cout << vec[i][j] << " ";
		}
		cout << endl;
	}
}

vector<int> conv_string_list_vector_int(string val){
	vector<int> vec;

	long unsigned int i = 0;
	string temp_val;
	while(i<val.length()){

		if(val[i] == '['){
			i += 1;
			continue;
		}
		else if(val[i] == ',' || val[i] == ']'){
			vec.push_back(stoi(temp_val));
			temp_val = "";
		}
		else{
			temp_val += val[i];
		}
		i++;
	}

	return vec;
}

vector<float> conv_string_list_vector_float(string val){
	vector<float> vec;

	long unsigned int i = 0;
	string temp_val;
	while(i<val.length()){

		if(val[i] == '['){
			i += 1;
			continue;
		}
		else if(val[i] == ',' || val[i] == ']'){
			vec.push_back(stof(temp_val));
			temp_val = "";
		}
		else{
			temp_val += val[i];
		}
		i++;
	}

	return vec;
}

vector<vector<float>> conv_2d_list_vector(string val){
	vector<vector<float>> vec;
	long unsigned int i = 0;
	string temp_val;
	vector<float> temp_vec;

	while(i<val.length()){
		if(val[i] == '['){
			i+= 1;
			continue;
		}
		else if(val[i] == ']'){
			temp_val = '[' + temp_val + ']';
			temp_vec = conv_string_list_vector_float(temp_val);
			vec.push_back(temp_vec);
			temp_val = "";
			i += 2;
		}
		else{
			temp_val += val[i];
		}
		i++;
	}
	return vec;

}

void convert_jsonString_to_vector(string buffer){
	int buffer_length = buffer.length();
	vector<int> linebreak_idx;
	for(int i = 0; i < buffer_length; i++){
		if(buffer[i] == '\n'){linebreak_idx.push_back(i);}
	}
	obj_count = stoi(buffer.substr (0, linebreak_idx[0]));
	vertex_count = conv_string_list_vector_int(buffer.substr (linebreak_idx[0]+1, linebreak_idx[1]-(linebreak_idx[0]+1)));
	frames_count = stoi(buffer.substr (linebreak_idx[1]+1, linebreak_idx[2]-(linebreak_idx[1]+1)));
	vertices_info = conv_2d_list_vector(buffer.substr (linebreak_idx[2]+1, linebreak_idx[3]-(linebreak_idx[2]+1)));
	location_info = conv_2d_list_vector(buffer.substr (linebreak_idx[3]+1, (buffer_length-1)));

}

void split_vertices_per_obj(vector<vector<float>> verices_info, vector<int> vertices_count){
	int no_cube_vertices = vertices_count[0];
	int no_suzanne_vertices = vertices_count[1];

	for(int i = 0; i < no_cube_vertices; i++){
		cube_vertices.push_back(vertices_info[i]);
	}
	for(int i = no_cube_vertices; i < (no_cube_vertices + no_suzanne_vertices); i++){
		suzanne_vertices.push_back(vertices_info[i]);
	}
}

void split_locations_per_obj(vector<vector<float>> locations_info, int frames_count){
	for(int i = 0; i < frames_count; i++){
		cube_locations.push_back(location_info[i]);
	}
	for(int i = frames_count; i < (2*frames_count); i++){
		suzanne_locations.push_back(location_info[i]);
	}
}

int main() {

	char buffer[6144] = {0};

	//Create a socket
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(client_socket == -1){
		cerr << "Can't create the client socket! Quitting!" << endl;
		return -1;
	}

	//Bind the IP address and port to a socket
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(54007);

	//Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0){
		cerr << "Invalid Address!" << endl;
		return -1;
	}

	if(connect(client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		cerr << "Connection Refused!" << endl;
		return -1;
	}

	string buffer_val;
	while(true){
		int bytesReceived = recv(client_socket, buffer, 6144, 0);
		string last_buffer_val = string(buffer, 0, bytesReceived);
		buffer_val += last_buffer_val;

		if (bytesReceived == -1)
		{
			cerr << "Error in recv(). Quitting" << endl;
			break;
		}
        if (bytesReceived == 0)
        {
            cout << "Client disconnected " << endl;
            break;
        }

	}

	convert_jsonString_to_vector(buffer_val);

	//splitting the vertices and locations info per object
	split_vertices_per_obj(vertices_info, vertex_count);
	split_locations_per_obj(location_info, frames_count);



	return 0;
}
