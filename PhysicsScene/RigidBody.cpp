#include "RigidBody.h"

RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass)
	: PhysicsObject(shapeID){

	m_position = position;
	m_velocity = velocity; 
	m_rotation = rotation;
	m_mass = mass;
}

void RigidBody::fixedUpdate(glm::vec2 gravity, float timeStep){

	applyForce(gravity * m_mass * timeStep);
	m_position += m_velocity * timeStep;
}

void RigidBody::applyForce(glm::vec2 force){

	m_velocity += force / m_mass;
}

void RigidBody::applyForceToActor(RigidBody* otherActor, glm::vec2 force){

	otherActor->applyForce(force);
	applyForce(-force);
}

void RigidBody::resolveCollision(RigidBody* other){

	glm::vec2 collisionNormal = glm::normalize(other->getPosition - m_position);
	glm::vec2 relativeVelocity = other->getVelocity() - m_velocity;

	float elasticity = 1.f;
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), collisionNormal /
		glm::dot(collisionNormal, collisionNormal * ((1 / m_mass) + (1 / other->getMass()))));

	glm::vec2 force = collisionNormal * j;

	applyForceToActor(other, -force);

}
