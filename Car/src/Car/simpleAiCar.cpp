#include "SimpleAiCar.h"

SimpleAiCar::SimpleAiCar(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color):
	Car(position, size, color) {}

void SimpleAiCar::calculateMove() {
	enum class Directions {
		FRONT = 0,
		FRONT_RIGHT_MID,
		FRONT_RIGHT,
		BACK_RIGHT,
		BACK,
		BACK_LEFT,
		FRONT_LEFT,
		FRONT_LEFT_MID,
	};
	const float frontDist = distanceToObstacles[(size_t)Directions::FRONT];
	const float frontRightMidDist = distanceToObstacles[(size_t)Directions::FRONT_RIGHT_MID];
	const float frontRightDist = distanceToObstacles[(size_t)Directions::FRONT_RIGHT];
	const float backRightDist = distanceToObstacles[(size_t)Directions::BACK_RIGHT];
	const float backDist = distanceToObstacles[(size_t)Directions::BACK];
	const float backLeftDist = distanceToObstacles[(size_t)Directions::BACK_LEFT];
	const float frontLeftDist = distanceToObstacles[(size_t)Directions::FRONT_LEFT];
	const float frontLeftMidDist = distanceToObstacles[(size_t)Directions::FRONT_LEFT_MID];

	const float forwardThreshold = visionRange * 0.45f;
	const float backwardThreshold = visionRange * 0.80f;
	const float turnThreshold = visionRange * 0.01f;

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