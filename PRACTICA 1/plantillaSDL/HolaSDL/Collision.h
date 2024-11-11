#pragma once
#include "checkML.h"
#include <SDL.h>

struct Collision 
{
    bool collides = false;
    bool damages = false;

    SDL_Rect intersection;       // rectangulo de interseccion de la colision
    void* collider = nullptr;    // puntero al objeto con el que se colisiona

    operator bool() const { return collides; }
};
