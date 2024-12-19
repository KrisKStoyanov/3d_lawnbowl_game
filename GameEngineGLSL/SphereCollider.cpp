#include "SphereCollider.h"

#define PI 3.14159265358979324

SphereCollider::SphereCollider(float _radius)
{
	radius = _radius;
}

SphereCollider::~SphereCollider()
{
}

#include <iostream>
bool SphereCollider::Collides(SphereCollider * other)
{
	return ((radius + other->radius) > glm::length(other->GetPosition() - GetPosition()));
}

void SphereCollider::Draw()
{

}

