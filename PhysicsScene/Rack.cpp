#include "Rack.h"

// Used to say which direction it needs to draw the balls.
enum Direction {
	UP = 0,
	DOWN
};

Rack::Rack(int ballCount, float ballSize, glm::vec2 startingPosition, PhysicScene* scene){
	// Initialies the direction to start creating the balls.
	Direction direction = UP;

	// Sets the position to start drawing the balls and other information for the balls.
	glm::vec2 newPosition = startingPosition;
	glm::vec2 zeroVector(0, 0);
	glm::vec4 color(0, 0, 1, 1);

	// While ball count isnt the amount of balls wanted in rack, create balls.
	int ballsAdded = 0;
	int ballsInRow = 2;
	while (ballsAdded != ballCount)
	{
		if (ballsAdded == 0){
			Sphere* newBall = new Sphere(newPosition, zeroVector, ballSize, color);
			scene->addActor(newBall);
			ballsAdded++;
		}

		else {
			for (int i = 0; i < ballsInRow; i++) {
				if (i == 0){
					if (direction == UP)
						newPosition = glm::vec2(newPosition.x + ballSize * 2, newPosition.y - ballSize);
					else if(direction == DOWN)
						newPosition = glm::vec2(newPosition.x + ballSize * 2, newPosition.y + ballSize);
				}
				else {
					if(direction == UP)
						newPosition = glm::vec2(newPosition.x, newPosition.y + ballSize * 2);
					else if(direction == DOWN)
						newPosition = glm::vec2(newPosition.x, newPosition.y - ballSize * 2);
				}

				Sphere* newBall = new Sphere(newPosition, zeroVector, ballSize, color);
				scene->addActor(newBall);
				ballsAdded++;

				if (ballsAdded == ballCount)
					break;
			}

			ballsInRow++;
			if (direction == UP)
				direction = DOWN;
			else if (direction == DOWN)
				direction = UP;
		}
	}
}
