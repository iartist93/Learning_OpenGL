#include <glad/glad.h>			// include glad before glfw as it contain the opengl headers 
#include "window.h"
#include "input.h"
#include <iostream>

Window* Window::_instance;

Window* Window::MainWindow()
{
	if (!_instance)
	{
		_instance = new Window();
		_instance->Init();
	}
	return _instance;
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Window::Init()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	glfwWindow = glfwCreateWindow(width, height, "First Window", NULL, NULL);

	if (glfwWindow == NULL)
	{
		std::cout << "ERROR::Faild to create GLFW Window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(glfwWindow);

	// Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, width, height);	// tell opengl the size of the rendering window


	// ------------ callbacks & Configurations ------------//

	glfwSetWindowSizeCallback(glfwWindow, Window::framebuffer_size_callback);
	glfwSetCursorPosCallback(glfwWindow, Input::mouse_callback);
	glfwSetScrollCallback(glfwWindow, Input::mouse_scroll);

	glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	// hide but capture the cursor (mouse shouldn't leave the window)
}