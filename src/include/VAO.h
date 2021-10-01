/*
 * VAO.h
 *
 *  Created on: Oct 1, 2021
 *      Author: gandhi
 */

#ifndef INCLUDE_VAO_H_
#define INCLUDE_VAO_H_

#include <iostream>
#include <stdio.h>
#include "../lib/glad/glad.h"
#include "VBO.h"
#include <GLFW/glfw3.h>
using namespace std;

class VAO{
public:
	GLuint ID;

	VAO();
	void LinkVBO(VBO VBO, GLuint layout);
	void Bind();
	void UnBind();
	void Delete();

};



#endif /* INCLUDE_VAO_H_ */
