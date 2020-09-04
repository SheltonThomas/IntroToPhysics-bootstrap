#pragma once
#include "PhysicsObject.h"
#include "RigidBody.h"

class Plane : public PhysicsObject{
public:
	Plane();
	Plane(glm::vec2 normal, float distanceToOrigin);
	~Plane() {}

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) {}
	virtual void debug() {};
	virtual void makeGizmo();
	virtual void resetPosition() {}

	glm::vec2 getNormal() { return m_normal; }
	float getDistance() { return m_distanceToOrigin; }

	void resolveCollision(RigidBody* other, glm::vec2 contact);

protected:
	glm::vec2 m_normal;
	float m_distanceToOrigin;
};

