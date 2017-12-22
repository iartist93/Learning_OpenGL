#pragma once

#include<glad/glad.h>
#include<string>
#include<sstream>
#include<fstream>
#include<iostream>
#include <glm/glm/glm.hpp>

class Shader
{
public:
	Shader();
	Shader(const GLchar *vShaderPath, const GLchar *fShaderPath);
	
	//-------------------------------------------------------#
	// activiate the shader program
	void use();

	//---------- uniform utilities functions ---------------#

	void setBool(const char *uniformName, bool value) const;
	void setInt(const char *uniformName, int value) const;
	void setFloat1(const char *unifromName, float value) const;
	void setFloat4(const char *uniformName, float fv1, float fv2, float fv3, float fv4);
	void setMatrix4fv(const char *uniformName, const float *martix); 	// 4fv = vector/Array of 4 floats
	
	void setFloat3(const char *uniformName, float fv1, float fv2, float fv3);
	void setFloat3(const char *uniformName, glm::vec3 &value);


public:
	unsigned int ID;	// shader program id 
};
