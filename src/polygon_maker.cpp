/*
 * polygon_maker.cpp
 *
 *  Created on: Sep 30, 2021
 *      Author: gandhi
 */

#include "include/polygon_maker.h"

polygon_maker::polygon_maker(GLFWwindow* window, GLfloat* vertices, const char* vertexShaderSource, const char* fragmentShaderSource){
	polygon_maker::this_window = window;
	polygon_maker::polygon_vertices = vertices;
	polygon_maker::vertexShaderSource = vertexShaderSource;
	polygon_maker::fragmentShaderSource = fragmentShaderSource;
}

void polygon_maker::make_polygon(){
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	//sending from cpu to GPU, but in big batches called buffers (different from screen front and back buffers)
	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(polygon_vertices), polygon_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}
