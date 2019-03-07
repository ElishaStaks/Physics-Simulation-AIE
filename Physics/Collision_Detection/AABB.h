#pragma once
#include <glm/ext.hpp>
#include <vector>
#include "RigidBody.h"

class AABB : public RigidBody
{
public:
	AABB(const glm::vec2& halfExtents, const glm::vec2& position, glm::vec2 velocity, float mass,  float linearDrag, float angularDrag, 
		float elasticity, bool kinematic, bool isStatic, glm::vec4 colour);
	~AABB();

    void makeGizmo() override;
	glm::vec4 getColour() { return m_colour; }

	glm::vec2 getMin() const;
	glm::vec2 getMax() const;
	glm::vec2 getExtents() const;

protected:
	glm::vec2 m_halfExtents;
	glm::vec4 m_colour;
};