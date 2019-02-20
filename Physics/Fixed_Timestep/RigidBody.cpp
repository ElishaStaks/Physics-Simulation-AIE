#include "RigidBody.h"
#include <iostream>

using namespace std;

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
	cout << "The actors mass: " << getMass() << endl;
	cout << "The actors X position: " << m_position.x << "The actors Y position: " <<  m_position.y <<  endl;
	cout << "The actors velocity: " << m_velocity.x << m_velocity.y << endl;
	cout << "The actors rotation: " << getRotation() << endl;
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