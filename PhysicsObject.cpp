#include "PhysicsObject.h"



PhysicsObject::PhysicsObject(float _mass, Collider* _col = nullptr)
{
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	mass = _mass;
	collider = _col;
	grounded = false;
}


PhysicsObject::~PhysicsObject()
{
}
#include <iostream>
void PhysicsObject::UpdateTransform(int deltaTime)
{
	//std::cout << acceleration << std::endl;
	position += velocity * (float(deltaTime) / 1000);
	velocity = direction * (acceleration * mass);

	if (acceleration > 0) {
		acceleration -= .005f * float(deltaTime);
	}
	if (acceleration < 0) {
		acceleration += .005f * (deltaTime);
	}
	if (acceleration < .1f && acceleration > -.1f) {
		acceleration = 0;
	}
}
