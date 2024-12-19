#include "PlaneCollider.h"

PlaneCollider::PlaneCollider(glm::vec3 _direction)
{
	direction = _direction;
}


PlaneCollider::~PlaneCollider()
{

}

bool PlaneCollider::Collides(SphereCollider * other)
{
	return (other->radius >= (glm::length(other->GetPosition().y - GetPosition().y)));
}
