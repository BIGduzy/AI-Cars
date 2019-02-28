#pragma once

#include <SFML\Graphics.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <utility>

#include <iostream>

#include "car.h"

class SimpleAiCar: public Car {
public:
	SimpleAiCar(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);
	void calculateMove() override;
};