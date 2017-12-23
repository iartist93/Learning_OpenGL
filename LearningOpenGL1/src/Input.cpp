#include "input.h"
#include "camera.h"
#include "Fuck.h"
#include <iostream>

int Input::lastMouseX;
int Input::lastMouseY;
int Input::currentMouseX;
int Input::currentMouseY;
bool Input::firstMouse = true;

glm::vec2 Input::GetMousePosition()
{
	return glm::vec2(currentMouseX, currentMouseY);
}

glm::vec2 Input::GetMouseOffset()
{
	float offsetX = currentMouseX - lastMouseX;
	float offsetY = -(currentMouseY - lastMouseY);

	std::cout << "Mouse Offset " << offsetX << " " << offsetY << std::endl;

	return glm::vec2(offsetX, offsetY);
}

void Input::UpdateMousePosition(int xPos, int yPos)
{
	if (firstMouse)
	{
		lastMouseX = xPos;
		lastMouseY = yPos;
		currentMouseX = xPos;
		currentMouseY = yPos;
		firstMouse = false;
	} 
	else 
	{
		lastMouseX = currentMouseX;
		lastMouseY = currentMouseY;

		currentMouseX = xPos;
		currentMouseY = yPos;
	}
}

void Input::ProcessKeyboard(GLFWwindow *window, float deltaTime)
{
	// Moving the camera
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)	// Forward
		Fuck::getInstance()->getMainCamera()->ProcessKeyboardInput(FORWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)	// BackWord
		Fuck::getInstance()->getMainCamera()->ProcessKeyboardInput(BACKWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)	// Right
		Fuck::getInstance()->getMainCamera()->ProcessKeyboardInput(RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)	// Left
		Fuck::getInstance()->getMainCamera()->ProcessKeyboardInput(LEFT, deltaTime);

	// Exit the games
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}
}
