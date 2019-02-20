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

	static bool plane2Plane(PhysicsObject*, PhysicsObject*) { return false; }
	static bool plane2Sphere(PhysicsObject*, PhysicsObject*) { return false; }
	static bool plane2Box(PhysicsObject*, PhysicsObject*) { return false; }
	static bool sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2);
	static bool sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);
	static bool sphere2Box(PhysicsObject* obj1, PhysicsObject* obj2) { return false; }
	static bool box2Plane(PhysicsObject*, PhysicsObject*) { return false; }
	static bool box2Sphere(PhysicsObject*, PhysicsObject*) { return false; }
	static bool box2Box(PhysicsObject*, PhysicsObject*) { return false; }

protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;
};