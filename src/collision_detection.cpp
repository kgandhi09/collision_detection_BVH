//============================================================================
// Name        : collision_detection.cpp
// Author      : Kushal Gandhi
// Version     :
// Copyright   : Your copyright notice
// Description : Collision Detection in C++, Ansi-style
//============================================================================

#include <iostream>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

int main() {


	char buffer[4096] = {0};
	char *echo = "Message Received";

	//Create a socket
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(client_socket == -1){
		cerr << "Can't create the client socket! Quitting!" << endl;
		return -1;
	}

	//Bind the IP address and port to a socket
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(54003);

	//Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0){
		cerr << "Invalid Address!" << endl;
		return -1;
	}

	if(connect(client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		cerr << "Connection Refused!" << endl;
		return -1;
	}


	while(true){
		int bytesReceived = recv(client_socket, buffer, 4096, 0);
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

        cout << string(buffer, 0, bytesReceived) << endl;
	}
	return 0;
}
