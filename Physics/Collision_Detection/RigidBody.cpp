#include "RigidBody.h"
#include <iostream>

using std::cout;
using std::endl;

RigidBody::RigidBody(const ShapeType& shapeID, const glm::vec2& position, const glm::vec2& velocity, const float rotation, const float mass,
	const glm::vec4& colour, const bool kinematic, const bool isStatic,
	const float elasticity, const float linearDrag, const float angularDrag)
	: PhysicsObject(shapeID, colour, kinematic)
{
	m_position = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_mass = mass;
	m_elasticity = elasticity;
	m_linearDrag = linearDrag;
	m_angularDrag = angularDrag;
	m_isStaticRigid = isStatic;
	isKinematic = kinematic;
}

RigidBody::~RigidBody()
{
}

void RigidBody::FixedUpdate(const glm::vec2& gravity, const float timeStep)
{
	if (isKinematic || m_isStaticRigid)
		return;

	ApplyForce(gravity * m_mass * timeStep);
	m_position += m_velocity * timeStep;

	m_velocity -= m_velocity * m_linearDrag * timeStep;

	// if the velocity is small enough to be below the threshold then it is set to 0
	if (length(m_velocity) < MIN_LINEAR_THRESHOLD) {
		m_velocity = glm::vec2(0.0f, 0.0f);
	}
}

// Extra info to the console when debugging
void RigidBody::Debug()
{
	std::cout << "Position: " << m_position.x << ", " << m_position.y << std::endl;
	std::cout << "Velocity: " << m_velocity.x << ", " << m_velocity.y << std::endl;
}

void RigidBody::resolveCollision(RigidBody * actor2)
{
	if ( this->GetStatic() && !actor2->GetStatic()) {

		glm::vec2 normal = glm::normalize(actor2->GetPosition() - m_position);
		float elasticity = 1;

		float j = glm::dot(-(1 + elasticity) * (actor2->GetVelocity()), normal) /
			(1 / actor2->GetMass());

		glm::vec2 force = normal * j;
		actor2->ApplyForce(force);
	
	}
	else if (!this->GetStatic() && actor2->GetStatic())
	{
		glm::vec2 normal = glm::normalize(actor2->GetPosition() - m_position);
		float elasticity = 1;

		float j = glm::dot(-(1 + elasticity) * (this->GetVelocity()), normal) /
			(1 / this->GetMass());

		glm::vec2 force = normal * j;
		this->ApplyForce(force);
	}
	else {
		glm::vec2 normal = glm::normalize(actor2->GetPosition() - m_position);
		glm::vec2 relativeVelocity = actor2->GetVelocity() - m_velocity;
		float elasticity = (m_elasticity + actor2->GetElasticity()) / 2.0f;

		float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) /
			glm::dot(normal, normal * ((1 / m_mass) + (1 / actor2->GetMass())));

		glm::vec2 force = normal * j;
		ApplyForceToActor(force, actor2);
		std::cout << "COLLISION SUCCESSFUL" << std::endl;
	}
}

void RigidBody::ApplyForce(const glm::vec2 & force)
{
	if (m_kinematic || m_isStaticRigid)
		return;

	m_velocity += force / m_mass;
}

void RigidBody::ApplyForceToActor(const glm::vec2 & force, RigidBody* actor)
{
	ApplyForce(-force);
	actor->ApplyForce(force);
}


void RigidBody::resolveOverlap(const glm::vec2 & displacement)
{
	m_position += displacement;
}

void RigidBody::SetPosition(const glm::vec2 & position)
{
	m_position = position;
}

void RigidBody::SetVelocity(const glm::vec2 & velocity)
{
	m_velocity = velocity;
}

void RigidBody::SetRotation(const float rotation)
{
	m_rotation = rotation;
}

void RigidBody::SetMass(const float mass)
{
	m_mass = mass;
}

void RigidBody::SetLinearDrag(const float linearDrag)
{
	m_linearDrag = linearDrag;
}

void RigidBody::SetAngularDrag(const float angularDrag)
{
	m_angularDrag = angularDrag;
}

//void RigidBody::SetStatic(const bool staticRigidbody)
//{
//	m_isStaticRigid = staticRigidbody;
//}