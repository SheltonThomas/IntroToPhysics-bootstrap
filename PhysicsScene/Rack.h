#pragma once
#include "Sphere.h"
#include "PhysicScene.h"

class Rack{
public:
	Rack(int ballCount, float ballSize, glm::vec2 startingPosition, PhysicScene* scene);
};

