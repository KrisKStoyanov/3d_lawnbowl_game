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

class Transform
{
public:
	Transform(glm::vec3 _pos = glm::vec3(0.0f,0.0f,0.0f), glm::vec3 _dir = glm::vec3(0.0f,0.0f,0.0f));
	~Transform();
	glm::vec3 position;
	glm::vec3 direction;
	void Translate(glm::vec3 _newPos);
	void Rotate(glm::mat4 model, float _angle, glm::vec3 _newDir);
	void Scale(glm::mat4 model, glm::vec3 _newScale);
	void Update();
};

