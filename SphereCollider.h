#pragma once

#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider(float _radius);
	~SphereCollider();
	bool Collides(SphereCollider * other);
	float radius;
	void Draw();
};
