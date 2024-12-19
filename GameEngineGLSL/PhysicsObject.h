#pragma once

#include "SphereCollider.h"
#include "PlaneCollider.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "glm/gtx/rotate_vector.hpp"

#include <string>

class PhysicsObject
{
public:
	PhysicsObject(float _mass, Collider* collider);
	~PhysicsObject();
	void UpdateTransform(int deltaTime);
	void Rotate(glm::vec3 vector, float angle, glm::vec3 externalForce = glm::vec3(1.0f,1.0f,1.0f));
	void SetTrajectory(bool _enableRot, float _accel, float _rotMag, bool _enableExtern, glm::vec3 _externForce = glm::vec3(1.0f, 1.0f, 1.0f));
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 velocity;
	glm::vec3 friction = glm::vec3(1.0f,1.0f,1.0f);
	glm::vec3 rotation;
	glm::vec3 worldUp;
	glm::vec3 gravity;
	float acceleration;
	float mass;
	bool grounded;

	bool enableRot;
	float rotationAngle;
	float rotationMag;

	bool enableExtern;
	glm::vec3 externalForce;

	Collider* collider = nullptr;
};

