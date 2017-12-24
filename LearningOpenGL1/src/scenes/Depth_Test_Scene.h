#pragma once

#include "../GScene.h"
#include "../Shader.h"
#include "../Texture.h"
#include "../Model.h"
#include "../Fuck.h"
#include "../Camera.h"
#include "../GLView.h"
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp> 

#include <string>

class DepthTestingScene : Scene
{
public:
	static Scene* CreateScene();

	void render();
	void clear();
	bool init();
	std::string name();


public:
	Shader programShader;
	Model nanoSuitModel;
	unsigned int cubeVAO, cubeVBO;
	unsigned int planeVAO, planeVBO;
	unsigned int cubeTexture;
	unsigned int floorTexture;

};

