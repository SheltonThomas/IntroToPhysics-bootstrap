#include "PhysicsSceneApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Gizmos.h>
#include "Rocket.h"

PhysicsSceneApp::PhysicsSceneApp() {

}

PhysicsSceneApp::~PhysicsSceneApp() {

}

bool PhysicsSceneApp::startup() {
	
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	glm::vec2 gravity(0.f, -10.f);
	glm::vec2 initialPosition(-40.f, 0.f);
	glm::vec2 initialVelocity(25.f, 25.f);

	m_physicsScene = new PhysicScene();
	m_physicsScene->setTimStep(.01f);
	m_physicsScene->setGravity(gravity);

	setUpContinuousDemo(initialPosition, initialVelocity, gravity);

	Sphere* ball = new Sphere(initialPosition, initialVelocity, 1.f, 1.f, glm::vec4(1.f, 0.f, .5f, 1.f));
	m_physicsScene->addActor(ball);

	return true;
}

void PhysicsSceneApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void PhysicsSceneApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	//aie::Gizmos::clear();

	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsSceneApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16.f / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100,
		-100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

void PhysicsSceneApp::setUpContinuousDemo(glm::vec2 initialPosition, glm::vec2 initialVelocity, glm::vec2 gravity){

	//Can use to calculate where something will be after a set amount of time.

	float time = 0.f;
	float timeStep = .5f;
	float radius = 2.f;
	int segments = 12;
	glm::vec4 color = glm::vec4(1, 0, 0, 1);
	glm::vec2 finalPosition = initialPosition;

	while (time <= timeStep * 10){

		finalPosition.x = (initialPosition.x + (initialVelocity.x * time)) + (.5f * gravity.x * (time * time));
		finalPosition.y = (initialPosition.y + (initialVelocity.y * time)) + (.5f * gravity.y * (time * time));

		aie::Gizmos::add2DCircle(finalPosition, radius, segments, color);
		time += timeStep;
	}
}
