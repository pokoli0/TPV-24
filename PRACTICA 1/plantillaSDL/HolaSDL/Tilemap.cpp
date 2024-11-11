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

	cout << "Tilemap" << endl;
}

Tilemap::~Tilemap()
{
	delete texture;
	delete background;
}

void Tilemap::loadTilemap(string fichero)
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

			indices.push_back(fila); // Agregar la fila a la matriz
		}

		// para comprobar que se ha guardado bien: 
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

	// Recuadro donde se pintar� la tesela en la ventana
	rect.w = TILE_SIDE;
	rect.h = TILE_SIDE;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int i = 0; i < WINDOW_WIDTH + 1; ++i) 
	{
		for (int j = 0; j < WINDOW_HEIGHT; ++j) 
		{
			// �ndice en el conjunto de patrones de la matriz de �ndices
			int indice = indices[j][x0 + i];

			// Si el �ndice es -1 no se pinta nada
			if (indice != -1) {
				// Separa n�mero de fila y de columna
				int fx = indice / 9;								// !!!!! esto estaba al reves (/ por %)
				int fy = indice % 9;								// !!!!! esto estaba al reves (/ por %)

				rect.x = -d0 + i * TILE_SIDE;
				rect.y = j * TILE_SIDE;

				// Usa renderFrame para pintar la tesela
				background->renderFrame(rect, fx, fy);				// !!!!! esto estaba al reves (fx por fy)
			}
		}
	}
}

void Tilemap::render()
{
	renderTilemap();
}

Collision Tilemap::hit(const SDL_Rect& rect, bool fromPlayer)
{

	// DE RUBEN: DUDA IMPLEMENTACION DE COLISIONES


	Collision collision; // Inicializa una instancia de Collision

	// Calcula las celdas del nivel que contienen las esquinas del rect�ngulo
	int row0 = rect.y / TILE_SIDE;
	int col0 = rect.x / TILE_SIDE;
	int row1 = (rect.y + rect.h - 1) / TILE_SIDE;
	int col1 = (rect.x + rect.w - 1) / TILE_SIDE;

	for (int row = row0; row <= row1; ++row) {
		for (int col = col0; col <= col1; ++col) {
			int index = indices[row][col];

			// Verifica si hay colisi�n con un obst�culo
			if (index != -1 && index % texture->getNumColumns() < OBSTACLE_THRESHOLD) {
				collision.collides = true;

				// Calcula la intersecci�n entre rect y el tile en cuesti�n
				SDL_Rect tileRect = { col * TILE_SIDE, row * TILE_SIDE, TILE_SIDE, TILE_SIDE };
				SDL_IntersectRect(&rect, &tileRect, &collision.intersection);

				// Aqu� puedes asignar el puntero `collider` y establecer `damages` si aplica
				collision.collider = nullptr; // Ajusta esto seg�n tu implementaci�n
				collision.damages = fromPlayer; // Ejemplo: tal vez solo da�a si es el jugador

				return collision;
			}
		}
	}

	return collision; // Retorna la instancia sin colisi�n si no encontr� obst�culos
}

void Tilemap::update()
{
	renderTilemap();

	//game->checkCollision(rect, true);
}
