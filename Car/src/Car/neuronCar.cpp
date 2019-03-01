#include "NeuronCar.h"

NeuronCar::NeuronCar(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color):
	Car(position, size, color),
	carBrain({numLines, numLines, 4}), // 8 -> 8 -> 4,
	lastPos(position),
	lastRotation(rotation)
{
	srand(static_cast<size_t>(time(NULL)));
}

// TODO: We should remove this function and use the simple ai to create a dataset
void NeuronCar::tmpAi() {
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

	const float forwardThreshold = visionRange * 0.55f;
	const float backwardThreshold = visionRange * 0.95f;
	const float turnThreshold = visionRange * 0.01f;

	// Reset
	targetForward = false;
	targetBackward = false;
	targetLeft = false;
	targetRight = false;

	if (frontDist > forwardThreshold) {
		targetForward = true;
	}

	if (frontDist < backwardThreshold) {
		targetBackward = true;
	}

	if ((frontLeftMidDist + frontLeftDist) - (frontRightMidDist + frontRightDist) < -turnThreshold) {
		targetRight = true;
	} else if ((frontLeftMidDist + frontLeftDist) - (frontRightMidDist + frontRightDist) > turnThreshold) {
		targetLeft = true;
	}

	if (lastPos.x > position.x - 3 &&
		lastPos.x < position.x + 3 &&
		lastPos.y > position.y - 3 &&
		lastPos.y < position.y + 3 &&
		lastRotation > rotation - turnSpeed &&
		lastRotation < rotation + turnSpeed)
	{
		targetForward = true;
		targetRight = (frontLeftMidDist + frontLeftDist) < (frontRightMidDist + frontRightDist);
		targetLeft = !targetRight;
	}

	lastPos = position;
	lastRotation = rotation;
}

void NeuronCar::calculateMove() {
	// TODO: Load a trained network from file

	std::vector<double> inputVals;
	for (const auto& distances : distanceToObstacles) {
		double input = (static_cast<double>(distances) - 0) * (1 - 0) / (visionRange - 0) + 0;
		inputVals.emplace_back(input);
	}

	carBrain.feedForward(inputVals);
	std::vector<double> results;
	carBrain.getResults(results);

	// The first few labs are player controlled
	if (score < 2'000) {
		GameStateManager::FPS = 120 + 1 * 8'000; // 50340 NOTE: This only works on release
		tmpAi();
		forward = targetForward;
		backward = targetBackward;
		left = targetLeft;
		right = targetRight;

		std::vector<double> targetVals;
		targetVals.emplace_back(targetForward);
		targetVals.emplace_back(targetBackward);
		targetVals.emplace_back(targetLeft);
		targetVals.emplace_back(targetRight);
		carBrain.backProp(targetVals);
	} else {
		GameStateManager::FPS = 60;
		std::cout << results[0] << std::endl; // forward
		std::cout << results[1] << std::endl; // Backward
		std::cout << results[2] << std::endl; // Left
		std::cout << results[3] << std::endl; // Right
		std::cout << std::endl << std::endl;
		std::cout << std::endl << std::endl;

		// My little car is all grown up, so now it can drive on its own d;) #pride
		forward = results[0] > 0.7f;
		backward = results[1] > 0.7f;
		left = results[2] > 0.7f;
		right = results[3] > 0.7f;
	}
}