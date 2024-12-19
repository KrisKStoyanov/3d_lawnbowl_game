#pragma once

#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#pragma comment(lib, "glew32.lib") 
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	VIEW_UP,
	VIEW_DOWN,
	VIEW_LEFT,
	VIEW_RIGHT
};

class Camera
{
private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat movementSpeed;
	GLfloat mouseSensitivity;

	void UpdateCameraVectors();

public:
	Camera(glm::vec3 position, glm::vec3 target, GLfloat movementSpeed, GLfloat mouseSensitivity);
	
	~Camera();

	glm::vec3 GetPosition();

	glm::mat4 projection;
	glm::mat4 view;

	glm::vec3 target;

	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
	void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true);

	bool firstMouse = true;
	GLfloat lastX;
	GLfloat lastY;

	void Setup(int windowWidth, int windowHeight);
	void UpdateViewMatrix();
};

