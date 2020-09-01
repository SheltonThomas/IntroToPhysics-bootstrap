#include "PhysicScene.h"
#include <list>
#include "RigidBody.h"
#include <iostream>
#include "Sphere.h"
#include "Plane.h"

PhysicScene::PhysicScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0)) {
}

PhysicScene::~PhysicScene() {

	for (auto iActor : m_actors){
		delete iActor;
	}
}

void PhysicScene::addActor(PhysicsObject* actor){

	m_actors.push_back(actor);
}

void PhysicScene::removeActor(PhysicsObject* actor) {
	
	for (auto pActor = m_actors.begin(); pActor < m_actors.end(); ++pActor){
		if (*pActor == actor){
			m_actors.erase(pActor);
		}
	}
}

void PhysicScene::update(float deltaTime){

	/*static std::list<PhysicsObject*> dirty;*/

	static float accumulatedTime = 0.f;
	accumulatedTime += deltaTime;

	while (accumulatedTime >= m_timeStep){
		for (auto pActor : m_actors){
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}

		accumulatedTime -= m_timeStep;
	}

	checkForCollision();

	/*for (auto iActor : m_actors){
		for (auto iOther : m_actors) {
			if (iActor == iOther) 
				continue;

			if (std::find(dirty.begin(), dirty.end(), iActor) != dirty.end() &&
				std::find(dirty.begin(), dirty.end(), iOther) != dirty.end())
				continue;

			RigidBody* actorRigid = dynamic_cast<RigidBody*>(iActor);
			RigidBody* otherRigid = dynamic_cast<RigidBody*>(iOther);

			if (!actorRigid || !otherRigid)
				return;

			if (actorRigid->checkCollision(iOther))
			{
				actorRigid->applyForceToActor(otherRigid, actorRigid->getVelocity() * actorRigid->getMass());
				dirty.push_back(iActor);
				dirty.push_back(iOther);
			}
		}
	}
	dirty.clear();*/
}

void PhysicScene::updateGizmos(){

	for (auto pActor : m_actors) {
		pActor->makeGizmo();
	}
}

void PhysicScene::debugScene(){

	int count = 0;
	for (auto iActor : m_actors)
	{
		std::cout << count << " : ";
		iActor->debug();
		count++;
	}
}


typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctions[] = {

	PhysicScene::planeToPlane, PhysicScene::planeToSphere,
	PhysicScene::sphereToPlane, PhysicScene::sphereToSphere
};

void PhysicScene::checkForCollision(){

	int actorCount = m_actors.size();

	for (int outer = 0; outer < actorCount - 1; outer++) {

		for (int inner = outer + 1; inner < actorCount; inner++) {

			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];
			int shapeID1 = object1->getShapeID();
			int shapeID2 = object2->getShapeID();

			int functionID = (shapeID1 * SHAPE_COUNT) + shapeID2;
			fn collisionFunction = collisionFunctions[functionID];
			if (collisionFunction) {
				collisionFunction(object1, object2);
			}
		}
	}
}

bool PhysicScene::planeToPlane(PhysicsObject* object1, PhysicsObject* object2)
{
	Plane* plane1 = dynamic_cast<Plane*>(object1);
	Plane* plane2 = dynamic_cast<Plane*>(object2);

	if (plane1 != nullptr && plane2 != nullptr){

		return plane1->getNormal() != plane2->getNormal();
	}
}

bool PhysicScene::planeToSphere(PhysicsObject* object1, PhysicsObject* object2)
{
	sphereToPlane(object2, object1);
	return false;
}

bool PhysicScene::sphereToPlane(PhysicsObject* object1, PhysicsObject* object2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(object1);
	Plane* plane = dynamic_cast<Plane*>(object2);

	if (sphere != nullptr && plane != nullptr) {

		glm::vec2 collisionNormal = plane->getNormal();
		float sphereToPlaneDistance = glm::dot(sphere->getPosition(), collisionNormal - plane->getDistance());

		if (sphereToPlaneDistance < 0) {
			collisionNormal *= -1.f;
			sphereToPlaneDistance *= -1;
		}

		sphereToPlaneDistance -= sphere->getRadius();

		if (sphereToPlaneDistance <= 0){

			sphere->applyForce(-sphere->getVelocity() * sphere->getMass());

			return true;
		}
	}

	return false;
}

bool PhysicScene::sphereToSphere(PhysicsObject* object1, PhysicsObject* object2)
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(object1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(object2);

	if (sphere1 != nullptr && sphere2 != nullptr) {

		if (glm::distance(sphere1->getPosition(), sphere2->getPosition()) <= sphere1->getRotation() + sphere2->getRadius()) {

			sphere1->applyForceToActor(sphere2, sphere1->getVelocity() * sphere1->getMass());
			return true;
		}
	}
	return false;
}
