#pragma once

#include <glm/glm.hpp>

class Collider
{
private:
	glm::vec3 position;
public:
	virtual bool Collides(Collider* other) { return 0; };
	virtual glm::vec3 GetPosition() { return glm::vec3(position); };
	virtual void SetPosition(glm::vec3 newPosition) { position = newPosition; };
};

