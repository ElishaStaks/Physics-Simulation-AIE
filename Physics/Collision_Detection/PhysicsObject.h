#pragma once
#include <glm/vec2.hpp>

// Shape of actors
enum ShapeType {
	PLANE = 0,
	SPHERE,
	BOX,
	SHAPE_COUNT
};

class RigidBody;

class PhysicsObject
{
public:
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void resolveCollision(RigidBody* actor2) = 0;
	virtual void debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPosition() {};

	ShapeType getShapeID() { return m_shapeID; }

protected:
	// Constructor which allows us to pass through our shapeID
	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}
	// This variable allows us to access our enum
	ShapeType m_shapeID;
};