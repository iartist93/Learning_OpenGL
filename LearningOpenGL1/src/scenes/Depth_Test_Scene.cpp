#include "Depth_Test_Scene.h"

#include "../Objects.h"


bool DepthTestingScene::init()
{
	programShader = Shader("./shaders/vShaderDepthTesting.glsl", "./shaders/fShader_nano_suit_model.glsl");
	nanoSuitModel = Model("./models/nanosuit.obj");

	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	
	glBindVertexArray(0);


	// plane VAO
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	
	glBindVertexArray(0);

	// load textures
	// -------------
	cubeTexture = LoadTextureFromFile("marble.jpg", "resources");
	floorTexture = LoadTextureFromFile("metal.png", "resources");

	// shader configuration
	// --------------------
	programShader.use();
	programShader.setInt("texture1", 0);


	return true;
}

std::string DepthTestingScene::name()
{
	return std::string("Depth Test Scene");
}

void DepthTestingScene::render()
{
	auto director = Fuck::getInstance();
	auto camera = director->getMainCamera();
	auto glView = director->getGLView();

	programShader.use();

	glm::mat4 model;
	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(camera->fov), (float)glView->width / (float)glView->height, 0.1f, 100.0f);
	
	programShader.setMatrix4fv("view", glm::value_ptr(view));
	programShader.setMatrix4fv("projection", glm::value_ptr(projection));
	
	
	// cubes
	glBindVertexArray(cubeVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cubeTexture);
	
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
	programShader.setMatrix4fv("model", glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	programShader.setMatrix4fv("model", glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	
	// floor
	glBindVertexArray(planeVAO);
	glBindTexture(GL_TEXTURE_2D, floorTexture);
	programShader.setMatrix4fv("model", glm::value_ptr(glm::mat4()));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}


void DepthTestingScene::clear()
{
	glClearColor(139.0f/255.0f, 155.0f / 255.0f, 0.0f, 168.0f / 255.0f);	// state-set function
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// state-using function
}

Scene* DepthTestingScene::CreateScene()
{
	auto scene = new DepthTestingScene();
	return scene;
}