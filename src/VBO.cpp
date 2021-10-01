/*
 * VBO.cpp
 *
 *  Created on: Oct 1, 2021
 *      Author: gandhi
 */

#include "include/VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size){
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void VBO::Bind(){
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::UnBind(){
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete(){
	glDeleteBuffers(1, &ID);
}
