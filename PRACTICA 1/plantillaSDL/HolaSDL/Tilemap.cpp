#include "Tilemap.h"

// Velocidad y frecuencia de cambio de frame
constexpr int SPEED = 10;
constexpr int FRAME_PERIOD = 20;

Tilemap::Tilemap(Game* g,  vector<vector<int>> ind)
{
	indices = ind;
	game = g;
	texture = game->getTexture(Game::BACKGROUND);

}

void Tilemap::render()
{

	int offset = game->getMapOffset();

	for (int i = 0; i < indices.size(); i++) {

		for (int j = 0; j < indices[i].size(); j++)
		{
			if (indices[i][j] == -1) {
				//?¿¿?¿?¿? del dogggg
				SDL_Rect destino{ x, y, texture->getFrameWidth(), texture->getFrameHeight() };
				texture->renderFrame(destino, 0, (abs(x) / FRAME_PERIOD) % texture->getNumColumns());
			}
		}
	}

	
}
