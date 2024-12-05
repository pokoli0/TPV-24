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
    catch (GameError& e)
    {
        cout << e.what() << endl;
    }
    catch (const exception& e)
    {
        cerr << "Exception: " << e.what() << endl;
    }
    catch (const std::string& error)
    {
        cerr << "Unexpected exception: " << error << endl;
    }
    catch (...)
    {
        cout << "An error occurred." << endl;
    }

    return 0;
}
