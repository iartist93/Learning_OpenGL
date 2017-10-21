#include <glad/glad.h>			// include glad before glfw as it contain the opengl headers 
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>				// convert the vector/martix classes to array pointer representation to use and pass them to opengl

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"
#include "../camera.h"
#include "../objects.h"
#include "../shader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


struct
{
	int width = 800;
	int height = 600;
} viewPort;


///GLobal Variables
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastMousePosX = viewPort.width / 2.0f;
float lastMousePosY = viewPort.height / 2.0f;
bool firstMouse = true;

Camera camera;
glm::vec3 lampPosition;
GLFWwindow *window;


void Update();
GLFWwindow* CreateGLFWWindow(int width, int height);

//-----------------------------------------------------------------//
// Callbacks
//------------------------------------------------------------------//
void mouse_callback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastMousePosX = xPos;
		lastMousePosY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastMousePosX;	// increase right
	float yOffset = lastMousePosY - yPos;	// increase downwards

	std::cout << xOffset << " " << yOffset << " " << lastMousePosX << " " << lastMousePosY << std::endl;

	lastMousePosX = xPos;
	lastMousePosY = yPos;

	// objective :: update the forward vector
	camera.ProcessMouseMovement(xOffset, yOffset);
}

void mouse_scroll(GLFWwindow *window, double xOffset, double yOffset)
{
	// objective::update the FOV value
	camera.ProcessMouseScroll(xOffset, yOffset);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput()
{
	// Moving the camera
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)	// Forward
		camera.ProcessKeyboardInput(FORWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)	// BackWord
		camera.ProcessKeyboardInput(BACKWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)	// Right
		camera.ProcessKeyboardInput(RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)	// Left
		camera.ProcessKeyboardInput(LEFT, deltaTime);

	// Exit the games
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	window = CreateGLFWWindow(800, 600);

	// Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// -------- callbacks & Configurations -------//

	glfwSetWindowSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, mouse_scroll);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	// hide but capture the cursor (mouse shouldn't leave the window)

	//-------------- rendering -------------------//

	Update();

	//--------------------------------------------//

	// delallocate all resources when we done form all
	
	// glDeleteVertexArrays(1, &VAO);
	// glDeleteBuffers(1, &VBO);

	glfwTerminate();		// deallocate the resources 

	return 0;
}


void Update()
{
	while (!glfwWindowShouldClose(window))
	{
		deltaTime = glfwGetTime() - lastFrame;
		lastFrame = glfwGetTime();

		processInput();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// state-set function
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// state-using function


		//--------------------- Drawing --------------------//

		// glDrawArrays(GL_TRIANGLES, 0, 36);

		//--------------------------------------------------//

		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cerr << "OpenGL error: " << err << std::endl;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
}


GLFWwindow* CreateGLFWWindow(int width, int height)
{
	glfwInit();

	// set hints fot the next call of GLFWCreateWindow() call
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow *window = glfwCreateWindow(width, height, "First Window", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "ERROR::Faild to create GLFW Window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	glViewport(0, 0, viewPort.width, viewPort.height);	// tell opengl the size of the rendering window

	return window;
}