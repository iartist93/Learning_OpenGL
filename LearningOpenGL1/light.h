#pragma once

#include <glm\glm\glm.hpp>

enum LightType
{
	POINT_LIGHT,
	DIRECTIONAL_LIGHT,
	FLASH_LIGHT
};

class Light
{
public:
	Light();

	int Init(LightType type, glm::vec3 lightColor, float amibent, float diffuse, float specular,
		glm::vec3 lightDirection, glm::vec3 lightPosition);


	void Activiate();
	void Deactivate();

public:
	LightType type;
	float ambient;
	float diffuse;
	float specular;
	glm::vec3 color;
	glm::vec3 position; 
	glm::vec3 direction;
	
private:
	// each light in the scene will have a unique id for easy debugging and setting/gettting from the scene
	static int ID = 0;				// <<--- static class variables

};

Light::Light()
{

}

int Light::Init(LightType type, glm::vec3 lightColor,  float amibent, float diffuse, float specular, 
	glm::vec3 lightDirection = glm::vec3(0.0, 0.0, -1.0f), 
	glm::vec3 lightPosition = glm::vec3(0.0f)) 
{
	this->type = type;
	this->color = color;
	this->position = position;
	this->direction = direction;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	
	return ID++;
}



// TODO::

	// create a new variable in each light struct to [ active ] to check while calcuation to see
	// if we will consider it in this frame calculations or not

	// add GUI for 1- chaning the light parameters (pos, dir, color, ambient, diffuse, specular)
	// add GUI for enable/disable the rendering of light objects in the scene
	
	





