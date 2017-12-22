#include <glad/glad.h>			// include glad before glfw as it contain the opengl headers 
#include "GLView.h"
#include <iostream>


GLView::GLView(const std::string& viewName, int width, int height, bool resizable)
{
	this->width = width;
	this->height = height;

	glfwInit();

	glfwWindowHint(GLFW_RESIZABLE, resizable ? true : false);	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	glfwWindow = glfwCreateWindow(width, height, viewName.c_str(), NULL, NULL);

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

	glfwSetWindowSizeCallback(glfwWindow, WindowEventHandler::OnFramebufferSizeCallback);
	glfwSetCursorPosCallback(glfwWindow, WindowEventHandler::OnGLFWMouseCallback);
	glfwSetScrollCallback(glfwWindow, WindowEventHandler::OnGLFWMouseScrollCallback);

	glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	// hide but capture the cursor (mouse shouldn't leave the window)
}

bool GLView::windowShouldClose()
{
	return glfwWindowShouldClose(glfwWindow) ? true : false;
}

void GLView::terminate()
{
	glfwSetWindowShouldClose(glfwWindow, 1);
}

void GLView::swpapBuffer()
{
	glfwSwapBuffers(glfwWindow);
}

void GLView::pollEvents()
{
	glfwPollEvents();
}
