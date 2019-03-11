#include "PhysicsScene.h"
#include "RigidBody.h"
#include "Sphere.h"
#include "Plane.h"
#include <list>
#include <iostream>
#include "AABB.h"

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
		float sphereToPlane = glm::dot(sphere->getPosition(), plane->getNormal()) - plane->getDistance();
		float intersection = sphere->getRadius() - sphereToPlane;

		if (intersection >= 0) {
			sphere->resolveOverlap(collisionNormal * intersection);
			plane->resolveCollision(sphere);
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

			if (sphere1->getKinematic())
				return true;

			sphere1->resolveOverlap( normal * -overlap);
			sphere1->resolveCollision(sphere2);
			return true;
		}
	}
	return false;
}

bool PhysicsScene::sphere2Box(PhysicsObject * obj1, PhysicsObject * obj2)
{
	return box2Sphere(obj2, obj1);
}

bool PhysicsScene::box2Plane(PhysicsObject * obj1, PhysicsObject * obj2)
{
	// Try to cast objects to sphere to sphere
	AABB* box = dynamic_cast<AABB*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);

	// If we are successfull then test for collision
	if (box != nullptr && plane != nullptr) {
		glm::vec2 collisionNormal = plane->getNormal();

		glm::vec2 corners[4];
		corners[0] = box->getMin();
		corners[1] = { box->getMin().x, box->getMax().y };
		corners[2] = box->getMax();
		corners[3] = { box->getMax().x, box->getMin().y };

		float intersection = glm::dot(corners[0], collisionNormal) - plane->getDistance();

		for (int i = 1; i < 4; i++)
		{
			float temp = glm::dot(corners[i], collisionNormal) - plane->getDistance();
			if (temp < intersection) {
				intersection = temp;
			}
		}

		// Box restitution 
		if (intersection <= 0) {
			box->setPosition(box->getPosition() - intersection * collisionNormal);
			plane->resolveCollision(box);
			return true;
		}
	}
	return false;
}

bool PhysicsScene::box2Sphere(PhysicsObject * obj1, PhysicsObject * obj2)
{
	// Try to cast objects to sphere to sphere
	AABB* box = dynamic_cast<AABB*>(obj1);
	Sphere* sphere = dynamic_cast<Sphere*>(obj2);

	// If we are successfull then test for collision
	if (box != nullptr && sphere != nullptr) {
		// clamps the sphere to the box
		glm::vec2 distance = clamp(sphere->getPosition(), box->getMin(), box->getMax());
		// point of which the sphere makes contact with the box
		glm::vec2 point = distance - sphere->getPosition();
		// Sphere collision normal
		glm::vec2 normal = glm::normalize(sphere->getPosition() - box->getPosition());
		
		if (glm::dot(point, point) <= sphere->getRadius() *  sphere->getRadius()) {

			if (box->getKinematic())
				return true;

			// box to sphere restitution
			glm::vec2 pointNormal = glm::normalize(point) * sphere->getRadius();
			float intersection = glm::distance(distance, pointNormal + sphere->getPosition());

			if (intersection >= 0) {
				box->setPosition(box->getPosition() + intersection * point);
				box->resolveCollision(sphere);
			}
			return true;
		}
	}
	return false;
}

bool PhysicsScene::box2Box(PhysicsObject * obj1, PhysicsObject * obj2)
{
	// Try to cast objects to sphere to sphere
	AABB* box = dynamic_cast<AABB*>(obj1);
	AABB* box2 = dynamic_cast<AABB*>(obj2);

	// If we are successfull then test for collision
	if (box != nullptr && box2 != nullptr) {
		// checking if all sides of the aabb are overlapping
		if (!(box->getMax().x < box2->getMin().x || box->getMax().y < box2->getMin().y ||
			  box2->getMax().x < box->getMin().x || box2->getMax().y < box->getMin().y)) {

			if (box->getKinematic())
				return true;

			float x1 = box2->getMax().x - box->getMin().x;
			float x2 = box->getMax().x - box2->getMin().x;

			float y1 = box2->getMax().y - box->getMin().y;
			float y2 = box->getMax().y - box2->getMin().y;

			float smallestDist = x1;

			if (x2 < smallestDist)
				smallestDist = x2;
			if (y1 < smallestDist)
				smallestDist = y1;
			if (y2 < smallestDist)
				smallestDist = y2;

			if (smallestDist == x1) {
				glm::vec2 collisionNormal = glm::vec2(1, 0);

				box->setPosition(box->getPosition() + collisionNormal * smallestDist * 0.5f);
				box2->setPosition(box2->getPosition() - collisionNormal * smallestDist * 0.5f);

				box->resolveCollision(box2);
			}
			else if(smallestDist == x2)
			{
				glm::vec2 collisionNormal = glm::vec2(-1, 0);

				box->setPosition(box->getPosition() + collisionNormal * smallestDist * 0.5f);
				box2->setPosition(box2->getPosition() - collisionNormal * smallestDist * 0.5f);

				box->resolveCollision(box2);
			}
			else if (smallestDist == y1)
			{
				glm::vec2 collisionNormal = glm::vec2(0, 1);

				box->setPosition(box->getPosition() + collisionNormal * smallestDist * 0.5f);
				box2->setPosition(box2->getPosition() - collisionNormal * smallestDist * 0.5f);

				box->resolveCollision(box2);
			}
			else if (smallestDist == y2)
			{
				glm::vec2 collisionNormal = glm::vec2(0, -1);

				box->setPosition(box->getPosition() + collisionNormal * smallestDist * 0.5f);
				box2->setPosition(box2->getPosition() - collisionNormal * smallestDist * 0.5f);

				box->resolveCollision(box2);
			}
			return true;
		}
	}
	return false;
}