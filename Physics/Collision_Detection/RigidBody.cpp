#include "RigidBody.h"
#include <iostream>

using std::cout;
using std::endl;


RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float mass, float rotation, float linearDrag, float angularDrag, float elasticity)
	: PhysicsObject(shapeID), m_position(position), m_mass(mass), m_rotation(rotation), m_velocity(velocity), m_linearDrag(linearDrag), 
	m_angularDrag(angularDrag) ,m_elasticity(elasticity)
{
}

RigidBody::~RigidBody()
{
}

void RigidBody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	applyForce(gravity * m_mass * timeStep);
	m_position += m_velocity * timeStep;

	m_velocity -= m_velocity * m_linearDrag * timeStep;
	m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;

	if (length(m_velocity) < MIN_LINEAR_THRESHOLD) {
		m_velocity = glm::vec2(0, 0);
	}
	if (abs(m_angularVelocity) < MIN_ROTATION_THRESHOLD) {
		m_angularVelocity = 0;
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

