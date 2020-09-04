#include "RigidBody.h"
#include <iostream>

RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass)
	: PhysicsObject(shapeID){

	m_position = position;
	m_velocity = velocity; 
	m_rotation = rotation;
	m_mass = mass;
	m_moment = 1;
	m_angularVelocity = 0;
}

void RigidBody::fixedUpdate(glm::vec2 gravity, float timeStep){

	applyForce(gravity * m_mass * timeStep, m_position);

	if (glm::length(m_velocity) < .01f)
		m_velocity = glm::vec2(0, 0);

	if (glm::abs(m_angularVelocity) < .01f)
		m_angularVelocity = 0;

	m_velocity -= m_velocity * m_linearDrag * timeStep;
	m_position += m_velocity * timeStep;

	//std::cout << m_velocity.x << " " << m_velocity.y << std::endl;

	m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;
	m_rotation += m_angularVelocity * timeStep;

}

void RigidBody::applyForce(glm::vec2 force, glm::vec2 position){

	m_velocity += force / m_mass;
	m_angularVelocity += (force.y * position.x - force.x * position.y) / m_moment;
}

void RigidBody::resolveCollision(RigidBody* other, glm::vec2 contact, glm::vec2* collisionNormal){

	// collisionNormal? checks to see if collisionNormal variable is null
	glm::vec2 normal = glm::normalize(collisionNormal ? *collisionNormal
		: other->m_position - m_position);
	glm::vec2 perpendicular(normal.x, normal.y);

	float radius = glm::dot(contact - m_position, -perpendicular);
	float otherRadius = glm::dot(contact - other->m_position, perpendicular);

	float velocity = glm::dot(m_velocity, normal) - radius * m_angularVelocity;

	float otherVelocity = glm::dot(other->m_velocity, normal) + otherRadius * other->m_angularVelocity;

	if (velocity <= otherVelocity) return;

	float mass = 1.0f / (1.0f / getMass() + (radius * radius) / getMoment());
	float otherMass = 1.0f / (1.0f / other->getMass() + (otherRadius * otherRadius) / other->getMoment());

	float elasticity = (m_elasticity + other->m_elasticity) / 2;

	float j = (1.0f + elasticity) * mass * otherMass /
		(mass + otherMass) * (velocity - otherVelocity);

	glm::vec2 force = normal * j;

	other->applyForce(force, contact - other->m_position);
	applyForce(-force, contact - m_position);
}
