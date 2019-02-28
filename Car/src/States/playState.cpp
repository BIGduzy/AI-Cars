#include "playState.h"

PlayState::PlayState(sf::RenderWindow& window):
	State(window)	
{
	cars.emplace_back(std::make_unique<PlayerCar>(sf::Vector2f{200, 100}, sf::Vector2f{36, 12}, sf::Color{200, 50, 50}));
	cars.emplace_back(std::make_unique<SimpleAiCar>(sf::Vector2f{200, 90}, sf::Vector2f{36, 12}, sf::Color{50, 50, 250}));
	cars.emplace_back(std::make_unique<SimpleAiCar>(sf::Vector2f{200, 110}, sf::Vector2f{36, 12}, sf::Color{50, 50, 250}));
}

void PlayState::init() {

}

float PlayState::calculateDistance(const sf::Vector2f& pointA, const sf::Vector2f& pointB) const {
	return sqrt(pow(pointA.x - pointB.x, 2) + pow(pointA.y - pointB.y, 2));
}

PlayState::Overlab PlayState::overlaps(const sf::Vector2f& pointA, const sf::Vector2f& pointB, const sf::Vector2f& pointC, const sf::Vector2f& pointD) const {
	float uA = ((pointD.x - pointC.x) * (pointA.y - pointC.y) - (pointD.y - pointC.y) * (pointA.x - pointC.x)) /
		((pointD.y - pointC.y) * (pointB.x - pointA.x) - (pointD.x - pointC.x) * (pointB.y - pointA.y));
	float uB = ((pointB.x - pointA.x) * (pointA.y - pointC.y) - (pointB.y - pointA.y) * (pointA.x - pointC.x)) /
		((pointD.y - pointC.y) * (pointB.x - pointA.x) - (pointD.x - pointC.x) * (pointB.y - pointA.y));

	return {
		uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1,
		sf::Vector2f{
			pointA.x + (uA * (pointB.x - pointA.x)),
			pointA.y + (uA * (pointB.y - pointA.y))
		}
	};
}

bool PlayState::overlaps(const sf::RectangleShape& shape, const sf::Vector2f& pointC, const sf::Vector2f& pointD) const {
	// Rotation of the rectangle;
	const auto topLeft = shape.getTransform().transformPoint(sf::Vector2f{0, 0});
	const auto topRight = shape.getTransform().transformPoint(sf::Vector2f{shape.getSize().x, 0});
	const auto bottomLeft = shape.getTransform().transformPoint(sf::Vector2f{0, shape.getSize().y});
	const auto bottomRight = shape.getTransform().transformPoint(sf::Vector2f{shape.getSize().x, shape.getSize().y});

	return (
		overlaps(topLeft, bottomLeft, pointC, pointD).overlab || // Left
		overlaps(topRight, bottomRight, pointC, pointD).overlab || // Right
		overlaps(topLeft, topRight, pointC, pointD).overlab || // Top
		overlaps(bottomLeft, bottomRight, pointC, pointD).overlab    // Bottom
	);
}

