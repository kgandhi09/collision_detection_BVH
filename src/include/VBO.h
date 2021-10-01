/*
 * VBO.h
 *
 *  Created on: Oct 1, 2021
 *      Author: gandhi
 */

#ifndef INCLUDE_VBO_H_
#define INCLUDE_VBO_H_

#include <iostream>
#include <stdio.h>
#include "../lib/glad/glad.h"
#include <GLFW/glfw3.h>
using namespace std;

class VBO{
public:
	GLuint ID;

	VBO(GLfloat* vertices, GLsizeiptr size);
	void Bind();
	void UnBind();
	void Delete();

};

#endif /* INCLUDE_VBO_H_ */
