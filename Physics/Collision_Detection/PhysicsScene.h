#pragma once
#include <glm/vec2.hpp>
#include <vector>
#include "PhysicsObject.h"

class PhysicsScene
{
public:
	PhysicsScene();
	//PhysicsScene(const glm::vec2& gravity, const float timestep);
	~PhysicsScene();

	// adds an actor to the scene
	void AddActor(PhysicsObject* actor);
	// removes an actor from the scene
	bool RemoveActor(PhysicsObject* actor);
	// This calls the update function for all actors in the scene
	void update(const float deltaTime);
	// updates actors gizmos
	void UpdateGizsmos();
	// calls debug for all actors objects
	void DebugScene();
	// sets the gravity in the scene
	void SetGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	glm::vec2 GetGravity() const { return m_gravity; }
	void SetTimeStep(const float timeStep) { m_timeStep = timeStep; }
	float GetTimeStep() const { return m_timeStep; }
	// checks if actors have collided with eachother in the scene
	void CheckForCollision();

#pragma region Plane Collision
	// checks for collision between plane and plane
	static bool plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2) { return false; }
	// does the reverse of a circle to plane collision check
	static bool plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2) { return sphere2Plane(obj2, obj1); }
	// does the reverse of a box to plane collision check
	static bool plane2Box(PhysicsObject* obj1, PhysicsObject* obj2) { return box2Plane(obj2, obj1); }
#pragma endregion

#pragma region Sphere Collision 
	// checks for collision between circle and plane
	static bool sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2);
	// checks for collision between box and plane
	static bool sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);
	// checks for collision between circle and box
	static bool sphere2Box(PhysicsObject* obj1, PhysicsObject* obj2);
#pragma endregion

#pragma region Box Collision
	// checks for collision between box and plane
	static bool box2Plane(PhysicsObject* obj1, PhysicsObject* obj2);
	// does the reverse of a cirlce to box collision check
	static bool box2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);
	// checks for collision between box and box
	static bool box2Box(PhysicsObject* obj1, PhysicsObject* obj2);
#pragma endregion

	
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