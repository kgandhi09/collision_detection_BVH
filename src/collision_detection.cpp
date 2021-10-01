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
	GLfloat polygon_vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2/3, 0.0f
		-0.5f/2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.5f/2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f

	};

	GLuint indices[] = {
			0, 3, 5,
			3, 2, 4,
			5, 4, 1
	};

	//sending from cpu to GPU, but in big batches called buffers (different from screen front and back buffers)
	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(polygon_vertices), polygon_vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	while(!glfwWindowShouldClose(window)){
		glClearColor(0.27f, 0.05f, 0.34f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		//Take care of all GLFW events
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwDestroyWindow(window);

	//This function destroys all remaining windows and cursors, restores any modified gamma ramps and frees any other allocated resources
	glfwTerminate();
}
