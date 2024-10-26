#include "Tilemap.h"

// Velocidad y frecuencia de cambio de frame
constexpr int SPEED = 10;
constexpr int FRAME_PERIOD = 20;


Tilemap::Tilemap()
{
}

Tilemap::Tilemap(Game* g, string f)
{
	loadTilemap(f);
	game = g;
	background = game->getTexture(Game::BACKGROUND);
}

Tilemap::~Tilemap()
{
	delete texture;
	delete background;
	delete game;
}

void Tilemap::loadTilemap(string fichero)
{
	ifstream f;
	f.open(fichero);
	if (!f.is_open()) {
		throw string("fichero de mapa no encontrado");
	}
	else {
		string linea;
		vector<vector<int>> matriz;

		while (getline(f, linea)) {
			istringstream stream(linea);
			string valor;
			vector<int> fila;


			// Leer cada valor separado por coma
			while (getline(stream, valor, ',')) {
				istringstream convertir(valor); // Crear un istringstream para la conversión
				int num;
				convertir >> num; // Convertir el string a int

				fila.push_back(num); // Agregar el número a la fila
			}

			indices.push_back(fila); // Agregar la fila a la matriz

		}

		//for (const auto& row : indices) {
		//	for (const auto& value : row) {
		//		std::cout << value << " ";
		//	}
		//	std::cout << std::endl;
		//}
	}

	f.close();
}

void Tilemap::renderTilemap()
{
	int offset = game->getMapOffset();  // atributo de Game

	// Primera columna de la matriz del mapa visible en la ventana
	int x0 = offset / TILE_SIDE;
	// Anchura oculta de esa primera columna
	int d0 = offset % TILE_SIDE;

	// Recuadro donde se pintará la tesela en la ventana
	SDL_Rect rect;
	rect.w = TILE_SIDE;
	rect.h = TILE_SIDE;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int i = 0; i < WINDOW_WIDTH + 1; ++i) {
		for (int j = 0; j < WINDOW_HEIGHT; ++j) {

			if (x0 + i < indices.size() && j < indices[0].size()) {
				// Índice en el conjunto de patrones de la matriz de índices
				int indice = indices[x0 + i][j];

				// Separa número de fila y de columna
				int fx = indice / 9;
				int fy = indice % 9;

				rect.y = i * TILE_SIDE;
				rect.x = j * TILE_SIDE - d0; // raro


				// Usa renderFrame para pintar la tesela
				background->renderFrame(rect, fx, fy);
			}
		}
	}
}

void Tilemap::render()
{

	renderTilemap();
	
}

void Tilemap::update()
{

	renderTilemap();
}
