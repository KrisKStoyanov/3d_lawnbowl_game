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

class Material
{
public:
	Material(glm::vec3 ambRefl, glm::vec3 difRefl, glm::vec3 specRefl, float shininess);
	~Material();
	glm::vec3 ambRefl;
	glm::vec3 difRefl;
	glm::vec3 specRefl;
	//glm::vec4 emitCols;
	float shininess;
};

