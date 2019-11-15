#include "AABB.h"
#include <Gizmos.h>
#include <iostream>


AABB::AABB(const glm::vec2& halfExtents, const glm::vec2& position, const glm::vec2& velocity, const float mass,
	const glm::vec4& colour, const bool kinematic, const bool isStatic,
	const float elasticity, const float linearDrag, const float angularDrag)
	: RigidBody(BOX, position, velocity, 0.0f, mass, colour, kinematic, isStatic, elasticity, linearDrag, angularDrag), m_halfExtents(halfExtents)
{
	m_halfExtents = halfExtents;
	m_position = position;
	m_velocity = velocity;
	m_mass = mass;
	m_colour = colour;
	m_kinematic = kinematic;
	m_isStaticRigid = isStatic;
	m_elasticity = elasticity;
	m_linearDrag = linearDrag;
	m_angularDrag = angularDrag;
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
