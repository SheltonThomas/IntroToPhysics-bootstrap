#include "PhysicsSceneApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Gizmos.h>
#include "Sphere.h"
#include "Plane.h"
#include "Rack.h"

PhysicsSceneApp::PhysicsSceneApp() {

}

PhysicsSceneApp::~PhysicsSceneApp() {

}

bool PhysicsSceneApp::startup() {
	
	// increase the 2D line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	//Initialize gravity and the physics scene

	glm::vec2 gravity(0.f, 0.f);

	m_physicsScene = new PhysicScene();
	m_physicsScene->setTimeStep(.01f);
	m_physicsScene->setGravity(gravity);


	//Create the wall.
	Plane* wall1 = new Plane(glm::vec2(0, 1), 50);
	Plane* wall2 = new Plane(glm::vec2(0, 1), -50);
	Plane* wall3 = new Plane(glm::vec2(1, 0), 90);
	Plane* wall4 = new Plane(glm::vec2(1, 0), -90);

	//Ball information
	float ballScalar = 2.5f;
	float cueBallSize = 1.7f * ballScalar;
	float ballSize = 1.6f * ballScalar;
	glm::vec4 cueBallColor(1, 1, 1, 1);
	glm::vec2 cueBallStartingVelocity(0, 0);

	glm::vec2 zeroVector(0, 0);
	glm::vec4 ballsColor(0, 0, 1, 1);
	glm::vec2 ballsStartingPosition(25, 0);

	//Create ball and rack
	Sphere* cueBall = new Sphere(glm::vec2(-50, 0), cueBallStartingVelocity, cueBallSize, cueBallColor);
	Rack rack = Rack(15, ballSize, ballsStartingPosition, m_physicsScene);

	//add the ball and walls to the scene.

	m_physicsScene->addActor(cueBall);

	m_physicsScene->addActor(wall1);
	m_physicsScene->addActor(wall2);
	m_physicsScene->addActor(wall3);
	m_physicsScene->addActor(wall4);

	return true;
}

void PhysicsSceneApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void PhysicsSceneApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

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
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 
		100 / aspectRatio, -1.0f, 1.0f));

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

glm::vec2 PhysicsSceneApp::calculateVelocity(glm::vec2 initialPosition, glm::vec2 finalPosition, float gravity, float time)
{
	glm::vec2 initialVelocity = glm::vec2(0, 0);

	initialVelocity.x = (finalPosition.x - initialPosition.x) / time;
	initialVelocity.y = (finalPosition.y - initialPosition.y - (0.5f * gravity * (time * time)) / time);

	return initialVelocity;
}
