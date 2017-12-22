#pragma once

#include "GScene.h"

#include "shader.h"
#include "ModelLoading/model.h"

#include "Fuck.h"
#include "camera.h"
#include "GLView.h"

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

