#pragma once
#include "GameError.h"
#include "checkML.h"

class FileFormatError : public GameError
{
public:
    FileFormatError(const std::string& message) : GameError(message) { m = message; }
};