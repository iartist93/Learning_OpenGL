#ifndef __Shader__
#define	__Shader__

#include<glad\glad.h>
#include<string>
#include<sstream>
#include<fstream>
#include<iostream>

class Shader
{
public:
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


	//------------------------------------------------------#

public:
	unsigned int ID;	// shader program id 

};

Shader::Shader(const GLchar *vShaderPath, const GLchar *fShaderPath)
{
	// 1- retrieving the vertex and fragment shaders from external files
	std::string vShaderSource;
	std::string fShaderSource;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	try
	{
		vShaderFile.open(vShaderPath);
		fShaderFile.open(fShaderPath);

		std::stringstream vShaderStream, fShaderStream;

		// read from the files to the string stream
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// close the files
		vShaderFile.close();
		fShaderFile.close();

		// convert the string stream into strings
		vShaderSource = vShaderStream.str();			// read the stream buffer of this file
		fShaderSource = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULY_READ" << std::endl;
	}

	// convert the shaderstring to char*
	const char *vShaderCode = vShaderSource.c_str();
	const char *fShaderCode = fShaderSource.c_str();

	// 2- attack, compile, link and checking error
	int vShaderObject, fShaderObject;
	int success;
	char infoLog[512];

	vShaderObject = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShaderObject, 1, &vShaderCode, 0);
	glCompileShader(vShaderObject);
	glGetShaderiv(vShaderObject, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vShaderObject, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATON::FAILED " << infoLog << std::endl;
	}

	fShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShaderObject, 1, &fShaderCode, 0);
	glCompileShader(fShaderObject);
	glGetShaderiv(fShaderObject, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fShaderObject, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATON::FAILED " << infoLog << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vShaderObject);
	glAttachShader(ID, fShaderObject);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 255, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK::FALED " << infoLog << std::endl; 
	}

	glDeleteShader(vShaderObject);
	glDeleteShader(fShaderObject);

}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const char *uniformName, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, uniformName), (int) value);
}

void Shader::setInt(const char *uniformName, int value) const
{
	glUniform1i(glGetUniformLocation(ID, uniformName), value);
}

void Shader::setFloat1(const char *uniformName, float value) const
{
	glUniform1f(glGetUniformLocation(ID, uniformName), value);
}

void Shader::setFloat3(const char *uniformName, float fv1, float fv2, float fv3)
{
	glUniform3f(glGetUniformLocation(ID, uniformName), fv1, fv2, fv3);
}

void Shader::setFloat3(const char *uniformName, glm::vec3 &value)
{
	glUniform3fv(glGetUniformLocation(ID, uniformName), 1, &value[0]);
}

void Shader::setFloat4(const char *uniformName, float fv1, float fv2, float fv3, float fv4)
{
	glUniform4f(glGetUniformLocation(ID, uniformName), fv1, fv2, fv3, fv4);
}

void Shader::setMatrix4fv(const char *uniformName, const float *matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, uniformName), 1, GL_FALSE, matrix);
}


#endif // !Shader
