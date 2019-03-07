#include "AABB.h"
#include <Gizmos.h>
#include <iostream>


AABB::AABB(const glm::vec2 & halfExtents, const glm::vec2 & position, glm::vec2 velocity, float mass,  float linearDrag, float angularDrag, 
	float elasticity, bool kinematic, bool isStatic, glm::vec4 colour)
	:	RigidBody(BOX, position, velocity, mass, 0, linearDrag, angularDrag, elasticity, kinematic, isStatic, colour), m_halfExtents(halfExtents)
{
	m_halfExtents = halfExtents;
	m_position = position;
	m_velocity = velocity;
	m_mass = mass;
	m_linearDrag = linearDrag;
	m_angularDrag = angularDrag;
	m_elasticity = elasticity;
	isKinematic = kinematic;
	isStaticRigid = isStatic;
	m_colour = colour;
}

AABB::~AABB()
{
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
	aie::Gizmos::add2DAABB(m_position, m_halfExtents, m_colour);
}
