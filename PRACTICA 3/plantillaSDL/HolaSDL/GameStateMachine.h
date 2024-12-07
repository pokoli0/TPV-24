/**
 * M�quina de estados con punteros inteligentes.
 *
 * @file gameStateMachine.h
 * @author Rub�n Rubio
 * @date TPV1 2024
 */

#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include <memory>
#include <stack>
#include <SDL_events.h>

#include "GameState.h"

 /**
  * M�quina de estados del juego.
  *
  * Se comporta como una pila y proporciona m�todos update, render y
  * handleEvent para aplicarlos sobre el estado actual.
  */
class GameStateMachine
{
	// Pila (como las de EDA) de punteros inteligentes a estados del juego
	std::stack<std::shared_ptr<GameState>> gameStates;

public:
	~GameStateMachine();

	// Apila un nuevo estado, que se convierte en el estado actual,
	// manteniendo el anterior en la pila
	void pushState(std::shared_ptr<GameState> state);
	// Reemplaza el estado actual por el nuevo estado
	void replaceState(std::shared_ptr<GameState> state);
	// Desapila el estado actual y pasa al siguiente en la pila
	// (no hace nada si no la pila es vac�a)
	void popState();

	// Sobrecargas que reciben un puntero normal
	void pushState(GameState* state);
	void replaceState(GameState* state);

	bool empty() const;
	operator bool() const;

	// M�todos que delegan en los m�todos hom�nimos de GameState
	// sobre el estado actual (no hacen nada si la pila es vac�a)
	void update();
	void render(SDL_Renderer* r) const;
	void handleEvent(const SDL_Event& event);
};

inline void
GameStateMachine::pushState(GameState* state)
{
	pushState(std::shared_ptr<GameState>(state));
}

inline void
GameStateMachine::replaceState(GameState* state)
{
	replaceState(std::shared_ptr<GameState>(state));
}

#endif // GAME_STATE_MACHINE_H