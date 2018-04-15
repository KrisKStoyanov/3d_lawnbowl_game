#pragma once

#include "SphereCollider.h"
#include "PlaneCollider.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <string>

class PhysicsObject
{
public:
	PhysicsObject(float _mass, Collider* collider);
	~PhysicsObject();
	void UpdateTransform(int deltaTime);
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 velocity;
	glm::vec3 friction = glm::vec3(1.0f,1.0f,1.0f);
	glm::vec3 rotationSpeed;
	float acceleration;
	float mass;
	bool grounded;
	Collider* collider = nullptr;
};

