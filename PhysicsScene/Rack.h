#pragma once
#include "Sphere.h"
#include "PhysicScene.h"

class Rack{
public:
	/**
	* The constructor that handles adding all the balls to the scene.
	**/
	Rack(int ballCount, float ballSize, glm::vec2 startingPosition, PhysicScene* scene);
};

