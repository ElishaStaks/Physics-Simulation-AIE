#include "RigidBody.h"
#include <iostream>

using std::cout;
using std::endl;

RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float mass, float rotation, float linearDrag, float angularDrag, 
	float elasticity, bool kinematic, bool isStatic, glm::vec4 colour)
	: PhysicsObject(shapeID), m_position(position), m_mass(mass), m_rotation(rotation), m_velocity(velocity), m_linearDrag(linearDrag), 
	m_angularDrag(angularDrag) ,m_elasticity(elasticity), isKinematic(kinematic), m_colour(colour)
{
	isKinematic = false;
	isStaticRigid = false;
}

RigidBody::~RigidBody()
{
}

void RigidBody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	if (isKinematic || isStaticRigid)
		return;

	applyForce(gravity * m_mass * timeStep);
	m_position += m_velocity * timeStep;

	m_velocity -= m_velocity * m_linearDrag * timeStep;

	if (length(m_velocity) < MIN_LINEAR_THRESHOLD) {
		m_velocity = glm::vec2(0, 0);
	}
}

// Extra info to the console when debugging
void RigidBody::debug()
{
	cout << "Actor mass: " << getMass() << endl;
	cout << "Actor position x: " << m_position.x << endl;
	cout << "Actor position y: " << m_position.y << endl;
	cout << "Actor velocity x: " << m_velocity.x << endl;
	cout << "Actor velocity y: " << m_velocity.y << endl;
	cout << "Actor rotation: " << getRotation() << endl;
}

void RigidBody::resolveCollision(RigidBody * actor2)
{
	if ( this->getRigidStatic() && !actor2->getRigidStatic()) {

		glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position);
		float elasticity = 1;

		float j = glm::dot(-(1 + elasticity) * (actor2->getVelocity()), normal) /
			(1 / actor2->getMass());

		glm::vec2 force = normal * j;
		actor2->applyForce(force);
	
	}
	else if (!this->getRigidStatic() && actor2->getRigidStatic())
	{
		glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position);
		float elasticity = 1;

		float j = glm::dot(-(1 + elasticity) * (this->getVelocity()), normal) /
			(1 / this->getMass());

		glm::vec2 force = normal * j;
		this->applyForce(force);
	}
	else {
		glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position);
		glm::vec2 relativeVelocity = actor2->getVelocity() - m_velocity;
		float elasticity = (m_elasticity + actor2->getElasticity()) / 2.0f;

		float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) /
			glm::dot(normal, normal * ((1 / m_mass) + (1 / actor2->getMass())));

		glm::vec2 force = normal * j;
		applyForceToActor(actor2, force);
		std::cout << "COLLISION SUCCESSFUL" << std::endl;
	}
}

void RigidBody::applyForce(glm::vec2 force)
{
	//f = ma
	m_velocity += force / m_mass;
}

void RigidBody::applyForceToActor(RigidBody * actor2, glm::vec2 force)
{
	applyForce(-force);
	actor2->applyForce(force);
}

void RigidBody::resolveOverlap(const glm::vec2 & displacement)
{
	m_position += displacement;
}

