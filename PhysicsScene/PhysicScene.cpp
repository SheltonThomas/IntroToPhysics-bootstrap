#include "PhysicScene.h"

PhysicScene::PhysicScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0)) {
}

PhysicScene::~PhysicScene() {

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

	static float accumulatedTime = 0.f;
	accumulatedTime += deltaTime;

	while (accumulatedTime >= m_timeStep){
		for (auto pActor : m_actors){
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}

		accumulatedTime -= m_timeStep;
	}
}

void PhysicScene::updateGizmos(){

	for (auto pActor : m_actors) {
		pActor->makeGizmo();
	}
}