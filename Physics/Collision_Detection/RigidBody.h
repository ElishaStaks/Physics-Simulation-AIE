#pragma once
#include "PhysicsObject.h"
#include <glm/ext.hpp>

// Linear Drag
#define MIN_LINEAR_THRESHOLD 0.1f
// Angular Velocity
#define MIN_ROTATION_THRESHOLD 0.01f

class RigidBody : public PhysicsObject {
public:
	RigidBody(const ShapeType& shapeID, const glm::vec2& position, const glm::vec2& velocity, const float rotation, const float mass, 
		const glm::vec4& colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), const bool kinematic = false, const bool isStatic = false,
		const float elasticity = 1.0f, const float linearDrag = 0.0f, const float angularDrag = 0.0f);
	~RigidBody();

	virtual void FixedUpdate(const glm::vec2& gravity, const float timeStep);
	virtual void Debug();

	//virtual bool checkCollision(PhysicsObject* pOther);
	virtual void resolveCollision(RigidBody* actor2);

	void ApplyForce(const glm::vec2& force);

	void ApplyForceToActor(const glm::vec2& force, RigidBody* actor);

	void resolveOverlap(const glm::vec2& displacement);

    void SetPosition(const glm::vec2& position);
	glm::vec2 GetPosition() const { return m_position; }

	void SetVelocity(const glm::vec2& velocity);
	glm::vec2 GetVelocity() const { return m_velocity; }

	void SetRotation(const float rotation);
	float GetRotation() const { return m_rotation; }

	void SetMass(const float mass);
	float GetMass() const { return m_mass; }

	float GetElasticity() const { return m_elasticity; }

	void SetLinearDrag(const float linearDrag);
	float GetLinearDrag() const { return m_linearDrag; }

	void SetAngularDrag(const float angularDrag);
	float GetAngularDrag() const { return m_angularDrag; }

	//void SetStatic(const bool staticRigidbody);
	//bool GetStatic() const { return m_isStaticRigid; }


protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	glm::vec4 m_colour;
	float m_rotation;  // 2D so we only need a single float to represent rotation
	float m_mass;
	float m_linearDrag;
	float m_angularDrag;
	float m_elasticity;
	bool m_isStaticRigid;
	bool isKinematic;
};