#include "TileMap.h"
#include "Game.h"

void TileMap::render(SDL_Renderer* renderer) const
{
	int offset = game->getMapOffset();  // atributo de Game

	// Primera columna de la matriz del mapa visible en la ventana
	int col0 = offset / TILE_SIDE;
	// Anchura oculta de esa primera columna
	int d0 = offset % TILE_SIDE;

	SDL_Rect rect;
	// Recuadro donde se pintar� la tesela en la ventana
	rect.w = TILE_SIDE;
	rect.h = TILE_SIDE;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int col = 0; col < WINDOW_WIDTH + 1; ++col) {
		rect.x = -d0 + col * TILE_SIDE;

		for (int row = 0; row < WINDOW_HEIGHT; ++row) {
			// �ndice en el conjunto de patrones de la matriz de �ndices
			int indice = matrix[row][col0 + col];

			// Si el �ndice es -1 no se pinta nada
			if (indice != -1) {
				// Separa n�mero de fila y de columna
				int frameCol = indice % texture->getNumColumns();
				int frameRow = indice / texture->getNumColumns();

				rect.y = row * TILE_SIDE;

				// Usa renderFrame para pintar la tesela
				texture->renderFrame(rect, frameRow, frameCol);

				if (DEBUG && indice % texture->getNumColumns() < OBSTACLE_THRESHOLD)
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 128); // green
					SDL_RenderDrawRect(renderer, &rect);
					SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
				}
			}
		}
	}
}

void TileMap::update()
{
}

Collision TileMap::hit(const SDL_Rect& region, Collision::Target target)
{
	Collision colision;

	// Celda del nivel que contiene la esquina superior izquierda del rectángulo
	int row0 = rect.y / TILE_SIDE;
	int col0 = (rect.x / TILE_SIDE);

	// Celda del nivel que contiene la esquina inferior derecha del rectángulo
	int row1 = (rect.y + rect.h - 1) / TILE_SIDE;
	int col1 = ((rect.x + rect.w - 1) / TILE_SIDE);


	// ajuste para que no pete
	row0 = max(0, row0);
	row1 = min(static_cast<int>(matrix.size()) - 1, row1);
	col0 = max(0, col0);
	col1 = min(static_cast<int>(matrix[0].size()) - 1, col1);


	for (int row = row0; row <= row1; ++row)
	{
		for (int col = col0; col <= col1; ++col)
		{
			int indice = matrix[row][col];
			colision.indice = indice;


			if (indice != -1 && indice % texture->getNumColumns() < OBSTACLE_THRESHOLD)
			{
				colision.collides = true;

				SDL_Rect auxRect{
					col * TILE_SIDE,
					row * TILE_SIDE,
					TILE_SIDE,
					TILE_SIDE
				};

				// Calculamos la interseccion
				if (SDL_IntersectRect(&rect, &auxRect, &colision.intersectionRect))
				{
					return colision;
				}
			}
		}
	}

	return colision;
}
