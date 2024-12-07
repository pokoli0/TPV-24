/**
 * M�quina de estados con punteros inteligentes.
 *
 * @file gameStateMachine.cpp
 * @author Rub�n Rubio
 * @date TPV1 2024
 */

#include "GameStateMachine.h"

using namespace std;

GameStateMachine::~GameStateMachine()
{
	while (!gameStates.empty())
		gameStates.pop();
}

void
GameStateMachine::pushState(shared_ptr<GameState> state)
{
	gameStates.push(std::move(state));
}

void
GameStateMachine::popState()
{
	// Si el estado final existe y se deja eliminar
	if (!gameStates.empty())
		gameStates.pop();
}

bool
GameStateMachine::empty() const
{
	return gameStates.empty();
}

GameStateMachine::operator bool() const
{
	return !gameStates.empty();
}

void
GameStateMachine::replaceState(shared_ptr<GameState> state)
{
	if (!gameStates.empty())
		gameStates.top() = std::move(state);
}

void
GameStateMachine::update()
{
	if (!gameStates.empty()) {
		// Esta variable local evita que el estado sea destruido hasta que
		// acabe esta funci�n si su actualizaci�n lo desapila de esta pila
		shared_ptr<GameState> current = gameStates.top();
		current->update();
	}
}

void
GameStateMachine::render(SDL_Renderer* r) const
{
	if (!gameStates.empty()) {
		// Asumimos que render (const) no desapilar� y destruir� el estado
		gameStates.top()->render(r);
	}
}

void
GameStateMachine::handleEvent(const SDL_Event& event)
{
	if (!gameStates.empty()) {
		shared_ptr<GameState> current = gameStates.top();
		current->handleEvent(event);
	}
}
