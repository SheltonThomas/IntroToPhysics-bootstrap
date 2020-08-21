#pragma once
#include "Sphere.h"
#include <Gizmos.h>
#include <Input.h>

class Rocket : public Sphere{

public:
	Rocket(float power, float fuel, float fuelWeight, float fuelUsageRate, glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 color);
	~Rocket() {}

	void fixedUpdate(glm::vec2 gravity, float timeStep);

	void propulse();

private:
	float m_fuel;
	float m_fuelMass;
	float m_baseMass = 0;
	float m_fuelUsageRate;
	aie::Input* input = aie::Input::getInstance();
	bool isBoosting = false;
	float m_power = 0;
};

