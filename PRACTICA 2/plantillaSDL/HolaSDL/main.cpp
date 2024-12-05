#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

#include "Game.h"

int main(int argc, char* argv[])
{
    try {
        Game game;
        game.run();
    }
    catch (const FileNotFoundError& fileError)
    {
        std::cerr << "File not found: " << fileError.what() << std::endl;
    }
    catch (const SDLError& sdlError)
    {
        std::cerr << "SDL error: " << sdlError.what() << std::endl;
    }
    catch (const FileFormatError& formatError)
    {
        std::cerr << "File format error: " << formatError.what() << std::endl;
    }
    catch (const std::string& error)
    {
        std::cerr << "Unexpected exception: " << error << std::endl;
    }

    SDL_Quit();

    return 0;
}
