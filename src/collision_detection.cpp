//============================================================================
// Name        : collision_detection.cpp
// Author      : Kushal Gandhi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "../src/lib/glad/glad.h"
#include <GLFW/glfw3.h>
using namespace std;

int main() {

	//initialize the glfw3 library
	glfwInit();

	//creates a window object
	//glfwCreateWindow(int width, int height, char* title, GLFWmonitor* monitor, GLFWwindow* share)
	GLFWwindow* window = glfwCreateWindow(800,800, "Collision Detection Simulator", NULL, NULL);

	//makes the OpenGL context of specified window current on the calling thread
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();

	//Specify the ViewPort of OpenGL in the window
	glViewport(0,0,800,800);

	//Specify the color of the window background
	glClearColor(0.27f, 0.05f, 0.34f, 1.0f);
	//Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	//Swap the back buffer with the front buffer
	glfwSwapBuffers(window);

	while(!glfwWindowShouldClose(window)){
		//Take care of all GLFW events
		glfwPollEvents();
	}


	glfwDestroyWindow(window);

	//This function destroys all remaining windows and cursors, restores any modified gamma ramps and frees any other allocated resources
	glfwTerminate();
}