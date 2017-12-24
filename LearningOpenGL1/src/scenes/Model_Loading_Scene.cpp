#include "Model_Loading_Scene.h"

bool ModelLoadingScene::init()
{
	programShader = Shader("./shaders/vShader_nano_suit_model.glsl", "./shaders/fShader_nano_suit_model.glsl");
	nanoSuitModel = Model("./models/nanosuit.obj");
	
	return true;
}

std::string ModelLoadingScene::name()
{
	return std::string("Model Loading Scene");
}

void ModelLoadingScene::render()
{	
	programShader.use();

	auto director = Fuck::getInstance();
	auto glView = director->getGLView();
	auto mainCamera = director->getMainCamera();
	
	// Model matrix (from local to wolrd space)
	glm::mat4 model;
	model = glm::rotate(model, glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, -1.7f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down

	// View matrix (from world to camera space)
	glm::mat4 view;
	view = mainCamera->GetViewMatrix();

	// Projection matrix (from camera to NDC)
	glm::mat4 projection;	// transform to the NDC using prespective projection
	projection = glm::perspective(glm::radians(mainCamera->fov), (float)glView->width / (float)glView->height, 0.1f, 100.0f);

	programShader.setMatrix4fv("model", glm::value_ptr(model));
	programShader.setMatrix4fv("view", glm::value_ptr(view));
	programShader.setMatrix4fv("projection", glm::value_ptr(projection));

	nanoSuitModel.Draw(programShader);	
}


void ModelLoadingScene::clear()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);	// state-set function
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// state-using function
}

Scene* ModelLoadingScene::CreateScene()
{
	auto scene = new ModelLoadingScene();
	return scene;
}