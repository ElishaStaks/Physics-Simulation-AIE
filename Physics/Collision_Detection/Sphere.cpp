#include "Sphere.h"
#include <glm/ext.hpp>

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, float linearDrag, float angularDrag, float elasticity, glm::vec4 colour) 
	: RigidBody(SPHERE, position, velocity, mass, 0, linearDrag, angularDrag, 1, colour)
{
	m_radius = radius;
	m_colour = colour;
}

Sphere::~Sphere()
{
}

void Sphere::makeGizmo()
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 20, m_colour);
}

bool Sphere::checkCollision(PhysicsObject * pOther)
{
	Sphere* sphere =  dynamic_cast<Sphere*>(pOther);

	if (sphere != nullptr) {
		float distance = glm::distance(sphere->m_position, this->m_position);
        float radius = sphere->m_radius + this->m_radius;
		
		if (distance < radius) {
			return true;
		}
	}
	return false;
}

void Sphere::resolveCollision(RigidBody * actor2)
{
	glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position);
	glm::vec2 relativeVelocity = actor2->getVelocity() - m_velocity;
	float elasticity = (m_elasticity + actor2->getElasticity()) / 2.0f;

	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) /
		glm::dot(normal, normal * ((1 / m_mass) + (1 / actor2->getMass())));

	glm::vec2 force = normal * j;
	applyForceToActor(actor2, force);
}