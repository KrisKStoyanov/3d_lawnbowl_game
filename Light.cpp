#include "Light.h"

Light::Light(glm::vec3 _position, glm::vec3 _color){
	position = _position;
	color = _color;

	diffuseCol = color * glm::vec3(0.5f);
	ambientCol = diffuseCol * glm::vec3(0.2f);
	specularCol = glm::vec3(1.0f);
}

Light::~Light()
{

}

