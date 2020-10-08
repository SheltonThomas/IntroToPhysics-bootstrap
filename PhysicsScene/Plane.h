#pragma once
#include "PhysicsObject.h"
#include "RigidBody.h"

/**
* Class for creating planes.
**/
class Plane : public PhysicsObject{
public:
	/**
	* Constructor for the class.
	**/
	Plane();
	/**
	* Constructor for the class.
	**/
	Plane(glm::vec2 normal, float distanceToOrigin);

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) {}
	virtual void debug() {};
	virtual void makeGizmo();
	virtual void resetPosition() {}

	/**
	* Gets the normal of the plane.
	**/
	glm::vec2 getNormal() { return m_normal; }
	/**
	* Gets the distance to the origin of the plane.
	**/
	float getDistance() { return m_distanceToOrigin; }

	/**
	* Resolves collisions with the plane.
	**/
	void resolveCollision(RigidBody* other, glm::vec2 contact);

protected:
	/**
	* Stores the normal of the plane.
	**/
	glm::vec2 m_normal;
	/**
	* Stores the distance to the origin of the plane.
	**/
	float m_distanceToOrigin;
};

