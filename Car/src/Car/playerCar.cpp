#include "PlayerCar.h"

PlayerCar::PlayerCar(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color):
	Car(position, size, color)
{
}
void PlayerCar::calculateMove() {
	setSpeed(forwardPressed*100);
	backward = backwardPressed;
	left = leftPressed;
	right = rightPressed;
}