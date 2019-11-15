#pragma once
#include <glm/ext.hpp>
#include <vector>
#include "RigidBody.h"

class AABB : public RigidBody
{
public:
	AABB(const glm::vec2& halfExtents, const glm::vec2& position, const glm::vec2& velocity, const float mass,
		const glm::vec4& colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), const bool kinematic = false, const bool isStatic = false,
		const float elasticity = 1.0f, const float linearDrag = 0.0f, const float angularDrag = 0.0f);
	~AABB();

    void makeGizmo() override;

	glm::vec2 getMin() const;
	glm::vec2 getMax() const;
	glm::vec2 getExtents() const;

protected:
	glm::vec2 m_halfExtents;
	glm::vec4 m_colour;
};