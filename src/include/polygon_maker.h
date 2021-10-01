/*
 * polygon_maker.h
 *
 *  Created on: Sep 30, 2021
 *      Author: gandhi
 */

#ifndef POLYGON_MAKER_H_
#define POLYGON_MAKER_H_

#include <iostream>
#include <stdio.h>
#include "../lib/glad/glad.h"
#include <GLFW/glfw3.h>
using namespace std;

class polygon_maker{
public:
	GLFWwindow* this_window;
	GLfloat* polygon_vertices;
	const char* vertexShaderSource;
	const char* fragmentShaderSource;

	polygon_maker(GLFWwindow* window, GLfloat vertices[], const char* vertexShaderSource, const char* fragmentShaderSource);
	void make_polygon();
};


#endif /* POLYGON_MAKER_H_ */
