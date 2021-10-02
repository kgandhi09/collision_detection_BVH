/*
 * shaderClass.cpp
 *
 *  Created on: Oct 1, 2021
 *      Author: gandhi
 */

#include "include/shaderClass.h"

string get_file_contents(const char* path){

	ifstream input_file(path);
	if(!input_file.is_open()){
		cout << "Could not open the file" << endl;
		exit(EXIT_FAILURE);
	}
    return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());

}

Shader::Shader(const char* vertexFile, const char* fragmentFile){
	string vertexCode = get_file_contents(vertexFile);
	string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	ID = glCreateProgram();

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate(){
	glUseProgram(ID);
}

void Shader::Delete(){
	glDeleteProgram(ID);
}

