#include "GameState.h"


void GameState::handleEvent(const SDL_Event& event)
{
	for (auto handler : eventHandlers) {
		handler->handleEvent(event);
	}
}

void GameState::addEventListener(EventHandler* l)
{
	eventHandlers.push_back(l);
}

void GameState::addObject(GameObject* o)
{
	stateList.push_back(o);
}
