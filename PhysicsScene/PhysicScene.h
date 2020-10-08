#pragma once
#include <glm/ext.hpp>
#include "PhysicsObject.h"
#include <vector>

/**
* Class that controls everything that happens.
**/
class PhysicScene{

public:
	/**
	* Constructor for the class.
	**/
	PhysicScene();

	/**
	* Adds an actor to the scene.
	**/
	void addActor(PhysicsObject* actor);
	/**
	* Removes an actor to the scene.
	**/
	void removeActor(PhysicsObject* actor);
	/**
	* Updates all the actors on the scene.
	**/
	void update(float deltaTime);
	/**
	* Draws all the actors.
	**/
	void updateGizmos();

	/**
	* Sets the gravity that is applied to all the actors on the scene.
	**/
	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	/**
	* Gets the gravity of the scene.
	**/
	glm::vec2 getGravity() const { return m_gravity; }

	/**
	* Sets the time step for the fixed update function.
	**/
	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	/**
	* Gets the time step of the scene.
	**/
	float getTimeStep() const { return m_timeStep; }

	/**
	* Not Used
	**/
	void debugScene();

	/**
	* Checks to see if any of the objects on the scene are colliding.
	**/
	void checkForCollision();

	/**
	* Plane to plane collision.
	**/
	static bool planeToPlane(PhysicsObject*, PhysicsObject*);
	/**
	* Plane to sphere collision.
	**/
	static bool planeToSphere(PhysicsObject*, PhysicsObject*);
	/**
	* Sphere to plane collision.
	**/
	static bool sphereToPlane(PhysicsObject*, PhysicsObject*);
	/**
	* Sphere to sphere collision.
	**/
	static bool sphereToSphere(PhysicsObject*, PhysicsObject*);

protected:
	/**
	* Gravity of the scene.
	**/
	glm::vec2 m_gravity;
	/**
	* Time step of the scene.
	**/
	float m_timeStep;
	/**
	* Actors on the scene.
	**/
	std::vector<PhysicsObject*> m_actors;
};

