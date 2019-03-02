#pragma once

#include <SFML\Graphics.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <utility>
#include<iostream>
class Car {
protected:
	sf::RectangleShape body; // TODO: Replace with texture
	sf::Vector2f position, velocity;
	float turnSpeed = 0.045f, maxSpeed = 6;
	float speed = 0;

	static constexpr size_t numLines = 8;
	static constexpr float PI = 3.1415926535897932f;
	std::array<std::pair<sf::Vector2f, sf::Vector2f>, numLines> visionLines{
		std::pair<sf::Vector2f, sf::Vector2f>{{0, 0},{visionRange, visionRange}},
	};
	std::array<float, numLines> visionLineAngles{
		0,
		PI * 0.15f,
		PI * 0.33f,
		PI - PI / 3,
		PI,
		PI + PI / 3,
		-PI * 0.33f,
		-PI * 0.15f
	};
	std::array<float, numLines> distanceToObstacles {
		visionRange + 1 // Set all to max range + 1
	};
public:
	bool backward = false, left = false, right = false; // TODO: Do not make this public
	float rotation = 0;
	static constexpr float visionRange = 280; 
	bool forwardPressed = false, backwardPressed = false, leftPressed = false, rightPressed = false;
	bool hit = false, onFinishLine = false;
	uint_fast16_t score = 0;
public:
	Car(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);

	inline const std::array<std::pair<sf::Vector2f, sf::Vector2f>, numLines>& getVisionLines() const { return visionLines; }
	inline const sf::RectangleShape& getShape() const { return body; }
	inline const sf::Vector2f getPosition() const { return position; }
	inline uint_fast8_t getSpeed() const { return static_cast<uint_fast8_t>(speed * 100); }
	inline void setSpeed(uint_fast8_t value) { speed = std::min(100.0f, std::max(0.0f, static_cast<float>(value))) / 100.0f; };
	void setDistanceToObstacle(size_t visionLineIndex, float distance);

	void update(sf::RenderWindow& window);
	virtual void calculateMove() = 0;
};