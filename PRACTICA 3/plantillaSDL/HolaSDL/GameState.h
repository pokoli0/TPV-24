#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <list>
#include <SDL_events.h>
#include "Game.h"
#include "EventHandler.h"
#include "gameList.h"
#include "SceneObject.h"

// GameState es propietario de
// los objetos en sus listas de GameObject y debe eliminarlos al destruirse, pero no ocurre as� con PlayState
// y los objetos de la lista de SceneObject(pues es una lista redundante)

class Game;

class GameState
{

public:
	GameState(Game* g);

	virtual ~GameState() = default;

	virtual void render() const;
	virtual void update();

	virtual void handleEvent(const SDL_Event& event);


	void addEventListener(EventHandler* l);

	void addObject(GameObject* o);
	

	/// ===== Getters =====

	Game* getGame() const { return game; }

protected:

	Game* game; // referencia al game

	// lista de objetos del juego
	GameList<GameObject> stateList;

	// lista de punteros a oyentes
	std::list<EventHandler*> eventHandlers;

};

#endif