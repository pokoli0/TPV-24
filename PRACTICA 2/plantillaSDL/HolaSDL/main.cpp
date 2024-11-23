#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

#include "Game.h"

#include "checkML.h"


using namespace std;

using uint = unsigned int;

int main(int argc, char* argv[])
{
	try {
		Game* game = new Game();
		game->run();
		delete game;
	}
	catch (FileNotFoundError& fileError)
	{
		std::cout << fileError.what() << std::endl;
	}
	catch (SDLError& SDLError)
	{
		std::cout << SDLError.what() << std::endl;
	}
	catch (FileFormatError& fileError)
	{
		std::cout << fileError.what() << std::endl;
	}
	catch (const string Error) {
		cout << "exception: " << Error;
		SDL_Quit();
	}

	return 0;
}
