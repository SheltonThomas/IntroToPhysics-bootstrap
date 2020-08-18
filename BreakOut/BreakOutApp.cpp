#include "BreakOutApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Gizmos.h>
#include <glm\ext.hpp>

BreakOutApp::BreakOutApp() {

}

BreakOutApp::~BreakOutApp() {

}

bool BreakOutApp::startup() {
	//Initialize the Gizmos Singleton class.
	aie::Gizmos::create(255U, 255U, 65536U, 65536U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	return true;
}

void BreakOutApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void BreakOutApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void BreakOutApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspecRatio = 16.f / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100.f, 100.f, -100.f / aspecRatio,
											100.f / aspecRatio, -1.f, 1.f));
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}