#pragma once
#include <glm/ext.hpp>
#include "PhysicsObject.h"
#include <vector>

class PhysicScene{

public:
	PhysicScene();
	~PhysicScene();

	void addActor(PhysicsObject* actor);
	void removeActor(PhysicsObject* actor);
	void update(float deltaTime);
	void updateGizmos();

	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	glm::vec2 getGravity() const { return m_gravity; }

	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	float getTimeStep() const { return m_timeStep; }

	void debugScene();

	void checkForCollision();

	static bool planeToPlane(PhysicsObject*, PhysicsObject*);
	static bool planeToSphere(PhysicsObject*, PhysicsObject*);
	static bool sphereToPlane(PhysicsObject*, PhysicsObject*);
	static bool sphereToSphere(PhysicsObject*, PhysicsObject*);

protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;
};

