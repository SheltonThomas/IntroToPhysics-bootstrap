#include "PhysicScene.h"
#include "RigidBody.h"
#include "Sphere.h"
#include "Plane.h"
#include <list>
#include <iostream>

PhysicScene::PhysicScene(){

	m_timeStep = .01f;
	m_gravity = glm::vec2(0, 0);
}

PhysicScene::~PhysicScene(){

	for (auto actor : m_actors) {
		delete actor;
	}
}

void PhysicScene::addActor(PhysicsObject* actor){

	m_actors.push_back(actor);
}

void PhysicScene::removeActor(PhysicsObject* actor){

	for (auto i = m_actors.begin(); i < m_actors.end(); i++) {
		if (*i == actor) {
			m_actors.erase(i);
		}
	}
}

void PhysicScene::update(float deltaTime){

	// store how much time has accumulated since last update
	static float accumulatedTime = 0.0f;
	accumulatedTime += deltaTime;

	// while enough time has accumulated...
	while (accumulatedTime >= m_timeStep) {
		// for each PhysicsObject in m_actors...
		for (auto pActor : m_actors) {
			// updated the physics of that object
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}
		// spend the time needed for that update
		accumulatedTime -= m_timeStep;
		// check for collisions
		checkForCollision();
	}
}

void PhysicScene::updateGizmos(){

	for (auto pActor : m_actors) {
		pActor->makeGizmo();
	}
}

void PhysicScene::debugScene(){

	for (auto actor : m_actors) {
		actor->debug();
	}
}

typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctions[] = {

	PhysicScene::planeToPlane, PhysicScene::planeToSphere,
	PhysicScene::sphereToPlane, PhysicScene::sphereToSphere
};

void PhysicScene::checkForCollision(){

	// get the number of actors in the scene
	int actorCount = m_actors.size();

	// check for collisions against all objects except this one
	for (int outer = 0; outer < actorCount - 1; outer++) {
		for (int inner = outer + 1; inner < actorCount; inner++) {
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];
			int shapeID1 = object1->getShapeID();
			int shapeID2 = object2->getShapeID();

			// find the function in the collision function array
			int functionID = (shapeID1 * SHAPE_COUNT) + shapeID2;
			fn collisionFunctionPtr = collisionFunctions[functionID];
			if (collisionFunctionPtr != nullptr) {
				// check collision
				collisionFunctionPtr(object1, object2);
			}
		}
	}
}

bool PhysicScene::planeToPlane(PhysicsObject* object1, PhysicsObject* object2){

	Plane* plane1 = dynamic_cast<Plane*>(object1);
	Plane* plane2 = dynamic_cast<Plane*>(object2);
	if (plane1 != nullptr && plane2 != nullptr) {
		if (plane1->getNormal().x != plane2->getNormal().x || plane1->getNormal().y != plane2->getNormal().y) {
			return true;
		}
	}
	return false;
}

bool PhysicScene::planeToSphere(PhysicsObject* object1, PhysicsObject* object2){

	sphereToPlane(object2, object1);
	return false;
}

bool PhysicScene::sphereToPlane(PhysicsObject* object1, PhysicsObject* object2){

	Sphere* sphere = dynamic_cast<Sphere*>(object1);
	Plane* plane = dynamic_cast<Plane*>(object2);
	if (sphere != nullptr && plane != nullptr) {
		// calculate distance from sphere surface to plane surface
		float sphereToPlaneDistance =
			glm::dot(sphere->getPosition(), plane->getNormal())
			- plane->getDistance();
		// flip the normal if behind the plane
		glm::vec2 collisionNormal = plane->getNormal();
		if (sphereToPlaneDistance < 0) {
			collisionNormal *= -1;
			sphereToPlaneDistance *= -1;
		}

		sphereToPlaneDistance -= sphere->getRadius();
		if (sphereToPlaneDistance <= 0) {

			glm::vec2 contact = sphere->getPosition() + (collisionNormal * -sphere->getRadius());
			plane->resolveCollision(sphere, contact);
			//sphere->applyForce(collisionNormal * sphere->getMass());
			return true;
		}
	}
	return false;
}

bool PhysicScene::sphereToSphere(PhysicsObject* object1, PhysicsObject* object2){

	Sphere* sphere1 = dynamic_cast<Sphere*>(object1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(object2);

	//std::cout << sphere1->getVelocity().x << " " << sphere2->getVelocity().y << std::endl;
	if (sphere1 != nullptr && sphere2 != nullptr) {
		if (glm::distance(sphere1->getPosition(), sphere2->getPosition()) < sphere1->getRadius() + sphere2->getRadius()) {
			
			glm::vec2 contact = (sphere1->getPosition() + sphere2->getPosition()) * .5f;

			//std::cout << sphere1->getVelocity().x << " " << sphere2->getVelocity().y << std::endl;

			sphere1->resolveCollision(sphere2, contact);
			//sphere1->applyForceToActor(sphere2, sphere1->getVelocity() * sphere1->getMass());
			return true;
		}
	}
	return false;
}