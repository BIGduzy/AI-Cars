#pragma once

#include <SFML\Graphics.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <utility>

class Car {
protected:
	sf::RectangleShape body; // TODO: Replace with texture
	sf::Vector2f position, velocity;
	float power = 3, rotation = 0, turnSpeed = 0.02f, maxSpeed = 6;

	static constexpr size_t numLines = 6;
	static constexpr float PI = 3.1415926535897932f;
	std::array<std::pair<sf::Vector2f, sf::Vector2f>, numLines> visionLines{
		std::pair<sf::Vector2f, sf::Vector2f>{{0, 0},{visionRange, visionRange}},
	};
	std::array<float, numLines> visionLineAngles{
		0,
		PI / 3,
		PI - PI / 3,
		PI,
		PI + PI / 3,
		-PI / 3,
	};
	std::array<float, numLines> distanceToObstacles {
		visionRange + 1 // Set all to max range + 1
	};
	bool forward = false, backward = false, left = false, right = false;
public:
	static constexpr float visionRange = 200; 
	bool forwardPressed = false, backwardPressed = false, leftPressed = false, rightPressed = false;
	bool hit = false, onFinishLine = false;
	uint_fast16_t score = 0;
public:
	Car(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);

	inline const std::array<std::pair<sf::Vector2f, sf::Vector2f>, numLines>& getVisionLines() const { return visionLines; }
	inline const sf::RectangleShape& getShape() const { return body; }
	inline const sf::Vector2f getPosition() const { return position; }
	void setDistanceToObstacle(size_t visionLineIndex, float distance);

	void update(sf::RenderWindow& window);
	virtual void calculateMove() = 0;
};