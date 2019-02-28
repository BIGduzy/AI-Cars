#pragma once

#include <SFML\Graphics.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <utility>

#include "car.h"

class PlayerCar : public Car {
public:
	PlayerCar(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);
	void calculateMove() override;
};