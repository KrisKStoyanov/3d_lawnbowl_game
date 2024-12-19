#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

struct Vertex
{
	glm::vec4 coords;
	glm::vec4 color;
	glm::vec2 uv;
	glm::vec3 normal;
};

#endif
