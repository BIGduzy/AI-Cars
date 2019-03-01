#include "gameStateManager.h"
#include <assert.h>

GameStateManager::GameStateManager() {};

float GameStateManager::FPS = 60.0f;

// Static member variables must be declared
std::vector<std::shared_ptr<State>> GameStateManager::states;

std::shared_ptr<State> GameStateManager::getCurrentState() {
	assert(states.size() > 0);

	return states.back();
}

void GameStateManager::popState() {
	if (states.size() > 0) {
		states.back()->cleanUp();
		states.pop_back();
	}
}

void GameStateManager::pushState(std::shared_ptr<State> state) {
	states.push_back(state);
	state->init();
}