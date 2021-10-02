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
#include "include/shaderClass.h"
#include "include/VBO.h"
#include "include/EBO.h"
#include "include/VAO.h"
using namespace std;

GLfloat polygon_vertices[] = {
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
	0.0f, 0.5f * float(sqrt(3)) * 2/3, 0.0f
//	-0.5f/2, 0.5f * float(sqrt(3)) / 6, 0.0f,
//	0.5f/2, 0.5f * float(sqrt(3)) / 6, 0.0f,
//	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f

};

GLuint indices[] = {
		0, 3, 5,
		3, 2, 4,
		5, 4, 1
};

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

	//sending from cpu to GPU, but in big batches called buffers (different from screen front and back buffers)
	Shader shaderProgram("/home/gandhi/Desktop/Eclipse Workspace/collision_detection_BVH/src/shaders/default_vert.txt", "/home/gandhi/Desktop/Eclipse Workspace/collision_detection_BVH/src/shaders/default_frag.txt");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(polygon_vertices, sizeof(polygon_vertices));
//	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkVBO(VBO1, 0);

	VAO1.UnBind();
	VBO1.UnBind();
//	EBO1.UnBind();

	while(!glfwWindowShouldClose(window)){
		glClearColor(0.27f, 0.05f, 0.34f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		VAO1.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		//Take care of all GLFW events
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
//	EBO1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);

	//This function destroys all remaining windows and cursors, restores any modified gamma ramps and frees any other allocated resources
	glfwTerminate();
}
