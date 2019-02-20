#include "RigidBody.h"
#include <iostream>

using std::cout;
using std::endl;

RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float mass, float rotation) 
	: PhysicsObject(shapeID), m_position(position), m_mass(mass), m_rotation(rotation), m_velocity(velocity)
{
}

RigidBody::~RigidBody()
{
}

void RigidBody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	applyForce(gravity * m_mass * timeStep);
	m_position += m_velocity * timeStep;
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

void RigidBody::resolveCollision(RigidBody * actor2)
{
	glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position);
	glm::vec2 relativeVelocity = actor2->getVelocity() - m_velocity;

	float elasticity = 1;
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) /
		glm::dot(normal, normal * ((1 / m_mass) + (1 / actor2->getMass())));

	glm::vec2 force = normal * j;
	applyForceToActor(actor2, -force);
}
