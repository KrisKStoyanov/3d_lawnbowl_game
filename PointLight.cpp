#include "PointLight.h"

PointLight::PointLight(glm::vec3 _position, glm::vec3 _ambColor, glm::vec3 _difColor, glm::vec3 _specColor, float _constant, float _linear, float _quadratic)
{
	position = _position;
	ambColor = _ambColor;
	difColor = _difColor;
	specColor = _specColor;
	constant = _constant;
	linear = _linear;
	quadratic = _quadratic;
}


PointLight::~PointLight()
{
}
