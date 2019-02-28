#pragma once

#include <SFML\Graphics.hpp>

#include <memory>
#include <iostream>

#include "state.h"
#include "../Car/car.h"
#include "../Car/playerCar.h"
#include "../Track/track.h"

class PlayState: public State {
private:
	bool debug = true;
	Track track;
	std::vector<std::unique_ptr<Car>> cars;
	bool wKeyDown = false, aKeyDown = false, sKeyDown = false, dKeyDown = false;
	struct Overlab {
		bool overlab;
		sf::Vector2f position;
	};

private:
	// TODO: Move These to Math class
	float calculateDistance(const sf::Vector2f& pointA, const sf::Vector2f& pointB) const;
	Overlab overlaps(const sf::Vector2f& pointA, const sf::Vector2f& pointB, const sf::Vector2f& pointC, const sf::Vector2f& pointD) const;
	bool overlaps(const sf::RectangleShape& shape, const sf::Vector2f& pointC, const sf::Vector2f& pointD) const;
public:
	PlayState(sf::RenderWindow& window);

	void init() override;
	void update() override;
	void render() const override;
	void cleanUp() override;
	void onKeyPressed(sf::Event& evt) override;
	void onKeyReleased(sf::Event& evt) override;
};