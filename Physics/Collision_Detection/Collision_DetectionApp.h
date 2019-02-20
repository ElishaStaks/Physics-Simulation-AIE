#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Sphere.h"
#include "PhysicsScene.h"
#include "RigidBody.h"
#include "Plane.h"

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
	Sphere*             m_sphere1;
	Sphere*             m_sphere2;
	Plane*              m_plane;
	Plane*              m_plane2;
	Plane*              m_plane3;
	Plane*              m_plane4;
	RigidBody*          rigid;
	PhysicsScene*       m_physicsScene;
};