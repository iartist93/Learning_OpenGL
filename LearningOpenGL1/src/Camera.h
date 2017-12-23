#pragma once

#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>


const float SENSITIVITY = 0.05f;
const float YAW = -90.0f;		// as 0.0f is the direction vector to the right so we rotate it to left by -90
const float PITCH = 0.0f;
const float FOV = 45.0f;
const float MOVEMENTSPEED = 2.5f;

enum CameraMovments
{
	FORWARD,
	RIGHT,
	BACKWARD,
	LEFT
};


class Camera
{
private:
	void UpdateCameraVectors();

public:
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
	
	glm::vec3 worldUp;

	float fov;
	float movementSpeed;
	float yaw;
	float pitch;

public:
	Camera (
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f),
		float yaw = YAW,
		float pitch = PITCH,
		float fov = FOV
	);

	glm::mat4 GetViewMatrix();
	void ProcessMouseMovement(double xOffset, double yOffset);
	void ProcessMouseScroll(double xOffset, double yOffset);
	void ProcessKeyboardInput(CameraMovments direction, float deltaTime);
};
