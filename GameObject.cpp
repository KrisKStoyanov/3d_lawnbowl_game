#include "GameObject.h"
//#include "glm/gtx/string_cast.hpp"

GameObject::GameObject(std::string _name, glm::vec3 _position, glm::vec3 _direction)
{
	name = _name;
	position = _position;
	direction = _direction;
}

GameObject::GameObject(std::string _name, glm::vec3 _position, glm::vec3 _direction, Mesh* _mesh, Texture* _texture, Material* _material, CustomShader* _shader, PhysicsObject* _physObj)
{
	name = _name;
	position = _position;
	direction = _direction;
	mesh = _mesh;
	texture = _texture;
	material = _material;
	customShader = _shader;
	physObj = _physObj;
}

GameObject::~GameObject()
{
}

void GameObject::Setup()
{
	if (physObj != nullptr) {
		physObj->position = position;
		physObj->direction = direction;
	}
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);
}

void GameObject::Draw()
{
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);

	if (texture != NULL) {
		customShader->LoadTexture(texture);
	}

	if (mesh != NULL) {
		if (mesh->drawElements) {
			mesh->DrawElementsMesh(modelMatrix);
		}

		else {
			mesh->DrawArrayMesh(modelMatrix);
		}
	}
}

void GameObject::Update(int deltaTime)
{
	if (physObj != nullptr) {
		position = physObj->position;
	}
}

