#pragma once
#include "RigidBody.h"

/**
* Handles sphere creation.
**/
class Sphere : public RigidBody {
public:
	/**
	* The constructor for the class.
	**/
	Sphere(glm::vec2 position, glm::vec2 velocity, float mass, glm::vec4 color);

	virtual void makeGizmo();
	
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);

	virtual bool checkCollision(PhysicsObject* otherActor);

	/**
	* Gets the radius of the sphere.
	**/
	float getRadius() { return m_radius; }
	/**
	* Gets the color of the sphere.
	**/
	glm::vec4 getColor() { return m_color; }

protected:
	/**
	* The radius of the sphere.
	**/
	float m_radius;
	/**
	* The color of the sphere.
	**/
	glm::vec4 m_color;
};
