#pragma once

#include <SFML\Graphics.hpp>

#include <vector>
#include <array>

class Track {
private:
	sf::VertexArray vertices;  // TODO: We could use vertex
public:
	Track();

	inline const std::array<sf::Vertex, 2> getFinishLine() const { return {vertices[9], vertices[10]}; }; // TODO: Let's not hardcode this
	inline const sf::VertexArray& getVertices() const { return vertices; }
};