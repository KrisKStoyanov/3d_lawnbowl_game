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

class DirLight
{
public:
	DirLight(glm::vec3 direction, glm::vec3 ambColor, glm::vec3 difColor, glm::vec3 specColor);
	~DirLight();

	glm::vec3 direction;

	glm::vec3 ambColor;
	glm::vec3 difColor;
	glm::vec3 specColor;
};

