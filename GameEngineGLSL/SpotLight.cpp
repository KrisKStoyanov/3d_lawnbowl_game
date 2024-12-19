#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff, glm::vec3 ambColor, glm::vec3 difColor, glm::vec3 specColor, float constant, float linear, float quadratic)
{
	this->position = position;
	this->direction = direction;
	this->cutOff = cutOff;
	this->outerCutOff = outerCutOff;
	this->ambColor = ambColor;
	this->difColor = difColor;
	this->specColor = specColor;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}


SpotLight::~SpotLight()
{
}
