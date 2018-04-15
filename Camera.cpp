#include "Camera.h"

Camera::Camera(glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _target = glm::vec3(0.0, 0.0, -1.0), GLfloat _movementSpeed = 0.5f, GLfloat _mouseSensitivity = 0.25f)
{
	yaw = -90.0f;
	pitch = 0.0f;
	front = glm::vec3(0.0, 0.0, -1.0);
	worldUp = glm::vec3(0.0, 1.0, 0.0);
	right = glm::vec3(1.0, 0.0, 0.0);

	position = _position;
	target = _target;
	movementSpeed = _movementSpeed;
	mouseSensitivity = _mouseSensitivity;
	UpdateCameraVectors();
}

Camera::~Camera()
{
}

glm::vec3 Camera::GetPosition()
{
	return position;
}

void Camera::Setup(int windowWidth, int windowHeight)
{
	lastX = windowWidth / 2;
	lastY = windowHeight / 2;
	projection = glm::perspective(90.0f, (GLfloat)windowWidth / (GLfloat)windowHeight, 0.1f, 5000.0f);
}

void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
	GLfloat velocity = movementSpeed * deltaTime;

	if (FORWARD == direction) {
		position += front * velocity;
		target += front * velocity;
	}

	if (BACKWARD == direction) {
		position -= front * velocity;
		target += front * velocity;
	}

	if (LEFT == direction) {
		position -= right * velocity;
	}
	if (RIGHT == direction) {
		position += right * velocity;
	}
	if (UP == direction) {
		position += worldUp * velocity;
	}
	if (DOWN == direction) {
		position -= worldUp * velocity;
	}

	if (VIEW_UP == direction) {
		target += worldUp * velocity;
	}
	if (VIEW_DOWN == direction) {
		target -= worldUp * velocity;
	}
	if (VIEW_LEFT == direction) {
		target -= right * velocity;
	}
	if (VIEW_RIGHT == direction) {
		target += right * velocity;
	}
}
#include <iostream>
void Camera::ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch)
{
	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;
	yaw += xOffset;
	pitch += yOffset;

	if (constrainPitch) {
		if (pitch > 90.0f) {
			pitch = 90.0f;
		}
		if (pitch < -90.0f) {
			pitch = -90.0f;
		}
	}

	UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(newFront);
	right = glm::normalize(glm::cross(front, worldUp)); 
	up = glm::normalize(glm::cross(right, front));
}

void Camera::UpdateViewMatrix()
{
	view = glm::lookAt(position, position + front, up);
}
