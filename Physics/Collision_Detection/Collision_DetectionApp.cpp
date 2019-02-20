#include "Collision_DetectionApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

Collision_DetectionApp::Collision_DetectionApp() {

}

Collision_DetectionApp::~Collision_DetectionApp() {

}

bool Collision_DetectionApp::startup() {
	
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();
	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, 0));
	m_physicsScene->setTimeStep(0.01f);

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_sphere1 = new Sphere(glm::vec2(-20, 0), glm::vec2(5, 0), 10.0f, 5.0f, glm::vec4(1, 1, 0, 0));
	m_sphere2 = new Sphere(glm::vec2(20, 0), glm::vec2(-5, 0), 10.0f, 5.0f, glm::vec4(1, 0, 1, 0));
	m_plane = new Plane(glm::normalize(glm::vec2( 0, 300)), 50.0f);
	m_plane2 = new Plane(glm::normalize(glm::vec2(0, -300)), 50.0f);
	m_plane3 = new Plane(glm::normalize(glm::vec2(700, 0)), 90.0f);
	m_plane4 = new Plane(glm::normalize(glm::vec2(-100, 0)), 90.0f);

	m_physicsScene->addActor(m_sphere1);
	m_physicsScene->addActor(m_sphere2);
	m_physicsScene->addActor(m_plane);
	m_physicsScene->addActor(m_plane2);
	m_physicsScene->addActor(m_plane3);
	m_physicsScene->addActor(m_plane4);

	m_sphere1->resolveCollision(m_sphere2);


	return true;
}

void Collision_DetectionApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	delete m_physicsScene;
	aie::Gizmos::destroy();
}

void Collision_DetectionApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();
	m_physicsScene->debugScene();
	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizsmos();

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