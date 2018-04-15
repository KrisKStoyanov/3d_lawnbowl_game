#include "DirLight.h"

DirLight::DirLight(glm::vec3 direction, glm::vec3 ambColor, glm::vec3 difColor, glm::vec3 specColor)
{
	this->direction = direction;
	this->ambColor = ambColor;
	this->difColor = difColor;
	this->specColor = specColor;
}


DirLight::~DirLight()
{
}
