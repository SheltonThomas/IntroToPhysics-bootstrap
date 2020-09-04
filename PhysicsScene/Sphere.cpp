#include "Sphere.h"
#include <Gizmos.h>

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 color)
	: RigidBody(SPHERE, position, velocity, 0.f, mass){

	m_radius = radius;
	m_color = color;
	m_moment = .5f * mass * radius * radius;
}

void Sphere::makeGizmo() {

	aie::Gizmos::add2DCircle(m_position, m_radius, 500, m_color);
}

void Sphere::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	RigidBody::fixedUpdate(gravity, timeStep);
}

bool Sphere::checkCollision(PhysicsObject* otherActor)
{
	Sphere* otherSphere = dynamic_cast<Sphere*>(otherActor);

	if (otherSphere) {
		return glm::distance(m_position, otherSphere->getPosition()) < m_radius + otherSphere->getRadius();
	}

	return false;
}
