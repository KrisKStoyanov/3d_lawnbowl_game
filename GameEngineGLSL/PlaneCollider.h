#pragma once

#include "Collider.h"
#include "SphereCollider.h"

class PlaneCollider : public Collider
{
public:
	PlaneCollider(glm::vec3 direction);
	~PlaneCollider();
	bool Collides(SphereCollider* sphereCol);
	glm::vec3 direction;
};

