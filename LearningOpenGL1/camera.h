#pragma once

#include <glad\glad.h>
#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>


const float SENSITIVITY = 0.1f;
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
	Camera(glm::vec3 position, glm::vec3 up, glm::vec3 forward, float yaw, float pitch, float fov);
	
	glm::mat4 GetViewMatrix();
	void ProcessMouseMovement(double xOffset, double yOffset);
	void ProcessMouseScroll(double xOffset, double yOffset);
	void ProcessKeyboardInput(CameraMovments direction, float deltaTime);

private:
	void UpdateCameraVectors();
};

Camera::Camera(
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f),
	float yaw = YAW, 
	float pitch = PITCH, 
	float fov = FOV
)
{
	this->position = position;
	this->worldUp = up;
	this->forward = forward;
	this->yaw = yaw;
	this->pitch = pitch;
	this->fov = fov;

	UpdateCameraVectors();
}


void Camera::ProcessMouseMovement(double xOffset, double yOffset)
{
	xOffset *= SENSITIVITY;
	yOffset *= SENSITIVITY;

	pitch += yOffset;
	yaw += xOffset;

	// constrains
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(double xOffset, double yOffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yOffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;

	UpdateCameraVectors();
}

void Camera::ProcessKeyboardInput(CameraMovments direction, float deltaTime)
{
	float velocity = MOVEMENTSPEED * deltaTime;

	// Moving the camera
	if (direction == FORWARD)	// Forward
		position += forward * velocity;
	
	if (direction == BACKWARD)	// BackWord
		position -= forward * velocity;
	
	if (direction == RIGHT)	// Right
		position += right * velocity;
	
	if (direction == LEFT)	// Left
		position -= right * velocity;
}


void Camera::UpdateCameraVectors()
{
	// caclating the new direction
	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

	// forward is inially looking towards -ve z-axis
	// forward is already included in the LookAt function <-- camPos + forwardVec = targetPos
	forward = glm::normalize(front);

	right = glm::normalize(glm::cross(forward, worldUp));
	up = glm::normalize(glm::cross(forward, right));
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, position + forward, up);
}