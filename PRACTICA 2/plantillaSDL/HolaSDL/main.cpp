#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

#include "Game.h"

using namespace std;

using uint = unsigned int;

int main(int argc, char* argv[])
{
	try {
		Game* game = new Game();
		game->run();
		delete game;
	}

	catch (const string Error) {
		cout << "exception: " << Error;
		SDL_Quit();

	}

	return 0;
}
