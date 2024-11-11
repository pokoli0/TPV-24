#pragma once
#include "checkML.h"
#include <SDL.h>

struct Collision 
{
    bool collides = false;
    bool damages = false;

    SDL_Rect rect;

    operator bool() const { return collides; }
};
