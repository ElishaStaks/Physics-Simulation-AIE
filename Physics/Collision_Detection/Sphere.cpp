#include "Sphere.h"
#include <glm/ext.hpp>

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, float linearDrag, float angularDrag, 
	float elasticity, bool kinematic, bool isStatic, glm::vec4 colour)
	: RigidBody(SPHERE, position, velocity, mass, 0, linearDrag, angularDrag, 1, kinematic, isStatic, colour)
{
	m_position = position;
	m_velocity = velocity;
	m_mass = mass;
	m_radius = radius;
	m_linearDrag = linearDrag;
	m_angularDrag = angularDrag;
	m_elasticity = elasticity;
	isKinematic = kinematic;
	isStaticRigid = isStatic;
	m_colour = colour;
}

Sphere::~Sphere()
{
}

void Sphere::makeGizmo()
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 20, m_colour, nullptr);
}