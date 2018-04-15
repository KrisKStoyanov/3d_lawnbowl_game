#include "Material.h"

Material::Material(glm::vec3 _ambRefl, glm::vec3 _difRefl, glm::vec3 _specRefl, float _shininess)
{
	ambRefl = _ambRefl;
	difRefl = _difRefl;
	specRefl = _specRefl;
	shininess = _shininess;
}

Material::~Material()
{
}
