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

void Tilemap::renderTilemap()
{

	constexpr int TILE_SIDE = 32;  // constantes est�ticas en Game
	constexpr int WINDOW_WIDTH = 18;
	constexpr int WINDOW_HEIGHT = 16;

	int offset = game->getMapOffset();  // atributo de Game

	// Primera columna de la matriz del mapa visible en la ventana
	int x0 = offset / TILE_SIDE;
	// Anchura oculta de esa primera columna
	int d0 = offset % TILE_SIDE;

	// Recuadro donde se pintar� la tesela en la ventana
	SDL_Rect rect;
	rect.w = TILE_SIDE;
	rect.h = TILE_SIDE;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int i = 0; i < WINDOW_WIDTH + 1; ++i) {
		for (int j = 0; j < WINDOW_HEIGHT; ++j) {
			// �ndice en el conjunto de patrones de la matriz de �ndices
			int indice = indices[x0 + i][j];

			// Separa n�mero de fila y de columna
			int fx = indice % 9;
			int fy = indice / 9;

			rect.x = -d0 + i * TILE_SIDE;
			rect.y = j * TILE_SIDE;

			// Usa renderFrame para pintar la tesela
			background->renderFrame(rect, fx, fy);
		}
	}
}

void Tilemap::render()
{

	renderTilemap();
	
}
