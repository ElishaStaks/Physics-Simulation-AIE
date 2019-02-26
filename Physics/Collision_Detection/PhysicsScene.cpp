#include "PhysicsScene.h"
#include "RigidBody.h"
#include "Sphere.h"
#include "Plane.h"
#include <list>
#include <iostream>



// Constructor by default initialises the time and the gravity of the scene
PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{

}

PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors) {
		delete pActor;
	}
}

void PhysicsScene::addActor(PhysicsObject * actor)
{
	m_actors.push_back(actor);
}

bool PhysicsScene::removeActor(PhysicsObject * actor)
{
	for (int x = 0; x < m_actors.size(); ++x) {

		if (m_actors[x] == actor) {
			m_actors.erase(m_actors.begin() + x);
			return true;
		}
	}
	return false;
}

void PhysicsScene::update(float deltaTime)
{
	static std::list<PhysicsObject*> dirty;
	// Update physics at a fixed step
	static float accumulatedTime = 0.0f;
	accumulatedTime += deltaTime;

	while (accumulatedTime >= m_timeStep) {
		for (auto pActor : m_actors) {
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}

		accumulatedTime -= m_timeStep;
		CheckForCollision();
	}
}
	

// Cycles through every actor and creates a gizmos 
void PhysicsScene::updateGizsmos()
{
	for (auto pActor : m_actors) {
		pActor->makeGizmo();
	}
}

void PhysicsScene::debugScene()
{
	int count = 0;
	for (auto pActor : m_actors) {
	std::cout << count << " : ";
		pActor->debug();
		count++;
	}
}

void PhysicsScene::CheckForCollision()
{
	int actorCount = m_actors.size();

	// Need to check for collisions against all objects except this one
	for (int outer = 0; outer < actorCount - 1; ++outer) {
		for (int inner = outer + 1; inner < actorCount; inner++) {
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];
			int shapeId1 = object1->getShapeID();
			int shapeId2 = object2->getShapeID();

			// Using function pointers
			int functionIdx = (shapeId1 * SHAPE_COUNT) + shapeId2;
			fn collisionFunctionPtr = collisionFunctionArray[functionIdx];
			if (collisionFunctionPtr != nullptr) {
				// Did a collision occur?
				collisionFunctionPtr(object1, object2);
			}
		}
	}
}

bool PhysicsScene::sphere2Plane(PhysicsObject *obj1, PhysicsObject *obj2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);

	if (sphere != nullptr && plane != nullptr) {
		glm::vec2 collisionNormal = plane->getNormal();
		glm::vec2 contact = sphere->getPosition() + (collisionNormal * -sphere->getRadius());
		float sphereToPlane = glm::dot(sphere->getPosition(), plane->getNormal()) - plane->getDistance();

	    // If we are behind the plane then we flip the normal
		if (sphereToPlane < 0) {
			collisionNormal *= -1;
			sphereToPlane *= -1;
		}

		float intersection = sphere->getRadius() - sphereToPlane;
		float overlap = intersection - sphereToPlane;

		if (intersection >= 0) {
			plane->resolveCollision(sphere, contact);
			//sphere->resolveOverlap(collisionNormal * -overlap);
			return true;
		}
	}
	return false;
}

bool PhysicsScene::sphere2Sphere(PhysicsObject *obj1, PhysicsObject* obj2)
{
	// Try to cast objects to sphere to sphere
	Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);

	// If we are successfull then test for collision
	if (sphere1 != nullptr && sphere2 != nullptr) {
		float distance = glm::distance(sphere1->getPosition(), sphere2->getPosition());
		float radius = sphere1->getRadius() + sphere2->getRadius();
		float overlap = radius - distance;
		// Sphere collision normal
		glm::vec2 normal = glm::normalize(sphere2->getPosition() - sphere1->getPosition());

		if (distance < radius) {
			sphere1->resolveOverlap( normal * -overlap);
			sphere1->resolveCollision(sphere2, 0.5f * (sphere1->getPosition() + sphere2->getPosition()));
			return true;
		}
	}
	return false;
}