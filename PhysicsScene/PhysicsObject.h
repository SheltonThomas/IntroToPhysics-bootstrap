#pragma once
#include <glm/ext.hpp>

enum ShapeType {
	PLANE = 0,
	SPHERE,
	SHAPE_COUNT
};


/**
* Used to as base class for anything that needs to be updated.
**/
class PhysicsObject{

protected:
	/**
	* Constructor for the class.
	**/
	PhysicsObject(ShapeType shapeID) : m_shapeID(shapeID) {}

public:
	/**
	* Used to update Physics Objects with a fixed time step.
	**/
	virtual void fixedUpdate(glm::vec2 gravity, float timeSteop) = 0;
	/**
	* Not Used.
	**/
	virtual void debug() = 0;
	/**
	* True virtual function for creating the gizmos(objects).
	**/
	virtual void makeGizmo() = 0;
	virtual void resetPosition() {}

	/**
	* Used to get what kind of shape the physics object is.
	**/
	ShapeType getShapeID() { return m_shapeID; }

protected:
	/**
	* Used to set what kind of shape the physics object is.
	**/
	ShapeType m_shapeID;
};

