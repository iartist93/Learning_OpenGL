#pragma once

#include "../GScene.h"

#include "../Shader.h"
#include "../Model.h"

#include "../Fuck.h"
#include "../Camera.h"
#include "../GLView.h"

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp> 

#include <string>


class DepthTestScene : Scene 
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
};

