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

class Light
{
public:
	Light(glm::vec3 position, glm::vec3 color);
	~Light();
	glm::vec3 position;
	glm::vec3 color;

	//Precalculated values
	glm::vec3 diffuseCol;
	glm::vec3 ambientCol;
	glm::vec3 specularCol;
};

