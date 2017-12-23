#include "camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 up, glm::vec3 forward, float yaw, float pitch, float fov)
{
	this->position = position;
	this->worldUp = up;
	this->forward = forward;
	this->yaw = yaw;
	this->pitch = pitch;
	this->fov = fov;

	UpdateCameraVectors();
}


/* Update the PITCH and YAW angels of the camera */
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


/* Update the Front/Right/Up Vectors of the camera related to the YAW/PITCH values */
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
	up = glm::normalize(glm::cross(right, forward));
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, position + forward, up);
}