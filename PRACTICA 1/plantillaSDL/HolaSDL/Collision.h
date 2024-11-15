#pragma once
#include "checkML.h"
#include <SDL.h>

struct Collision 
{
    bool collides = false;
    bool damages = false;

    SDL_Rect intersectionRect;

    int indice = 0;

    operator bool() const { return collides; }
};
