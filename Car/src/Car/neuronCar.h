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
	bool targetBackward = false, targetLeft = false, targetRight = false;
	sf::Vector2f lastPos;
	float lastRotation, targetForward;
public:
	NeuronCar(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);
	void calculateMove() override;
};