#include "Sphere.h"
#include <glm/ext.hpp>

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float rotation, float radius, float linearDrag, float angularDrag, float angularVelocity, float moment, float elasticity, glm::vec4 colour)
	: RigidBody(SPHERE, position, velocity, mass, rotation, linearDrag, angularDrag, angularVelocity, moment, 1)
{
	m_radius = radius;
	m_colour = colour;
}

Sphere::~Sphere()
{
}

void Sphere::makeGizmo()
{
	glm::vec2 end = glm::vec2(std::cos(m_rotation), std::sin(m_rotation)) * m_radius;
	aie::Gizmos::add2DCircle(m_position, m_radius, 20, m_colour);
	aie::Gizmos::add2DLine(m_position, m_position + end, glm::vec4(1, 1, 1, 1));
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

void Sphere::resolveCollision(RigidBody * actor2, glm::vec2 contact, glm::vec2* collisionNormal)
{
	// Find the vector between their centres, or use the provided direction of force, and make sure its normalised
	glm::vec2 normal = glm::normalize(collisionNormal ? *collisionNormal : actor2->getPosition() - m_position);
	// Get the vector perpendicular to the collision normal
	glm::vec2 perp(normal.y, -normal.x);

	// Determine the total velocity of the contact points for the two objects, for both linear and rotational

	// 'r' is the radius from axis to apllication of force
	float r1 = glm::dot(contact - m_position, -perp);
	float r2 = glm::dot(contact - actor2->getPosition(), perp);
	// Velocity of the contact point on this object
	float v1 = glm::dot(m_velocity, normal) - r1 * m_angularVelocity;
	// Velocity of contact point on actor2
	float v2 = glm::dot(actor2->getVelocity(), normal) + r2 * actor2->getAngularVelocity();

	// They're moving closer
	if (v1 > v2) {
		// Calculate the effective mass at contact point for each object
		// ie how much the contact point will move due to force applied
		float mass1 = 1.0f / (1.0f / m_mass + (r1*r1) / m_moment);
		float mass2 = 1.0f / (1.0f / actor2->getMass() + (r2*r2) / actor2->getMoment());

		float elasticity = (m_elasticity + actor2->getElasticity()) / 2.0f;
		glm::vec2 force = (1.0f + elasticity) *mass1*mass2 / (mass1 + mass2) * (v1 - v2) * normal;

		// Apply equal and opposite forces
		applyForce(-force, contact - m_position);
		actor2->applyForce(force, contact - actor2->getPosition());
	}
}