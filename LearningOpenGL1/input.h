#pragma once

#include <glm/glm/glm.hpp>
#include <GLFW/glfw3.h>

class Input
{
private:
	static int lastMouseX;
	static int lastMouseY;
	static int currentMouseX;
	static int currentMouseY;
	static bool firstMouse;

public:
	static glm::vec2 GetMousePosition();
	static glm::vec2 GetMouseOffset();

public:	// callback
	static void ProcessKeyboard(GLFWwindow *window, float deltaTime);
	static void mouse_callback(GLFWwindow *window, double xPos, double yPos);
	static void mouse_scroll(GLFWwindow *window, double xOffset, double yOffset);
};