#include "PlayerCar.h"

PlayerCar::PlayerCar(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color):
	Car(position, size, color)
{
}

void PlayerCar::calculateMove() {
	forward = forwardPressed;
	backward = backwardPressed;
	left = leftPressed;
	right = rightPressed;
}