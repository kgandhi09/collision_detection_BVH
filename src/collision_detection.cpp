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
#include "include/polygon_maker.h"
#include <math.h>
using namespace std;

const char* vertexShaderSource = "#version 330 core\n"
			"layout (location=0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"	gl_position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\n\0";

const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
			"}\n\0";

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
	GLfloat triangle_vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) *2, 0.0f

	};

	polygon_maker polygon_maker1(window, triangle_vertices, vertexShaderSource, fragmentShaderSource);
	polygon_maker1.make_polygon();

	while(!glfwWindowShouldClose(window)){
		//Take care of all GLFW events
		glfwPollEvents();
	}


	glfwDestroyWindow(window);

	//This function destroys all remaining windows and cursors, restores any modified gamma ramps and frees any other allocated resources
	glfwTerminate();
}
