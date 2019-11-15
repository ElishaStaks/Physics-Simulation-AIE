#pragma once
#include "PhysicsObject.h"
#include "RigidBody.h"

class Plane : public PhysicsObject
{
public:
	Plane(const glm::vec2& normal, const float distance,
		const glm::vec4& colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), const bool kinematic = false);
	~Plane();

	virtual void FixedUpdate(const glm::vec2& gravity, const float timeStep) {}
	virtual void Debug();
	virtual void makeGizmo() override;
	virtual void resetPosition() {}

	void resolveCollision(RigidBody* actor2);

    glm::vec2 GetNormal() const { return m_normal; }
	float GetDistance() const { return m_distanceToOrigin; }

protected:
	// normalised vector perpendicular to the plane
	glm::vec2 m_normal;
	// distance between the plane and the origin
	float m_distanceToOrigin;
};

