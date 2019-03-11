#pragma once


#include <SFML\Graphics.hpp>

#include <memory>

#include "state.h"
#include "../Track/track.h"
#include "../Car/car.h"
#include "../Car/simpleAiCar.h"
#include "../Car/neuronCar.h"

class LevelEditState: public State {
private:
	static constexpr unsigned GRID_SIZE = 16;
	std::unique_ptr<Track> track = nullptr;

	sf::VertexArray outerTrack, innerTrack;
	sf::VertexArray* selectedTrack = &outerTrack;
	std::vector<std::unique_ptr<Car>> cars;

private:
struct Overlab {
	bool overlab;
	sf::Vector2f position;
};
// TODO: Move These to Math class
float calculateDistance(const sf::Vector2f& pointA, const sf::Vector2f& pointB) const;
Overlab overlaps(const sf::Vector2f& pointA, const sf::Vector2f& pointB, const sf::Vector2f& pointC, const sf::Vector2f& pointD) const;
Overlab overlaps(const sf::RectangleShape& shape, const sf::Vector2f& pointC, const sf::Vector2f& pointD) const;

public:
	LevelEditState(sf::RenderWindow& window);

	void init() override;
	void update() override;
	void render() const override;
	void cleanUp() override;

	void onKeyPressed(sf::Event& evt) override;
	void onKeyReleased(sf::Event& evt) override;
	void onMouseButtonPressed(sf::Event& evt) override;
};