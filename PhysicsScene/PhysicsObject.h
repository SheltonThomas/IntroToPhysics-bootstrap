#pragma once
#include <glm/ext.hpp>

enum ShapeType {
	PLANE = 0,
	SPHERE,
	SQUARE,
	SHAPE_COUNT
};

class PhysicsObject{

protected:
	PhysicsObject(ShapeType shapeID) : m_shapeID(shapeID) {}

public:
	virtual void fixedUpdate(glm::vec2 gravity, float timeSteop) = 0;
	virtual void debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPosition() {}

	ShapeType getShapeID() { return m_shapeID; }

protected:
	ShapeType m_shapeID;
};

