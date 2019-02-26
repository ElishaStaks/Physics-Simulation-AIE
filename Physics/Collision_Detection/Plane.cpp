#include "Plane.h"
#include <glm/ext.hpp>
#include <Gizmos.h>
#include <iostream>

Plane::Plane(): PhysicsObject(ShapeType::PLANE)
{
	m_distanceToOrigin = 0;
	m_normal = glm::vec2(0, 1);
}

Plane::Plane(glm::vec2 normal, float distance) : PhysicsObject(ShapeType::PLANE)
{
	m_distanceToOrigin = distance;
	m_normal = normal;
}

Plane::~Plane()
{
}

void Plane::debug()
{
	std::cout << "Plane normal x: " <<  m_normal.x << std::endl;
	std::cout << "Plane normal y: " << m_normal.y << std::endl;
}

void Plane::makeGizmo()
{
	float lineSegmentLength = 300.0f;
	glm::vec2 centrePoint = m_normal * m_distanceToOrigin;
	//easy to rotate normal through 90 degrees around z
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec4 colour(1, 1, 1, 1);
	glm::vec2 start = centrePoint + (parallel * lineSegmentLength);
	glm::vec2 end = centrePoint - (parallel * lineSegmentLength);
	aie::Gizmos::add2DLine(start, end, colour);
}

void Plane::resolveCollision(RigidBody * actor2, glm::vec2 contact, glm::vec2* collisionNormal)
{
	// The plane is static, so the relative velocity is just the actor2's velocity
	glm::vec2 vRel = actor2->getVelocity();
	float e = actor2->getElasticity();
	float j = glm::dot(-(1 + e) * (vRel), m_normal) / (1 / actor2->getMass());

	glm::vec2 force = m_normal * j;
	actor2->applyForce(force, contact - actor2->getPosition());

	//float elasticity = 1;

	//float j = glm::dot(-(1 + elasticity) * (actor2->getVelocity()), m_normal) /
	//	(1 / actor2->getMass());

	//glm::vec2 force = m_normal * j;
	//actor2->applyForce(force);
}