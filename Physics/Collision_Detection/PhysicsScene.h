#pragma once
#include <glm/vec2.hpp>
#include <vector>
#include "PhysicsObject.h"

class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();

	void addActor(PhysicsObject* actor);
	bool removeActor(PhysicsObject* actor);
	void update(float deltaTime);
	void updateGizsmos();
	void debugScene();
	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	glm::vec2 getGravity() const { return m_gravity; }

	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	float getTimeStep() const { return m_timeStep; }

	void CheckForCollision();

	static bool plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2) { return false; }
	static bool plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2) { return false; }
	static bool plane2Box(PhysicsObject* obj1, PhysicsObject* obj2) { return false; }
	static bool sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2);
	static bool sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);
	static bool sphere2Box(PhysicsObject* obj1, PhysicsObject* obj2) { return false; }
	static bool box2Plane(PhysicsObject* obj1, PhysicsObject* obj2);
	static bool box2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);
	static bool box2Box(PhysicsObject* obj1, PhysicsObject* obj2);

protected:
	// Function pointer array for doing our collisions
	typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

	fn collisionFunctionArray[9] {
		PhysicsScene::plane2Plane, PhysicsScene::plane2Sphere, PhysicsScene::plane2Box,
		PhysicsScene::sphere2Plane, PhysicsScene::sphere2Sphere, PhysicsScene::sphere2Box,
		PhysicsScene::box2Plane, PhysicsScene::box2Sphere, PhysicsScene::box2Box,
	};

	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;
};