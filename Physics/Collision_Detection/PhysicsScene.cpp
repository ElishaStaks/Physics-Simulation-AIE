#include "PhysicsScene.h"
#include "RigidBody.h"
#include "Sphere.h"
#include "Plane.h"
#include <limits>
#include <list>
#include <iostream>
#include "AABB.h"

// Constructor by default initialises the time and the gravity of the scene
PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{

}

PhysicsScene::~PhysicsScene()
{
	// deallocates the actors to stop memory leaks
	for (auto pActor : m_actors) {
		if (pActor != nullptr) {
			delete pActor;
			pActor = nullptr;
		}
	}
	m_actors.clear();
}

void PhysicsScene::AddActor(PhysicsObject * actor)
{
	m_actors.push_back(actor);
}

bool PhysicsScene::RemoveActor(PhysicsObject * actor)
{
	// searches through the vector for the object
	for (int x = 0; x < m_actors.size(); ++x) {
		// checks if the object was found
		if (m_actors[x] == actor) {

			// increments an iterator that begins at the start of the vector by the current index
			// removes the object at the index
			m_actors.erase(m_actors.begin() + x);
			return true;
		}
	}
	return false;
}

// Fixed Update for physics
void PhysicsScene::update(float deltaTime)
{
	// Update physics at a fixed step
    static float accumulatedTime = 0.0f;
	accumulatedTime += deltaTime;

	while (accumulatedTime >= m_timeStep) {
		// calls fixed update on all actors
		for (auto pActor : m_actors) {
			pActor->FixedUpdate(m_gravity, m_timeStep);
		}

		CheckForCollision();
		accumulatedTime -= m_timeStep;
	}
}
	
// Cycles through every actor and draws them 
void PhysicsScene::UpdateGizsmos()
{
	for (auto pActor : m_actors) {
		pActor->makeGizmo();
	}
}

// calls debug function for each actor
void PhysicsScene::DebugScene()
{
	int count = 0;
	for (auto pActor : m_actors) {
	std::cout << count << " : ";
		pActor->Debug();
		count++;
	}
}

// checks collision between all actors in the scene
void PhysicsScene::CheckForCollision()
{
	int actorCount = m_actors.size();

	// Need to check for collisions against all objects except this one
	for (int outer = 0; outer < actorCount - 1; ++outer) {
		for (int inner = outer + 1; inner < actorCount; inner++) {
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];
			int shapeId1 = object1->GetShapeIDType();
			int shapeId2 = object2->GetShapeIDType();

			// gets the function based on which 2 objects are being checked against
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
		glm::vec2 collisionNormal = plane->GetNormal();
		float sphereToPlane = glm::dot(sphere->GetPosition(), plane->GetNormal()) - plane->GetDistance();
		float intersection = sphere->GetRadius() - sphereToPlane;

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
		float distance = glm::distance(sphere1->GetPosition(), sphere2->GetPosition());
		float radius = sphere1->GetRadius() + sphere2->GetRadius();
		float overlap = radius - distance;
		// Sphere collision normal
		glm::vec2 normal = glm::normalize(sphere2->GetPosition() - sphere1->GetPosition());

		if (distance < radius) {

			if (sphere1->GetKinematic())
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
		glm::vec2 collisionNormal = plane->GetNormal();

		glm::vec2 corners[4];
		corners[0] = box->getMin();
		corners[1] = { box->getMin().x, box->getMax().y };
		corners[2] = box->getMax();
		corners[3] = { box->getMax().x, box->getMin().y };

		float intersection = glm::dot(corners[0], collisionNormal) - plane->GetDistance();

		for (int i = 1; i < 4; i++)
		{
			float temp = glm::dot(corners[i], collisionNormal) - plane->GetDistance();
			if (temp < intersection) {
				intersection = temp;
			}
		}

		// Box restitution 
		if (intersection <= 0) {
			box->SetPosition(box->GetPosition() - intersection * collisionNormal);
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
		glm::vec2 distance = clamp(sphere->GetPosition(), box->getMin(), box->getMax());
		// point of which the sphere makes contact with the box
		glm::vec2 point = distance - sphere->GetPosition();
		// Sphere collision normal
		glm::vec2 normal = glm::normalize(sphere->GetPosition() - box->GetPosition());
		
		if (glm::dot(point, point) <= sphere->GetRadius() *  sphere->GetRadius()) {

			if (box->GetKinematic())
				return true;

			if (box->GetStatic()) {
				return false;
			}

			// box to sphere restitution
			glm::vec2 pointNormal = glm::normalize(point) * sphere->GetRadius();
			float intersection = glm::distance(distance, pointNormal + sphere->GetPosition());

			if (intersection >= 0) 
			{
				box->SetPosition(box->GetPosition() + intersection * point);
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

			if (box->GetKinematic())
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

				box->SetPosition(box->GetPosition() + collisionNormal * smallestDist * 0.5f);
				box2->SetPosition(box2->GetPosition() - collisionNormal * smallestDist * 0.5f);

				box->resolveCollision(box2);
			}
			else if(smallestDist == x2)
			{
				glm::vec2 collisionNormal = glm::vec2(-1, 0);

				box->SetPosition(box->GetPosition() + collisionNormal * smallestDist * 0.5f);
				box2->SetPosition(box2->GetPosition() - collisionNormal * smallestDist * 0.5f);

				box->resolveCollision(box2);
			}
			else if (smallestDist == y1)
			{
				glm::vec2 collisionNormal = glm::vec2(0, 1);

				box->SetPosition(box->GetPosition() + collisionNormal * smallestDist * 0.5f);
				box2->SetPosition(box2->GetPosition() - collisionNormal * smallestDist * 0.5f);

				box->resolveCollision(box2);
			}
			else if (smallestDist == y2)
			{
				glm::vec2 collisionNormal = glm::vec2(0, -1);

				box->SetPosition(box->GetPosition() + collisionNormal * smallestDist * 0.5f);
				box2->SetPosition(box2->GetPosition() - collisionNormal * smallestDist * 0.5f);

				box->resolveCollision(box2);
			}
			return true;
		}
	}
	return false;
}