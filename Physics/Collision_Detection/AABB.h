#pragma once
#include <glm/ext.hpp>
#include <vector>
#include "RigidBody.h"

class AABB : public RigidBody
{
public:
	AABB(const glm::vec2& halfExtents, const glm::vec2& position, glm::vec2 velocity, float mass,  float linearDrag, float angularDrag, float elasticity, glm::vec4 colour);
	~AABB();

	virtual bool checkCollision(PhysicsObject* pOther);

	void makeGizmo() override;
	void resolveCollision(RigidBody* actor2) override;
	glm::vec4 getColour() { return m_colour; }

	glm::vec2 getMin() const;
	glm::vec2 getMax() const;

protected:
	glm::vec2 m_halfExtents;
	glm::vec4 m_colour;
};