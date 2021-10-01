/*
 * EBO.h
 *
 *  Created on: Oct 1, 2021
 *      Author: gandhi
 */

#ifndef INCLUDE_EBO_H_
#define INCLUDE_EBO_H_

#include <iostream>
#include <stdio.h>
#include "../lib/glad/glad.h"
#include <GLFW/glfw3.h>
using namespace std;

class EBO{
public:
	GLuint ID;

	EBO(GLuint* indices, GLsizeiptr size);
	void Bind();
	void UnBind();
	void Delete();

};

#endif /* INCLUDE_EBO_H_ */
