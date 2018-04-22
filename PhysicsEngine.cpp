#include "PhysicsEngine.h"



PhysicsEngine::PhysicsEngine()
{
}


PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::HandlePhysics(int deltaTime)
{
	for (int i = 0; i < physicsObjects.size(); i++) {
		physicsObjects[i]->UpdateTransform(deltaTime);
	}
}

void PhysicsEngine::HandleCollisions()
{
	for (int i = 0; i != physicsObjects.size(); i++) {
		if (physicsObjects[i]->collider != nullptr) {
			physicsObjects[i]->collider->SetPosition(physicsObjects[i]->position);
		}
		//Attempt to cast this physObj collider as a sphere
		SphereCollider* sphereColi = dynamic_cast<SphereCollider*>(physicsObjects[i]->collider);
		PlaneCollider* planeColi = nullptr;
		//Re-attempt to cast as plane if sphere is invalidated
		if (sphereColi == nullptr) {
			planeColi = dynamic_cast<PlaneCollider*>(physicsObjects[i]->collider);
		}
		for (int j = i + 1; j != physicsObjects.size(); j++) {
			if (physicsObjects[j]->collider != nullptr) {
				physicsObjects[j]->collider->SetPosition(physicsObjects[j]->position);
			}
			SphereCollider* sphereColj = dynamic_cast<SphereCollider*>(physicsObjects[j]->collider);
			//If first physObj collider is a plane check plane collision
			if (planeColi != nullptr) {
				if (planeColi->Collides(sphereColj)) {
					//Cancel out sphere vertical momentum and reposition above the plane on collision
					sphereColj->SetPosition(glm::vec3(sphereColj->GetPosition().x, planeColi->GetPosition().y + sphereColj->radius, sphereColj->GetPosition().z));
				}
			}
			else {
				//If first physObj collider is a sphere check sphere collision
				if (sphereColi->Collides(sphereColj)) {
					physicsObjects[i]->direction = glm::normalize(physicsObjects[i]->position - physicsObjects[j]->position);
					physicsObjects[j]->direction = glm::normalize(physicsObjects[j]->position - physicsObjects[i]->position);
					physicsObjects[i]->acceleration += physicsObjects[j]->acceleration/ physicsObjects[i]->mass;
					physicsObjects[j]->acceleration -= physicsObjects[j]->acceleration / physicsObjects[i]->mass;
				}
			}
		}
	}
}

