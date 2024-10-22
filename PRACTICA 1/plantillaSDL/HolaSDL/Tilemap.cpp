#include "Tilemap.h"

// Velocidad y frecuencia de cambio de frame
constexpr int SPEED = 10;
constexpr int FRAME_PERIOD = 20;

Tilemap::Tilemap(Game* g,  vector<vector<int>> ind)
{
	indices = ind;
	game = g;
	background = game->getTexture(Game::BACKGROUND);

}

void Tilemap::render()
{



	int offset = game->getMapOffset();

	for (int i = 0; i < 16; i++) {

		for (int j = 0; j < 18; j++)
		{
			if (indices[i][j] == -1) {
				SDL_Rect 
				//?¿¿?¿?¿? del dogggg
				SDL_Rect destino{ x, y, texture->getFrameWidth(), texture->getFrameHeight() };
				background->renderFrame(destino, 0, (abs(x) / FRAME_PERIOD) % background->getNumColumns());
			}
		}
	}

	
}
