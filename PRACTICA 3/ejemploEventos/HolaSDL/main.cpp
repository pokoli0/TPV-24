#include "checkML.h"

#include "game.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	try {
		Game game;
		game.run();
	}
	catch (const std::string& msg) {
		cout << "Error: " << msg << endl;
	}

	return 0;
}
