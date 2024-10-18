#include "Tilemap.h"

// Velocidad y frecuencia de cambio de frame
constexpr int SPEED = 10;
constexpr int FRAME_PERIOD = 20;

Tilemap::Tilemap(Game* g,  vector<string> ind)
{
	indices = ind;
	game = g;
	texture = game->getTexture(Game::BACKGROUND);


}

void Tilemap::render()
{
	for (int i = 0; i < indices.size(); i++) {

		if (indices[i] == "-1") {
			//?¿¿?¿?¿? del dog
			SDL_Rect destino{ x, y, texture->getFrameWidth(), texture->getFrameHeight() };
			texture->renderFrame(destino, 0, (abs(x) / FRAME_PERIOD) % texture->getNumColumns());
		}
	}

	
}
