#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>

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

	static void UpdateMousePosition(int xPos, int yPos);

public:	// callback
	static void ProcessKeyboard(GLFWwindow *window, float deltaTime);
};