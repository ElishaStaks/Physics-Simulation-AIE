#include "Sphere.h"
#include <glm/ext.hpp>

Sphere::Sphere(const glm::vec2& position, const glm::vec2& velocity, const float radius, const float mass,
	const glm::vec4& colour, const bool kinematic, const bool isStatic,
	const float elasticity, const float linearDrag, const float angularDrag)
	: RigidBody(SPHERE, position, velocity, 0.0f, mass, colour, kinematic, isStatic, elasticity, linearDrag, angularDrag)
{
	m_radius = radius;
	m_position = position;
	m_velocity = velocity;
	m_radius = radius;
	m_mass = mass;
	m_colour = colour;
	m_kinematic = kinematic;
	m_isStaticRigid = isStatic;
	m_elasticity = elasticity;
	m_linearDrag = linearDrag;
	m_angularDrag = angularDrag;
}

Sphere::~Sphere()
{
}

void Sphere::makeGizmo()
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 25, m_colour);
}

void Sphere::SetRadius(const float radius)
{
	m_radius = radius;
}
