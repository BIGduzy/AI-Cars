#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "GSM/gameStateManager.h"
#include "States/playState.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Game State Manager");
	window.setJoystickThreshold(0.7f);
	sf::Event evt;

	// The game starts in the MenuState
	GameStateManager::pushState(std::make_shared<PlayState>(window));

	int update_counter = 0;
	int render_counter = 0;
	sf::Clock update_clock;
	sf::Clock stats_clock;
	sf::Time delta_time; // time between last update and current update call

	while (window.isOpen()) {
		while (window.pollEvent(evt)) {
			switch (evt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				GameStateManager::getCurrentState()->onKeyPressed(evt);
				break;
			case sf::Event::KeyReleased:
				GameStateManager::getCurrentState()->onKeyReleased(evt);
				break;
			case sf::Event::MouseButtonPressed:
				GameStateManager::getCurrentState()->onMouseButtonPressed(evt);
				break;
			case sf::Event::MouseButtonReleased:
				GameStateManager::getCurrentState()->onMouseButtonReleased(evt);
				break;
			case sf::Event::MouseMoved:
				GameStateManager::getCurrentState()->onMouseMoved(evt);
				break;
			case sf::Event::JoystickButtonPressed:
				GameStateManager::getCurrentState()->onJoystickButtonPressed(evt);
				break;
			case sf::Event::JoystickMoved:
				GameStateManager::getCurrentState()->onJoystickMoved(evt);
				break;
			case sf::Event::JoystickConnected:
				GameStateManager::getCurrentState()->onJoystickConnected(evt);
				break;
			case sf::Event::JoystickDisconnected:
				GameStateManager::getCurrentState()->onJoystickDisconnected(evt);
				break;
			}
		}

		/**********/
		/**UPDATE**/
		/**********/
		const sf::Time time_per_update = sf::seconds(1.f / GameStateManager::FPS);
		sf::Time elapsedTime = update_clock.restart();
		delta_time += elapsedTime;
		while (delta_time >= time_per_update) {
			delta_time -= time_per_update;
			update_counter++;
			// Update the active state
			GameStateManager::getCurrentState()->update();
		}

		/**********/
		/**RENDER**/
		/**********/
		if (GameStateManager::FPS <= 240) { // TODO: Remove thiss
			window.clear(sf::Color(200, 200, 200));
			// Draw the active state
			GameStateManager::getCurrentState()->render();
			window.display();
			render_counter++;

			sf::sleep(sf::milliseconds(10)); // call this when you want to limit your fps
		}


		//update fps and ups
		if (stats_clock.getElapsedTime() > sf::seconds(1)) {
			stats_clock.restart();
			std::string temp = "ups = " + std::to_string(update_counter) + " fps = " + std::to_string(render_counter);
			window.setTitle(temp);
			update_counter = 0;
			render_counter = 0;
		}

	}

	return 0;
}