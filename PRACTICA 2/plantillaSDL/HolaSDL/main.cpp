#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

#include "Game.h"

using namespace std;

int main(int argc, char* argv[])
{
    try {
        Game game;
        game.run();
    }
    catch (const FileNotFoundError& fileError)
    {
        cerr << "File not found: " << fileError.what() << endl;
    }
    catch (const SDLError& sdlError)
    {
        cerr << "SDL error: " << sdlError.what() << endl;
    }
    catch (const FileFormatError& formatError)
    {
        cerr << "File format error: " << formatError.what() << endl;
    }
    catch (const exception& e)
    {
        cerr << "Exception: " << e.what() << endl;
    }
    catch (const std::string& error)
    {
        cerr << "Unexpected exception: " << error << endl;
    }

    SDL_Quit();

    return 0;
}
