#include "Collision_DetectionApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <iostream>
#include "Plane.h"
#include "Sphere.h"
#include "AABB.h"

Collision_DetectionApp::Collision_DetectionApp() {

}

Collision_DetectionApp::~Collision_DetectionApp() {

}

bool Collision_DetectionApp::startup() {
	
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->SetGravity(glm::vec2(0, -10.0f));
	m_physicsScene->SetTimeStep(0.01f);

	Plane* top = new Plane(glm::normalize(glm::vec2(0, -1)), -55.0);
	m_physicsScene->AddActor(top);
	Plane* bottom = new Plane(glm::normalize(glm::vec2(0, 1)), -55.0);
	m_physicsScene->AddActor(bottom);
	Plane* right = new Plane(glm::normalize(glm::vec2(-1, 0)), -90.0f);
	m_physicsScene->AddActor(right);
	Plane* left = new Plane(glm::normalize(glm::vec2(1, 0)), -90.0f);
	m_physicsScene->AddActor(left);
	Plane* plane1 = new Plane(glm::normalize(glm::vec2(0.707f, 0.707f)), -70.0f);
	m_physicsScene->AddActor(plane1);
	Plane* plane2 = new Plane(glm::normalize(glm::vec2(-0.707f, 0.707f)), -70.0f);
	m_physicsScene->AddActor(plane2);

	AABB* kinematicBox = new AABB(glm::vec2(7.0f, 7.0f), glm::vec2(20, 5), glm::vec2(0, 0), 2.0f, glm::vec4(1, 0, 0, 1), true, false, 1.0f, 0.0f, 0.0f);
	m_physicsScene->AddActor(kinematicBox);

	Sphere* staticCircle2 = new Sphere({ 2, 5 }, { 0.0f, 0.0f }, 8.0f, 1.0f, { 1.0f, 1.0f, 1.0f, 1.0f }, false, true);
	m_physicsScene->AddActor(staticCircle2);

	AABB* box1 = new AABB(glm::vec2(7.0f, 7.0f), { 55.0f, 130.0f }, { 0.0f, 10.0f }, 2.0f, { 1.0f, 0.0f, 0.0f, 1.0f }, false, false);
	m_physicsScene->AddActor(box1);
	AABB* box2 = new AABB(glm::vec2(7.0f, 7.0f), { -65.0f, 7.0f }, { 3.0f, 3.0f }, 5.0f, { 0.0f, 1.0f, 1.0f, 1.0f }, false, false);
	m_physicsScene->AddActor(box2);
	AABB* box3 = new AABB(glm::vec2(7.0f, 7.0f), { 60.0f, -117.0f }, { 10.0f, 0.0f }, 2.0f, { 1.0f, 1.0f, 0.0f, 1.0f }, false, false);
	m_physicsScene->AddActor(box3);
	AABB* box4 = new AABB(glm::vec2(7.0f, 7.0f), { -100, -220.0f }, { -3.0f, 3.0f }, 5.0f, { 1.0f, 0.0f, 1.0f, 1.0f }, false, false);
	m_physicsScene->AddActor(box4);

	Sphere* sphere1 = new Sphere({ -60.0f, 20.0f }, { 0.0f, -10.0f }, 5.0f, 2.0f, { 1.0f, 0.0f, 0.0f, 1.0f }, false, false);
	m_physicsScene->AddActor(sphere1);
	Sphere* sphere2 = new Sphere({ 65.0f, 7.0f }, { -3.0f, -3.0f }, 5.0f, 5.0f, { 0.0f, 1.0f, 1.0f, 1.0f }, false, false);
	m_physicsScene->AddActor(sphere2);
	Sphere* sphere3 = new Sphere({ -60.0f, -7.0f }, { -100, 0.0f }, 5.0f, 2.0f, { 1.0f, 1.0f, 0.0f, 1.0f }, false, false);
	m_physicsScene->AddActor(sphere3);
	Sphere* sphere4 = new Sphere({ 65.0f, -20.0f }, { -100.0f, -3.0f }, 5.0f, 5.0f, { 1.0f, 0.0f, 1.0f, 1.0f }, false, false);
	m_physicsScene->AddActor(sphere4);

	Sphere* sphere5 = new Sphere({ -52.0f, -7.0f }, { -100, 0.0f }, 5.0f, 2.0f, { 1.0f, 1.0f, 0.0f, 1.0f }, false, false);
	m_physicsScene->AddActor(sphere5);
	Sphere* sphere6 = new Sphere({ 75.0f, -20.0f }, { -100.0f, -3.0f }, 5.0f, 5.0f, { 1.0f, 0.0f, 1.0f, 1.0f }, false, false);
	m_physicsScene->AddActor(sphere6);

	sphere1->ApplyForce(glm::vec2(50, 50));
	sphere2->ApplyForce(glm::vec2(0, 50));
	sphere3->ApplyForce(glm::vec2(100, 0));
	sphere4->ApplyForce(glm::vec2(0, 100));
	sphere5->ApplyForce(glm::vec2(-100, 0));
	sphere6->ApplyForce(glm::vec2(0, -100));

	box1->ApplyForce(glm::vec2(0, 100));
	box2->ApplyForce(glm::vec2(50, 0));
	box3->ApplyForce(glm::vec2(100, 50));
	box4->ApplyForce(glm::vec2(10, 50));

	return true;
}

void Collision_DetectionApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	aie::Gizmos::destroy();
	delete m_physicsScene;
	m_physicsScene = nullptr;
}

void Collision_DetectionApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();
	
	m_physicsScene->update(deltaTime);
	m_physicsScene->UpdateGizsmos();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Collision_DetectionApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;
	// Draws all gizmos added to the renderer after the update
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}