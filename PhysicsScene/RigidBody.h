#pragma once
#include "PhysicsObject.h"

class RigidBody : public PhysicsObject {
public:
	RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass);
	~RigidBody() {};

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void debug() {};

	void applyForce(glm::vec2 force, glm::vec2 contact);

	virtual bool checkCollision(PhysicsObject* Other) = 0;

	void resolveCollision(RigidBody* other, glm::vec2 contact, glm::vec2* collisionNormal = nullptr);

	glm::vec2 getPosition() { return m_position; }
	glm::vec2 getVelocity() { return m_velocity; }
	float getMass() { return m_mass; }
	float getRotation() { return m_rotation; }
	float getLinearDrag() { return m_linearDrag; }
	float getAngularDrag() { return m_angularDrag; }
	float getAngularVelocity() { return m_angularVelocity; }
	float getMoment() { return m_moment; }

	void setLinearDrag(float value) { m_linearDrag = value; }
	void setAngularDrag(float value) { m_angularDrag = value; }
	float getElasticity() { return m_elasticity; }
	void setElasticity(float value) { m_elasticity = value; }

protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_mass;
	float m_rotation;
	float m_angularVelocity;
	float m_moment;
	float m_linearDrag = .3f;
	float m_angularDrag = .3f;
	float m_elasticity = .5f;
};