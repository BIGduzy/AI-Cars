#include "SimpleAiCar.h"

SimpleAiCar::SimpleAiCar(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color):
	Car(position, size, color) {}

void SimpleAiCar::calculateMove() {
	enum class Directions {
		FRONT = 0,
		FRONT_RIGHT = 1,
		BACK_RIGHT = 2,
		BACK = 3,
		BACK_LEFT = 4,
		FRONT_LEFT = 5,
	};
	const float frontDist = distanceToObstacles[(size_t)Directions::FRONT];
	const float frontRightDist = distanceToObstacles[(size_t)Directions::FRONT_RIGHT];
	const float backRightDist = distanceToObstacles[(size_t)Directions::BACK_RIGHT];
	const float backDist = distanceToObstacles[(size_t)Directions::BACK];
	const float backLeftDist = distanceToObstacles[(size_t)Directions::BACK_LEFT];
	const float frontLeftDist = distanceToObstacles[(size_t)Directions::FRONT_LEFT];

	const float forwardThreshold = visionRange * 0.55f;
	const float backwardThreshold = visionRange * 0.95f;
	const float turnThreshold = visionRange * 0.02f;

	// Reset
	forward = false;
	backward = false;
	left = false;
	right = false;

	if (frontDist > forwardThreshold) {
		forward = true;
	}

	if (frontDist < backwardThreshold || backDist < backwardThreshold) {
		backward = true;
	}

	if (frontLeftDist - frontRightDist < -turnThreshold) {
		right = true;
	} else if (frontLeftDist - frontRightDist > turnThreshold) {
		left = true;
	}
}