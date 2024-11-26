#pragma once
#include "checkML.h"

#include <SDL.h>
#include <vector>

#include "Texture.h"
#include "Vector2D.h"

class Game;

class GameObject {
protected:
    Game* game; // Puntero al juego

public:
    GameObject(Game* game) : game(game) {}
    virtual ~GameObject() {}

    // Metodos virtuales puros (implementados por las clases hijas)
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void update() = 0;
};