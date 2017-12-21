#include <glad/glad.h>			// include glad before glfw as it contain the opengl headers 
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>				// convert the vector/martix classes to array pointer representation to use and pass them to opengl
#include "camera.h"
#include "objects.h"
#include "shader.h"
#include "input.h"
#include "window.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "ModelLoading/model.h"
#include <fstream>


//----------------------------------------//
//GLobal

float deltaTime = 0.0f;
float lastFrame = 0.0f;
glm::vec3 lampPosition;
void Update();

//----------------------------------------//

int main()
{
	Window::MainWindow()->glfwWindow;

	Shader programShader = Shader("./ModelLoading/vShader_nano_suit_model.glsl", "./ModelLoading/fShader_nano_suit_model.glsl");
	Model nanoSuitModel = Model("./ModelLoading/Models/nanosuit.obj");

	programShader.use();

	while (!glfwWindowShouldClose(Window::MainWindow()->glfwWindow))
	{
		deltaTime = glfwGetTime() - lastFrame;
		lastFrame = glfwGetTime();

		Input::ProcessKeyboard(Window::MainWindow()->glfwWindow, deltaTime);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// state-set function
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// state-using function

		//--------------------- Drawing --------------------//
		// Model matrix (from local to wolrd space
		glm::mat4 model;
		model = glm::rotate(model, glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, -1.7f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down

		// View matrix (from world to camera space)
		glm::mat4 view;
		view = Camera::Main()->GetViewMatrix();
		
		// Projection matrix (from camera to NDC)ss
		glm::mat4 projection;	// transform to the NDC using prespective projection
		projection = glm::perspective(glm::radians(Camera::Main()->fov), (float)Window::MainWindow()->width / (float)Window::MainWindow()->height, 0.1f, 100.0f);

		programShader.setMatrix4fv("model", glm::value_ptr(model));
		programShader.setMatrix4fv("view", glm::value_ptr(view));
		programShader.setMatrix4fv("projection", glm::value_ptr(projection));

		nanoSuitModel.Draw(programShader);
		
		//--------------------------------------------------//

		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cerr << "OpenGL error: " << err << std::endl;
		}

		glfwSwapBuffers(Window::MainWindow()->glfwWindow);
		glfwPollEvents();
	}

	glfwTerminate();		// deallocate the resources
	return 0;
}
