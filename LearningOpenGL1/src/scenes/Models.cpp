//#include <glad/glad.h>			// include glad before glfw as it contain the opengl headers 
//#include <GLFW/glfw3.h>
//#include <iostream>
//
//#include <glm/glm/glm.hpp>
//#include <glm/glm/gtc/matrix_transform.hpp>
//#include <glm/glm/gtc/type_ptr.hpp>				// convert the vector/martix classes to array pointer representation to use and pass them to opengl
//
//#include "../camera.h"
//#include "../objects.h"
//#include "../shader.h"
//
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//
//#include "model.h"
//#include <fstream>
//
//struct
//{
//	int width = 800;
//	int height = 600;
//} viewPort;
//
//
/////GLobal Variables
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//float lastMousePosX = viewPort.width / 2.0f;
//float lastMousePosY = viewPort.height / 2.0f;
//bool firstMouse = true;
//
//Camera camera;
//glm::vec3 lampPosition;
////GLFWwindow *window;
//
//
//void Update();
//GLFWwindow* CreateGLFWWindow(int width, int height);
//
////-----------------------------------------------------------------//
//// Callbacks
////------------------------------------------------------------------//
//void mouse_callback(GLFWwindow *window, double xPos, double yPos)
//{
//	if (firstMouse)
//	{
//		lastMousePosX = xPos;
//		lastMousePosY = yPos;
//		firstMouse = false;
//	}
//
//	float xOffset = xPos - lastMousePosX;	// increase right
//	float yOffset = lastMousePosY - yPos;	// increase downwards
//
//	std::cout << xOffset << " " << yOffset << " " << lastMousePosX << " " << lastMousePosY << std::endl;
//
//	lastMousePosX = xPos;
//	lastMousePosY = yPos;
//
//	// objective :: update the forward vector
//	camera.ProcessMouseMovement(xOffset, yOffset);
//}
//
//void mouse_scroll(GLFWwindow *window, double xOffset, double yOffset)
//{
//	// objective::update the FOV value
//	camera.ProcessMouseScroll(xOffset, yOffset);
//}
//
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}
//
//void processInput(GLFWwindow *window)
//{
//	// Moving the camera
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)	// Forward
//		camera.ProcessKeyboardInput(FORWARD, deltaTime);
//
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)	// BackWord
//		camera.ProcessKeyboardInput(BACKWARD, deltaTime);
//
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)	// Right
//		camera.ProcessKeyboardInput(RIGHT, deltaTime);
//
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)	// Left
//		camera.ProcessKeyboardInput(LEFT, deltaTime);
//
//	// Exit the games
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
//	{
//		glfwSetWindowShouldClose(window, true);
//	}
//}
//
//int main()
//{
//	glfwInit();
//
//	// set hints fot the next call of GLFWCreateWindow() call
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//	GLFWwindow *window = glfwCreateWindow(800, 600, "First Window", NULL, NULL);
//
//	if (window == NULL)
//	{
//		std::cout << "ERROR::Faild to create GLFW Window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	glfwMakeContextCurrent(window);
//
//	// Init GLAD
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	glEnable(GL_DEPTH_TEST);
//
//	// must be called after glad init
//	glViewport(0, 0, viewPort.width, viewPort.height);	// tell opengl the size of the rendering window
//
//	// -------- callbacks & Configurations -------//
//
//	glfwSetWindowSizeCallback(window, framebuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, mouse_scroll);
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	// hide but capture the cursor (mouse shouldn't leave the window)
//
//	// ------------------- shader program ----------------//
//
//	Shader programShader = Shader("./ModelLoading/vShader_nano_suit_model.glsl", "./ModelLoading/fShader_nano_suit_model.glsl");
//	Model nanoSuitModel = Model("./ModelLoading/Models/nanosuit.obj");
//	
//	programShader.use();
//
//	while (!glfwWindowShouldClose(window))
//	{
//		deltaTime = glfwGetTime() - lastFrame;
//		lastFrame = glfwGetTime();
//
//		processInput(window);
//
//		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// state-set function
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// state-using function
//
//		//--------------------- Drawing --------------------//
//		// Model matrix (from local to wolrd space
//		glm::mat4 model;
//		model = glm::rotate(model, glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//		model = glm::translate(model, glm::vec3(0.0f, -1.7f, 0.0f)); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
//
//		// View matrix (from world to camera space)
//		glm::mat4 view;
//		view = camera.GetViewMatrix();
//		
//		// Projection matrix (from camera to NDC)ss
//		glm::mat4 projection;	// transform to the NDC using prespective projection
//		projection = glm::perspective(glm::radians(camera.fov), (float)viewPort.width / (float)viewPort.height, 0.1f, 100.0f);
//
//		programShader.setMatrix4fv("model", glm::value_ptr(model));
//		programShader.setMatrix4fv("view", glm::value_ptr(view));
//		programShader.setMatrix4fv("projection", glm::value_ptr(projection));
//
//		nanoSuitModel.Draw(programShader);
//		
//		//--------------------------------------------------//
//
//		GLenum err;
//		while ((err = glGetError()) != GL_NO_ERROR) {
//			std::cerr << "OpenGL error: " << err << std::endl;
//		}
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//
//	glfwTerminate();		// deallocate the resources 
//
//	return 0;
//}
