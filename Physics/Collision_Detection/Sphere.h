#pragma once
#include "RigidBody.h"
#include <Gizmos.h>

class Sphere : public RigidBody {
public:
	Sphere(const glm::vec2& position, const glm::vec2& velocity, const float radius, const float mass, 
		const glm::vec4& colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), const bool kinematic = false, const bool isStatic = false, 
		const float elasticity = 1.0f, const float linearDrag = 0.0f, const float angularDrag = 0.0f);
	~Sphere();

	void makeGizmo() override;
    void SetRadius(const float radius);
	float GetRadius() const { return m_radius; }
	glm::vec4 getColour() { return m_colour; }

protected:
	float m_radius;
	glm::vec4 m_colour;
};