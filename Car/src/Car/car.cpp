#include "car.h"

Car::Car(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color):
	body(size),
	position(position),
	velocity(0, 0)
{
	body.setPosition(position);
	body.setFillColor(color);
	body.setOrigin({size.x / 2, size.y / 2});
}

void Car::setDistanceToObstacle(size_t visionLineIndex, float distance) {
	if (visionLineIndex < numLines) {
		distanceToObstacles[visionLineIndex] = distance;
	}
};

void Car::update(sf::RenderWindow& window) {
	// Movement
	// TODO: Add acceleration
	float vx = (maxSpeed * cos(rotation) * 0.1f) * speed;
	float vy = (maxSpeed * sin(rotation) * 0.1f) * speed;
	if (velocity.x < maxSpeed && velocity.x > -maxSpeed) {
		velocity.x += vx;
	}

	if (velocity.y < maxSpeed && velocity.y > -maxSpeed)
		velocity.y += vy;

	// TODO: Maybe not hardcode this
	if (backward) {
		velocity.x *= 0.92f;
		velocity.y *= 0.92f;
	}

	if (left && (std::round(velocity.x) != 0 || std::round(velocity.y) != 0 || true)) { // TODO: Remove true when AI is good
		rotation -= turnSpeed;
	}

	if (right && (std::round(velocity.x) != 0 || std::round(velocity.y) != 0 || true)) { // TODO: Remove true when AI is good
		rotation += turnSpeed;
	}

	position += velocity;

	// Clamp to window
	position.x = std::max(0.0f, std::min(static_cast<float>(window.getSize().x), position.x));
	position.y = std::max(0.0f, std::min(static_cast<float>(window.getSize().y), position.y));

	// TODO: Make reset function
	if (hit) {
		position = {200, 100};
		rotation = 0;
		velocity = {0, 0};
		for (auto& distance : distanceToObstacles) {
			distance = visionRange + 1;
		}
	}

	body.setPosition(position);
	body.setRotation(rotation * 180 / 3.1415926535f);

	// Update line positions
	size_t i = 0;
	for (auto& line : visionLines) {
		line.first = position;
		float r = rotation + visionLineAngles[i];
		line.second = position + sf::Vector2f{visionRange * cos(r), visionRange * sin(r)};
		++i;
	}
}