#pragma once

#include <SFML\Graphics.hpp>

#include <iostream>

#include "car.h"
#include "../NeuralNet/net.hpp" // TODO: Make new network
#include "../GSM/gameStateManager.h" // TODO: Do not use the GSM here

class NeuronCar: public Car {
private:
	Net carBrain;
	void tmpAi();
	bool targetForward = false, targetBackward = false, targetLeft = false, targetRight = false;
public:
	NeuronCar(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);
	void calculateMove() override;
};