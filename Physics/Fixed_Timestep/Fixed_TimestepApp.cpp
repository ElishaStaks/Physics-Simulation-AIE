#include "Fixed_TimestepApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Gizmos.h>
#include <glm\ext.hpp>
#include "Sphere.h"

Fixed_TimestepApp::Fixed_TimestepApp() {

}

Fixed_TimestepApp::~Fixed_TimestepApp() {

}

bool Fixed_TimestepApp::startup() {
	
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	// Memory allocating
	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, 0));
	// Setting the time step
	m_physicsScene->setTimeStep(0.01f);

	m_ball1 = new Sphere(glm::vec2(-10, 0), glm::vec2(0, 0), 10.0f, 8.0f, 1.f, 1.f, glm::vec4(1, 0, 0, 1));
	m_ball2 = new Sphere(glm::vec2(-10, -1), glm::vec2(0, 0), 2.0f, 2.0f, 1.f, 1.f, glm::vec4(0, 1, 0, 1));
	m_physicsScene->addActor(m_ball2);
	m_physicsScene->addActor(m_ball1);

	return true;
}

void Fixed_TimestepApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	delete m_physicsScene;
	aie::Gizmos::destroy();
}

void Fixed_TimestepApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_physicsScene->debugScene();
	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizsmos();

	/*if (input->isKeyDown(aie::INPUT_KEY_UP)) {

	}*/


	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Fixed_TimestepApp::draw() {

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