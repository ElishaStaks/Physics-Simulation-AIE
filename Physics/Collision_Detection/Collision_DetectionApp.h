#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Sphere.h"
#include "PhysicsScene.h"
#include "RigidBody.h"
#include "Plane.h"
#include "AABB.h"

class Collision_DetectionApp : public aie::Application {
public:

	Collision_DetectionApp();
	virtual ~Collision_DetectionApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	PhysicsScene*       m_physicsScene;
};