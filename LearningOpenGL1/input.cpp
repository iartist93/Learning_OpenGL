#include "input.h"
#include "camera.h"

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
	return glm::vec2(currentMouseX - lastMouseX, -(currentMouseY - lastMouseY));
}

void Input::ProcessKeyboard(GLFWwindow *window, float deltaTime)
{
	// Moving the camera
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)	// Forward
		Camera::Main()->ProcessKeyboardInput(FORWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)	// BackWord
		Camera::Main()->ProcessKeyboardInput(BACKWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)	// Right
		Camera::Main()->ProcessKeyboardInput(RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)	// Left
		Camera::Main()->ProcessKeyboardInput(LEFT, deltaTime);

	// Exit the games
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void Input::mouse_callback(GLFWwindow *window, double xPos, double yPos)
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

	float xOffset = currentMouseX - lastMouseX;
	float yOffset = -(lastMouseY - currentMouseY);

	// objective :: update the forward vector
	Camera::Main()->ProcessMouseMovement(xOffset, yOffset);
}

void Input::mouse_scroll(GLFWwindow *window, double xOffset, double yOffset)
{
	// objective::update the FOV value
	Camera::Main()->ProcessMouseScroll(xOffset, yOffset);
}