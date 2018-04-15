#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <vector>
#include "PhysicsObject.h"

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();
	std::vector<PhysicsObject*> physicsObjects;
	void HandlePhysics(int deltaTime);
	void HandleCollisions();
};

