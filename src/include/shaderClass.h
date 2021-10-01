/*
 * shaderClass.h
 *
 *  Created on: Oct 1, 2021
 *      Author: gandhi
 */

#ifndef INCLUDE_SHADERCLASS_H_
#define INCLUDE_SHADERCLASS_H_

#include <iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<cerrno>
#include <stdio.h>
#include "../lib/glad/glad.h"
#include <GLFW/glfw3.h>
using namespace std;

string get_file_contents(const char* filename);

class Shader{
public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();
};

#endif /* INCLUDE_SHADERCLASS_H_ */
