#include "PhysicScene.h"
#include <list>
#include "RigidBody.h"
#include <iostream>

PhysicScene::PhysicScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0)) {
}

PhysicScene::~PhysicScene() {

	for (auto iActor : m_actors){
		delete iActor;
	}
}

void PhysicScene::addActor(PhysicsObject* actor){

	m_actors.push_back(actor);
}

void PhysicScene::removeActor(PhysicsObject* actor) {
	
	for (auto pActor = m_actors.begin(); pActor < m_actors.end(); ++pActor){
		if (*pActor == actor){
			m_actors.erase(pActor);
		}
	}
}

void PhysicScene::update(float deltaTime){

	static std::list<PhysicsObject*> dirty;

	static float accumulatedTime = 0.f;
	accumulatedTime += deltaTime;

	while (accumulatedTime >= m_timeStep){
		for (auto pActor : m_actors){
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}

		accumulatedTime -= m_timeStep;
	}

	for (auto iActor : m_actors){
		for (auto iOther : m_actors) {
			if (iActor == iOther) 
				continue;

			if (std::find(dirty.begin(), dirty.end(), iActor) != dirty.end() &&
				std::find(dirty.begin(), dirty.end(), iOther) != dirty.end())
				continue;

			RigidBody* actorRigid = dynamic_cast<RigidBody*>(iActor);
			RigidBody* otherRigid = dynamic_cast<RigidBody*>(iOther);

			if (!actorRigid || !otherRigid)
				return;

			if (actorRigid->checkCollision(iOther))
			{
				actorRigid->applyForceToActor(otherRigid, actorRigid->getVelocity() * actorRigid->getMass());
				dirty.push_back(iActor);
				dirty.push_back(iOther);
			}
		}
	}
	dirty.clear();
}

void PhysicScene::updateGizmos(){

	for (auto pActor : m_actors) {
		pActor->makeGizmo();
	}
}

void PhysicScene::debugScene(){

	int count = 0;
	for (auto iActor : m_actors)
	{
		std::cout << count << " : ";
		iActor->debug();
		count++;
	}
}
