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
#include<iostream>
void PhysicsEngine::HandleCollisions()
{
	for (int i = 0; i != physicsObjects.size(); i++) {
		if (physicsObjects[i]->collider != nullptr) {
			physicsObjects[i]->collider->SetPosition(physicsObjects[i]->position);
		}
		SphereCollider* sphereColi = dynamic_cast<SphereCollider*>(physicsObjects[i]->collider);
		PlaneCollider* planeColi = nullptr;
		if (sphereColi == nullptr) {
			planeColi = dynamic_cast<PlaneCollider*>(physicsObjects[i]->collider);
		}
		for (int j = i + 1; j != physicsObjects.size(); j++) {
			if (physicsObjects[j]->collider != nullptr) {
				physicsObjects[j]->collider->SetPosition(physicsObjects[j]->position);
			}
			SphereCollider* sphereColj = dynamic_cast<SphereCollider*>(physicsObjects[j]->collider);
			if (planeColi != nullptr) {
				if (planeColi->Collides(sphereColj)) {
					sphereColj->SetPosition(glm::vec3(sphereColj->GetPosition().x, planeColi->GetPosition().y, sphereColj->GetPosition().z));
					//std::cout << "collision with plane detected" << std::endl;
				}
			}
			else {
				if (sphereColi->Collides(sphereColj)) {
					physicsObjects[i]->velocity *= -.5;
					physicsObjects[j]->velocity *= -.5;
					//std::cout << "collision with sphere detected" << std::endl;
				}
			}
		}
	}
}

