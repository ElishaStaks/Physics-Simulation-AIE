#pragma once
#include "RigidBody.h"
#include <Gizmos.h>

class Sphere : public RigidBody {
public:
	Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, float linearDrag, float angularDrag, float elasticity, glm::vec4 colour);
	~Sphere();

	void makeGizmo() override;
	virtual bool checkCollision(PhysicsObject* pOther);

	void resolveCollision(RigidBody* actor2) override;

	float getRadius() { return m_radius; }
	glm::vec4 getColour() { return m_colour; }

protected:
	float m_radius;
	glm::vec4 m_colour;
};