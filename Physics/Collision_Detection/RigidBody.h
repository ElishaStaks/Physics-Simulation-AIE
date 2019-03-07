#pragma once
#include "PhysicsObject.h"
#include <glm/ext.hpp>

// Linear Drag
#define MIN_LINEAR_THRESHOLD 0.1f
// Angular Velocity
#define MIN_ROTATION_THRESHOLD 0.01f

class RigidBody : public PhysicsObject {
public:
	RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float mass, float rotation, float linearDrag, float angularDrag, 
		float elasticity, bool kinematic, bool isStatic, glm::vec4 colour);
	~RigidBody();

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void debug();

	//virtual bool checkCollision(PhysicsObject* pOther);
	virtual void resolveCollision(RigidBody* actor2);

	void applyForce(glm::vec2 force);
	void applyForceToActor(RigidBody* actor2, glm::vec2 force);
	void resolveOverlap(const glm::vec2& displacement);

	void setVelocity(glm::vec2 newVelocity) { m_velocity = newVelocity; }
	void setLinearDrag(float linearDrag) { m_linearDrag = linearDrag; }
	void setAngularDrag(float angularDrag) { m_angularDrag = angularDrag; }
	void setElasticity(float elasticity) { m_elasticity = elasticity; }
	void setPosition(glm::vec2 position) { m_position = position; }
	void setRigidStatic(bool state) { isStaticRigid = state; }
	void setKinematic(bool state) { isKinematic = state; }

	glm::vec2 getPosition() { return m_position; }
	glm::vec2 getVelocity() { return m_velocity; }
	float getMass() { return m_mass; }
	float getRotation() { return m_rotation; }
	float getLinearDrag() { return m_linearDrag; }
	float getAngularDrag() { return m_angularDrag; }
	float getElasticity() { return m_elasticity; }

	bool getRigidStatic() { return isStaticRigid; }
	bool getKinematic() { return isKinematic; }


protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	glm::vec4 m_colour;
	float m_rotation;  // 2D so we only need a single float to represent rotation
	float m_mass;
	float m_linearDrag;
	float m_angularDrag;
	float m_elasticity;
	bool  isStaticRigid;
	bool isKinematic;
};