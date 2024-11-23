#pragma once
#include "checkML.h"

#include "GameError.h"

class SDLError : public GameError
{
public:
    SDLError(const std::string& message) : GameError(message) { m = message; }
};