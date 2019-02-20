#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
#include "Sphere.h"

class Fixed_TimestepApp : public aie::Application {
public:

	Fixed_TimestepApp();
	virtual ~Fixed_TimestepApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	PhysicsScene*       m_physicsScene;
	Sphere*             m_ball1;
	Sphere*             m_ball2;
	int*                fuel;
};