#include "Sphere.h"
#include <glm/ext.hpp>

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour) 
	: RigidBody(SPHERE, position, velocity, mass, 0)
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