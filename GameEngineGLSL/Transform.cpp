#include "Transform.h"

Transform::Transform(glm::vec3 _pos, glm::vec3 _dir)
{
	position = _pos;
	direction = _dir;
}

Transform::~Transform()
{
}

void Transform::Translate(glm::vec3 _newPos)
{
	position += _newPos;
}

void Transform::Rotate(glm::mat4 model, float _angle, glm::vec3 _newPos)
{
	model = glm::rotate(model, _angle, _newPos);
}

void Transform::Scale(glm::mat4 model, glm::vec3 _newScale)
{
	model = glm::scale(model, _newScale);
}

void Transform::Update()
{

}
