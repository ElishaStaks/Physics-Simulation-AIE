#pragma once
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

// Shape of actors
enum ShapeType {
	PLANE = 0,
	SPHERE,
	BOX,
	SHAPE_COUNT
};

//class RigidBody;

class PhysicsObject
{

protected:
	PhysicsObject(const ShapeType& a_shapeID, const glm::vec4& colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), const bool kinematic = false) :
		m_shapeID(a_shapeID), m_colour(colour), m_kinematic(kinematic) {}

public:
	virtual void FixedUpdate(const glm::vec2& gravity, const float timeStep) = 0;
	virtual void Debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPosition() {};

	void SetColour(const glm::vec4& colour) { m_colour = colour; }
	glm::vec4 GetColour() const { return m_colour; }
	void SetKinematic(const bool kinematic) { m_kinematic = kinematic; }
	bool GetKinematic() const { return m_kinematic; }

	ShapeType GetShapeIDType() { return m_shapeID; }

protected:
	// This variable allows us to access our enum
	ShapeType m_shapeID;
	// stores the colour of the object
	glm::vec4 m_colour;
	// determines if the object is kinematic
	bool m_kinematic;
};