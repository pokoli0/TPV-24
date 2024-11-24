#include "TileMap.h"
#include "Game.h"

TileMap::TileMap(Game* game, const string& mapFile, int x, int y)
	: SceneObject(game, x, y, TILE_SIDE, TILE_SIDE, game->getTexture(Game::BACKGROUND))
{
	loadTilemap(mapFile);
}

void TileMap::loadTilemap(string fichero)
{
	ifstream f;
	f.open(fichero);
	if (!f.is_open()) {
		throw string("fichero de mapa worldX.csv no encontrado");
	}
	else {
		string linea;
		vector<vector<int>> matriz;

		while (getline(f, linea)) // lee linea del fichero f y lo guarda en string linea 
		{
			istringstream stream(linea); // para procesar la linea
			string valor; // almacena temporalmente el valor extraido de la linea 

			vector<int> fila; // para almacenar nums de la fila

			// Leer cada valor separado por coma
			while (getline(stream, valor, ',')) // lee cada valor de la linea (stream), separando los valores por comas
			{
				istringstream convertir(valor); // istringstream para la conversion de string a int

				int num;
				convertir >> num; // guardamos el int convertido en num

				fila.push_back(num); // pushback del numero a la fila
			}

			matrix.push_back(fila); // Agregar la fila a la matriz
		}

		//para comprobar que se ha guardado bien: 
		//for (const auto& row : indices) {
		//	for (const auto& value : row) {
		//		std::cout << value << " ";
		//	}
		//	std::cout << std::endl;
		//}
	}

	f.close();
}


void TileMap::render(SDL_Renderer* renderer)
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
				int frameCol = indice % _texture->getNumColumns();
				int frameRow = indice / _texture->getNumColumns();

				rect.y = row * TILE_SIDE;

				// Usa renderFrame para pintar la tesela
				_texture->renderFrame(rect, frameRow, frameCol);

				if (DEBUG && indice % _texture->getNumColumns() < OBSTACLE_THRESHOLD)
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
	//game->checkCollision(rect, false);
}

Collision TileMap::hit(const SDL_Rect& region, Collision::Target target)
{
	Collision colision;

	// Celda del nivel que contiene la esquina superior izquierda del rectángulo
	int row0 = region.y / TILE_SIDE;
	int col0 = (region.x / TILE_SIDE);

	// Celda del nivel que contiene la esquina inferior derecha del rectángulo
	int row1 = (region.y + region.h - 1) / TILE_SIDE;
	int col1 = ((region.x + region.w - 1) / TILE_SIDE);


	//ajuste para que no pete
	row0 = max(0, row0);
	row1 = min(static_cast<int>(matrix.size()) - 1, row1);
	col0 = max(0, col0);
	col1 = min(static_cast<int>(matrix[0].size()) - 1, col1);


	for (int row = row0; row <= row1; ++row)
	{
		for (int col = col0; col <= col1; ++col)
		{
			int indice = matrix[row][col];

			if (indice != -1 && indice % _texture->getNumColumns() < OBSTACLE_THRESHOLD)
			{

				//cout << "col";
				SDL_Rect auxRect{
					col * TILE_SIDE,
					row * TILE_SIDE,
					TILE_SIDE,
					TILE_SIDE
				};

				// Calculamos la interseccion
				if (SDL_IntersectRect(&region, &auxRect, &colision.intersectionRect))
				{
					colision.result = Collision::OBSTACLE; // el resultado sera obstacle porque el tilemap no hace damage
					colision.horizontal = colision.intersectionRect.w;
					colision.vertical = colision.intersectionRect.h;
					return colision;
				}
			}
		}
	}

	return colision;
}

SceneObject* TileMap::clone() const
{
	return nullptr;
}