void PlayState::update() {
	size_t carIndex = 0;
	for (auto& car : cars) {
		// AI move
		car->calculateMove();
		// Update car position
		car->update(window);

		// Keyboard controlls
		car->forwardPressed = wKeyDown;
		car->backwardPressed = sKeyDown;
		car->leftPressed = aKeyDown;
		car->rightPressed = dKeyDown;

		// Check for collision with finish line and up score when crossed
		const auto finish = track.getFinishLine();
		bool onFinishLine = overlaps(car->getShape(), finish[0].position, finish[1].position);
		if (onFinishLine && !car->onFinishLine) { // Prevent multiple score if car stays on finish line
			car->onFinishLine = true;
			car->score += 1;
		} else {
			car->onFinishLine = onFinishLine;
		}
		std::cout << carIndex << ": " << car->score << std::endl; // TODO: Write on screen

		bool hit = false;
		const auto& vertices = track.getVertices();
		for (size_t i = 0; i < vertices.getVertexCount(); ++i) { // We can't use ranged based for loops on sf::vertexArray
			if (i == vertices.getVertexCount() - 1) { // Skip last one
				break;
			}

			const auto& vertex = vertices[i];
			const auto& nextVertex = vertices[i + 1];

			if (vertex.position == finish[0].position && nextVertex.position == finish[1].position) { // Skip finish
				continue;
			}

			if (overlaps(car->getShape(), vertex.position, nextVertex.position)) {
				hit = true;
			}
		}
		car->hit = hit;


		// Calculate distance to road for each vision line
		const auto& lines = car->getVisionLines();
		size_t lineIndex = 0;
		for (const auto& line : lines) {
			float smallestDistance = car->visionRange;

			// Check if a vision line overlabs with track line
			for (size_t i = 0; i < vertices.getVertexCount(); ++i) { // We can't use ranged based for loops on sf::vertexArray
				if (i == vertices.getVertexCount() - 1) { // Skip last one
					break;
				}

				const auto& vertex = vertices[i];
				const auto& nextVertex = vertices[i + 1];

				// Skip finish line
				if (vertex.position == finish[0].position && nextVertex.position == finish[1].position) {
					continue;
				}

				// Check if there is overlab between vision line and track line and then calculate the distance
				const auto overlab = overlaps(line.first, line.second, vertex.position, nextVertex.position);
				if (overlab.overlab) {
					float distance = calculateDistance(car->getPosition(), overlab.position);
					// Prevent overwriting the distance when a vision line sees more than one track line
					smallestDistance = std::min(smallestDistance, distance);
				}
			}

			// Set distance for vision line (used for AI)
			car->setDistanceToObstacle(lineIndex, smallestDistance);

			++lineIndex;
		}

		++carIndex;
	}
}

void PlayState::render() const {
	window.draw(track.getVertices());

	for (const auto& car : cars) {
		window.draw(car->getShape());

		if (debug) {
			const auto& vertices = track.getVertices();
			const auto finish = track.getFinishLine();
			const auto& lines = car->getVisionLines();
			for (const auto& line : lines) {
				const sf::Vertex lineVertices[2] = {line.first, line.second};
				// Render vision lines
				window.draw(lineVertices, 2, sf::LineStrip);

				// Check if a vision line overlabs with track line
				for (size_t i = 0; i < vertices.getVertexCount(); ++i) { // We can't use ranged based for loops on sf::vertexArray
					if (i == vertices.getVertexCount() - 1) { // Skip last one
						break;
					}

					const auto& vertex = vertices[i];
					const auto& nextVertex = vertices[i + 1];

					// Skip finish
					if (vertex.position == finish[0].position && nextVertex.position == finish[1].position) {
						continue;
					}

					// Draw circle if overlab
					const auto overlab = overlaps(line.first, line.second, vertex.position, nextVertex.position);
					if (overlab.overlab) {
						auto circle = sf::CircleShape(5.0f);
						circle.setPosition(overlab.position);
						circle.setFillColor(car->getShape().getFillColor());
						circle.setOrigin({5.0f, 5.0f});
						window.draw(circle);
					}
				}
			}
		} // End debug
	} // End cars
}

void PlayState::cleanUp() {

}


void PlayState::onKeyPressed(sf::Event& evt) {
	switch (evt.key.code) {
	case sf::Keyboard::W:
		wKeyDown = true;
		break;
	case sf::Keyboard::A:
		aKeyDown = true;
		break;
	case sf::Keyboard::Space:
	case sf::Keyboard::S:
		sKeyDown = true;
		break;
	case sf::Keyboard::D:
		dKeyDown = true;
		break;
	default:
		break;
	}
}

void PlayState::onKeyReleased(sf::Event& evt) {
	switch (evt.key.code) {
	case sf::Keyboard::W:
		wKeyDown = false;
		break;
	case sf::Keyboard::A:
		aKeyDown = false;
		break;
	case sf::Keyboard::Space:
	case sf::Keyboard::S:
		sKeyDown = false;
		break;
	case sf::Keyboard::D:
		dKeyDown = false;
		break;
	default:
		break;
	}

}