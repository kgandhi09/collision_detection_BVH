/*
 * VAO.cpp
 *
 *  Created on: Oct 1, 2021
 *      Author: gandhi
 */

#include "include/VAO.h"

VAO::VAO(){
	glGenVertexArrays(1, &ID);
}

void VAO::LinkVBO(VBO VBO, GLuint Layout){
	VBO.Bind();
	glVertexAttribPointer(Layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(Layout);
	VBO.UnBind();
}

void VAO::Bind(){
	glBindVertexArray(ID);
}

void VAO::UnBind(){
	glBindVertexArray(0);
}

void VAO::Delete(){
	glDeleteVertexArrays(1, &ID);
}
