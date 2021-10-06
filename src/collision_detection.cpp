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

void print_2d_vector(vector<vector<float>> vec){
	for(int i = 0; i < vec.size(); i++){
		for(int j = 0; j < vec[i].size(); j++){
			cout << vec[i][j] << " ";
		}
		cout << " " << endl;
	}
}

void convert_jsonString_to_vector(string buffer){
	cout << buffer << endl;
	int is_number_flag = 0;
	int is_negative_flag = 0;
	int is_vertex_info_flag = 0;
	int is_location_info_flag = 0;

	string start_of_array = "[[[";
	string end_of_array = "]]]";
	string start_of_sub_array = "[[";
	string end_of_sub_array = "]]";
	string vertex_info_part = "Vertex Info:";
	string location_info_part = "Location Info:";

	int str_length = buffer.length();
	string str;

	vector<vector<float>> vertex_info_cube;
	vector<vector<float>> vertex_info_suzanne;

	for(int i = 0; i < str_length; i++){

		is_vertex_info_flag = ((buffer.substr (i, i+12)).compare(vertex_info_part) == 0);
		is_location_info_flag = ((buffer.substr (i, i+14)).compare(location_info_part) == 0);

		//check if the part of the array is vertex or location info
		if(is_vertex_info_flag){

		}

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
	serv_addr.sin_port = htons(54020);

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


	return 0;
}
