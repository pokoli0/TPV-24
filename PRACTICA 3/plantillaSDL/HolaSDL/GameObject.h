#pragma once
#include "checkML.h"

#include <SDL.h>
#include <vector>

#include "Texture.h"
#include "Vector2D.h"

#include "GameList.h"

class Game;
class GameState;

class GameObject {
protected:
    Game* game; // Puntero al juego
    GameState* state; // Puntero al estado del juego

    GameList<GameObject>::anchor _anchor;


public:
    GameObject(Game* game) : game(game) {}
    GameObject(GameState* s) : state(s) {}
    GameObject(Game* g, GameState* s) : game(g), state(s) {}

    virtual ~GameObject() {};

    // Metodos virtuales puros (implementados por las clases hijas)
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void update() = 0;

    void setListAnchor(GameList<GameObject>::anchor&& anchor) {
        _anchor = std::move(anchor);
    }
};