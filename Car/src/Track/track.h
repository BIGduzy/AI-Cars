#pragma once

#include <SFML\Graphics.hpp>

#include <vector>
#include <array>

class Track {
private:
	// sf::VertexArray objects;  // TODO: We could use vertex
	std::vector<sf::VertexArray> objects;
public:
	Track(const sf::VertexArray& innerTrack, const sf::VertexArray& outerTrack);

	inline const std::array<sf::Vertex, 2> getFinishLine() const { return {objects[0][0], objects[1][0]}; }; // TODO: Create custorm fishishes
	//inline const std::array<sf::Vertex, 2> getFinishLine() const { return {objects[123], objects[124]}; }; // TODO: Let's not hardcode this
	//inline const std::array<sf::Vertex, 2> getFinishLine() const { return {objects[9], objects[10]}; };
	inline const std::vector<sf::VertexArray>& getObjects() const { return objects; }
};