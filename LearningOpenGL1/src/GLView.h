#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "input.h"
#include "camera.h"
#include "Fuck.h"
#include <iostream>

class GLView
{
private:
	friend class WindowEventHandler;

public:
	int width;
	int height;
	GLFWwindow *glfwWindow;

public:
	GLView(const std::string& viewName, int width, int height, bool resizable);
	bool windowShouldClose();
	void terminate();
	void swpapBuffer();
	void pollEvents();
};


class WindowEventHandler
{
public:
	static void OnGLFWMouseCallback(GLFWwindow *window, double xPos, double yPos)
	{
		Input::UpdateMousePosition(xPos, yPos);

		auto director = Fuck::getInstance();
		
		// objective :: update the forward vector
		director->getMainCamera()->ProcessMouseMovement(Input::GetMouseOffset().x, Input::GetMouseOffset().y);
	}

	static void OnGLFWMouseScrollCallback(GLFWwindow *window, double xOffset, double yOffset)
	{
		auto director = Fuck::getInstance();

		// objective::update the FOV value
		director->getMainCamera()->ProcessMouseScroll(xOffset, yOffset);
	}

	static void OnFramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
};