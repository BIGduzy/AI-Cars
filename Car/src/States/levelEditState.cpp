#include "levelEditState.h"

LevelEditState::LevelEditState(sf::RenderWindow& window):
	State(window) {

	innerTrack.setPrimitiveType(sf::LineStrip);
	outerTrack.setPrimitiveType(sf::LineStrip);
}

void LevelEditState::init() {
}


float LevelEditState::calculateDistance(const sf::Vector2f& pointA, const sf::Vector2f& pointB) const {
	return sqrt(pow(pointA.x - pointB.x, 2) + pow(pointA.y - pointB.y, 2));
}

LevelEditState::Overlab LevelEditState::overlaps(const sf::Vector2f& pointA, const sf::Vector2f& pointB, const sf::Vector2f& pointC, const sf::Vector2f& pointD) const {
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

LevelEditState::Overlab LevelEditState::overlaps(const sf::RectangleShape& shape, const sf::Vector2f& pointC, const sf::Vector2f& pointD) const {
	// Rotation of the rectangle;
	const auto topLeft = shape.getTransform().transformPoint(sf::Vector2f{0, 0});
	const auto topRight = shape.getTransform().transformPoint(sf::Vector2f{shape.getSize().x, 0});
	const auto bottomLeft = shape.getTransform().transformPoint(sf::Vector2f{0, shape.getSize().y});
	const auto bottomRight = shape.getTransform().transformPoint(sf::Vector2f{shape.getSize().x, shape.getSize().y});

	return {(
		overlaps(topLeft, bottomLeft, pointC, pointD).overlab || // Left
		overlaps(topRight, bottomRight, pointC, pointD).overlab || // Right
		overlaps(topLeft, topRight, pointC, pointD).overlab || // Top
		overlaps(bottomLeft, bottomRight, pointC, pointD).overlab    // Bottom
		),
		overlaps(topRight, bottomRight, pointC, pointD).position // TOOD: Calculate once and use center of car
	};
}

void LevelEditState::update() {
	if (track == nullptr) return;

	// TODO: See PlayState::update
	for (auto& car : cars) {
		// AI move
		car->calculateMove();
		// Update car position
		car->update(window);

		// Check for collision with finish line and up score when crossed
		const auto finish = track->getFinishLine();
		bool onFinishLine = overlaps(car->getShape(), finish[0].position, finish[1].position).overlab;
		if (onFinishLine && !car->onFinishLine) { // Prevent multiple score if car stays on finish line
			car->onFinishLine = true;
			car->score += 1;
			//car->rotation += 3.1415926535f; // TODO: This is only for training
		} else {
			car->onFinishLine = onFinishLine;
		}

		bool hit = false;
		const auto& objects = track->getObjects();
		for (const auto& object : objects) {
			for (size_t i = 0; i < object.getVertexCount(); ++i) { // We can't use ranged based for loops on sf::vertexArray
				if (i == object.getVertexCount() - 1) { // Skip last one
					break;
				}

				const auto& vertex = object[i];
				const auto& nextVertex = object[i + 1];
				if (vertex.position == finish[0].position && nextVertex.position == finish[1].position) { // Skip finish
					continue;
				}

				if (overlaps(car->getShape(), vertex.position, nextVertex.position).overlab) {
					hit = true;
				}
			}
		}
		car->hit = hit;

		// Calculate distance to road for each vision line
		const auto& lines = car->getVisionLines();
		size_t lineIndex = 0;
		for (const auto& line : lines) {
			float smallestDistance = car->visionRange;
			for (const auto& object : objects) {

				// Check if a vision line overlabs with track line
				for (size_t i = 0; i < object.getVertexCount(); ++i) { // We can't use ranged based for loops on sf::vertexArray
					if (i == object.getVertexCount() - 1) { // Skip last one
						break;
					}

					const auto& vertex = object[i];
					const auto& nextVertex = object[i + 1];

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

				for (const auto& otherCar : cars) {
					if (otherCar == car) { continue; } // Skip same car

					const auto overlab = overlaps(otherCar->getShape(), line.first, line.second);
					if (overlab.overlab) {
						float distance = calculateDistance(car->getPosition(), overlab.position);
						// Prevent overwriting the distance when a vision line sees more than one track line
						smallestDistance = std::min(smallestDistance, distance); // TODO: Before we do this we need an AI that can drive d;)
					}
				}
			}

			// Set distance for vision line (used for AI)
			car->setDistanceToObstacle(lineIndex, smallestDistance);

			++lineIndex;
		}
	}
}

void LevelEditState::render() const {
	if (track != nullptr) {
		const auto& objects = track->getObjects();
		for (const auto& object : objects) {
			window.draw(object);
		}
		
		const auto& finish = track->getFinishLine();
		auto line = sf::VertexArray(sf::LineStrip, 2);
		line.append(sf::Vertex{finish[0]});
		line.append(sf::Vertex{finish[1]});
		window.draw(line);
	} else {
		window.draw(innerTrack);
		window.draw(outerTrack);

		const auto& mousePosI = sf::Mouse::getPosition(window);

		sf::Vector2f mousePos(static_cast<float>(mousePosI.x), static_cast<float>(mousePosI.y));

		if (selectedTrack->getVertexCount()) {
			auto tmp = sf::VertexArray(sf::LineStrip, 2);
			sf::Vertex start = selectedTrack->operator[](selectedTrack->getVertexCount() - 1);
			tmp.append(start);
			tmp.append(sf::Vertex{mousePos, {0, 225, 0}});
			window.draw(tmp);
		}
	}


	for (const auto& car : cars) {
		window.draw(car->getShape());

		if (track != nullptr) {
			if (false) {
				const auto& objects = track->getObjects();
				const auto finish = track->getFinishLine();
				const auto& lines = car->getVisionLines();
				for (const auto& line : lines) {
					const sf::Vertex lineVertices[2] = {line.first, line.second};
					// Render vision lines
					window.draw(lineVertices, 2, sf::LineStrip);

					// Check if a vision line overlabs with track line
					for (const auto& object : objects) {
						for (size_t i = 0; i < object.getVertexCount(); ++i) { // We can't use ranged based for loops on sf::vertexArray
							if (i == object.getVertexCount() - 1) { // Skip last one
								break;
							}

							const auto& vertex = object[i];
							const auto& nextVertex = object[i + 1];

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
				}
			}
		}
	} // End cars
}

void LevelEditState::cleanUp() {

}


void LevelEditState::onKeyPressed(sf::Event& evt) {
	switch (evt.key.code) {
	case sf::Keyboard::W:
		break;
	case sf::Keyboard::A:
		break;
	case sf::Keyboard::Space:
	case sf::Keyboard::S:
		break;
	case sf::Keyboard::D:
		break;
	default:
		break;
	}
}

void LevelEditState::onKeyReleased(sf::Event& evt) {
	switch (evt.key.code) {
	case sf::Keyboard::W:
		break;
	case sf::Keyboard::A:
		break;
	case sf::Keyboard::Space:
	case sf::Keyboard::S:

		break;
	case sf::Keyboard::D:
		break;
	default:
		break;
	}
}

void LevelEditState::onMouseButtonPressed(sf::Event& evt) {
		sf::Vector2f mousePos(static_cast<float>(evt.mouseButton.x), static_cast<float>(evt.mouseButton.y));
	if (evt.mouseButton.button == sf::Mouse::Left) {
		selectedTrack->append(sf::Vertex{mousePos, sf::Color{0, 0, 0}});
	} else if (evt.mouseButton.button == sf::Mouse::Right) {
		selectedTrack->append(selectedTrack->operator[](0)); // TODO: Hmmmmmmmmmmm

		if (selectedTrack == &outerTrack) {
			selectedTrack = &innerTrack;
		} else if (selectedTrack == &innerTrack) {
			selectedTrack = &outerTrack;
			cars.emplace_back(std::make_unique<NeuronCar>(mousePos, sf::Vector2f{36, 12}, sf::Color{50, 200, 50}));

			track = std::make_unique<Track>(innerTrack, outerTrack);
		}

	}
}