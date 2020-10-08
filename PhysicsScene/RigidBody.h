#pragma once
#include "PhysicsObject.h"

/**
* Class that applies forces to objects.
**/
class RigidBody : public PhysicsObject {
public:
	/**
	* Constructor for the class.
	**/
	RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass);

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void debug() {};

	/**
	* Applies a force to the object.
	**/
	void applyForce(glm::vec2 force, glm::vec2 contact);

	/**
	* Pure virtual funtction used to check for collisions with other objects.
	**/
	virtual bool checkCollision(PhysicsObject* Other) = 0;

	/**
	* Resolves collsions with collided objects.
	**/
	void resolveCollision(RigidBody* other, glm::vec2 contact, glm::vec2* collisionNormal = nullptr);

	/**
	* Gets the position of the rigid body.
	**/
	glm::vec2 getPosition() { return m_position; }
	/**
	* Gets the velocity of the rigid body.
	**/
	glm::vec2 getVelocity() { return m_velocity; }
	/**
	* Gets the mass of the rigid body.
	**/
	float getMass() { return m_mass; }
	/**
	* Gets the rotation of the rigid body.
	**/
	float getRotation() { return m_rotation; }
	/**
	* Gets the linear drag of the rigid body.
	**/
	float getLinearDrag() { return m_linearDrag; }
	/**
	* Gets the angular drag of the rigid body.
	**/
	float getAngularDrag() { return m_angularDrag; }
	/**
	* Gets the angular velocity of the rigid body.
	**/
	float getAngularVelocity() { return m_angularVelocity; }
	/**
	* Gets the momentum of the rigid body.
	**/
	float getMoment() { return m_moment; }
	/**
	* Gets the elasticity of the rigid body.
	**/
	float getElasticity() { return m_elasticity; }
	
	/**
	* Sets the linear drag of the rigid body.
	**/
	void setLinearDrag(float value) { m_linearDrag = value; }
	/**
	* Sets the angular drag of the rigid body.
	**/
	void setAngularDrag(float value) { m_angularDrag = value; }
	/**
	* Sets the elasticity drag of the rigid body.
	**/
	void setElasticity(float value) { m_elasticity = value; }

protected:
	/**
	* The position of the rigid body.
	**/
	glm::vec2 m_position;
	/**
	* The velocity of the rigid body.
	**/
	glm::vec2 m_velocity;
	/**
	* The mass of the rigid body.
	**/
	float m_mass;
	/**
	* The rotation of the rigid body.
	**/
	float m_rotation;
	/**
	* The angular velocity of the rigid body.
	**/
	float m_angularVelocity;
	/**
	* The momentum of the rigid body.
	**/
	float m_moment;
	/**
	* The linear drag of the rigid body.
	**/
	float m_linearDrag = .5f;
	/**
	* The angular drag of the rigid body.
	**/
	float m_angularDrag = .3f;
	/**
	* The elasticity of the rigid body.
	**/
	float m_elasticity = .5f;
};