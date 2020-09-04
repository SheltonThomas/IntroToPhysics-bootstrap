#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicScene.h"

class PhysicsSceneApp : public aie::Application {
public:

	PhysicsSceneApp();
	virtual ~PhysicsSceneApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void setUpContinuousDemo(glm::vec2 pos, glm::vec2 velocity, glm::vec2 gravity);

	glm::vec2 calculateVelocity(glm::vec2 initialPosition, glm::vec2 finalPosition, float gravity, float time);

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	PhysicScene* m_physicsScene;
};