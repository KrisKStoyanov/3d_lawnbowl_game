#include "PhysicsObject.h"



PhysicsObject::PhysicsObject(float _mass, Collider* _col = nullptr)
{
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = direction;
	rotationAngle = 0.0f;
	worldUp = glm::vec3(0.0, 1.0, 0.0f);
	gravity = glm::vec3(0.0f, -9.81f, 0.0f);
	mass = _mass;
	collider = _col;
	grounded = false;
	enableRot = false;
}


PhysicsObject::~PhysicsObject()
{
}


void PhysicsObject::UpdateTransform(int deltaTime)
{
	//std::cout << acceleration << std::endl;
	position += velocity * (float(deltaTime) / 1000);
	velocity = (direction * (acceleration * mass));

	if (enableRot) {
		velocity = glm::rotate(velocity, rotationAngle, worldUp);
	}

	if (enableExtern) {
		velocity += externalForce / mass;
	}

	if (acceleration > 0) {
		acceleration -= .005f * float(deltaTime);
	}
	if (acceleration < 0) {
		acceleration += .005f * (deltaTime);
	}
	if (acceleration < .1f && acceleration > -.1f) {
		acceleration = 0;
	}

	if (rotationAngle < rotationMag) {
		rotationAngle += 0.001f;
	}
	if (rotationAngle > rotationMag) {
		rotationAngle -= 0.001f;
	}
	if (rotationAngle == rotationMag || acceleration == 0) {
		enableRot = false;
		rotationAngle = 0.0f;
		enableExtern = false;
	}
}

void PhysicsObject::Rotate(glm::vec3 vector, float angle, glm::vec3 externalForce)
{
	vector = glm::rotate(vector, angle, worldUp) * externalForce;
}

void PhysicsObject::SetTrajectory(bool _enableRot, float _accel, float _rotMag,bool _enableExtern, glm::vec3 _externForce)
{
	enableRot = _enableRot;
	acceleration = _accel;
	rotationMag = _rotMag;

	enableExtern = _enableExtern;
	externalForce = _externForce;
}
