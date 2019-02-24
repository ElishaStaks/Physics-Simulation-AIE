#include "AABB.h"
#include <Gizmos.h>


AABB::AABB(const glm::vec2 & halfExtents, const glm::vec2 & position, glm::vec2 velocity, float mass,  float linearDrag, float angularDrag, float elasticity, glm::vec4 colour)
	:	RigidBody(BOX, position, velocity, mass, 0, linearDrag, angularDrag, elasticity), m_halfExtents(halfExtents)
{
	m_colour = colour;
}

AABB::~AABB()
{
}

bool AABB::checkCollision(PhysicsObject * pOther)
{
	AABB* aabb = dynamic_cast<AABB*>(pOther);

	if (aabb != nullptr) {

	}
	return false;
}

void AABB::resolveCollision(RigidBody * actor2)
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

void AABB::makeGizmo()
{
	aie::Gizmos::add2DAABBFilled(m_position, m_halfExtents, glm::vec4(1, 1, 1, 1));
}