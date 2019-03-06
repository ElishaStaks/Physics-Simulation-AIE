#include "AABB.h"
#include <Gizmos.h>
#include <iostream>


AABB::AABB(const glm::vec2 & halfExtents, const glm::vec2 & position, glm::vec2 velocity, float mass,  float linearDrag, float angularDrag, float elasticity, glm::vec4 colour)
	:	RigidBody(BOX, position, velocity, mass, 0, linearDrag, angularDrag, elasticity, colour), m_halfExtents(halfExtents)
{
	m_colour = colour;
}

AABB::~AABB()
{
}

bool AABB::checkCollision(PhysicsObject * pOther)
{
	AABB* box = dynamic_cast<AABB*>(pOther);

	if ( box != nullptr) {
		if (!(box->getMax().x < this->getMin().x || box->getMax().y < this->getMin().y ||
			box->getMin().x > this->getMax().x || box->getMin().y < this->getMin().y)) {
			std::cout << "COLLISION SUCCESSFUL" << std::endl;
			return true;
		}
	}
	return false;
}

void AABB::resolveCollision(RigidBody * actor2)
{
	//glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position);
	//glm::vec2 relativeVelocity = actor2->getVelocity() - m_velocity;
	//float elasticity = (m_elasticity + actor2->getElasticity()) / 2.0f;

	//float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) /
	//glm::dot(normal, normal * ((1 / m_mass) + (1 / actor2->getMass())));

	//glm::vec2 force = normal * j;
	//applyForceToActor(actor2, force);
	//std::cout << "COLLISION SUCCESSFUL" << std::endl;
}
	
glm::vec2 AABB::getMin() const
{
	return m_position - m_halfExtents;
}

glm::vec2 AABB::getMax() const
{
	return m_position + m_halfExtents;
}

glm::vec2 AABB::getExtents() const
{
	return m_halfExtents;
}

void AABB::makeGizmo()
{
	aie::Gizmos::add2DAABBFilled(m_position, m_halfExtents, m_colour);
}
