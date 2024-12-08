#include "PlayState.h"
#include <iostream>

PlayState::PlayState(Game* g, int l)
	: GameState(g)
{
	cout << "Play State " << l << endl;

	mapOffset = 0;
	//mapOffset = 5880; // para probar cambio de nivel

	level = l;
	lastLevel = 2; // nuestro juego tiene 2 niveles

	gameWon = false;

	nextObject = 0;

	loadLevel(level);
}

void PlayState::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);

	for (auto obj : stateList) obj->render(renderer);
}

void PlayState::update()
{
	// Borde derecho del mapa (+ una casilla)
	const int rightThreshold = mapOffset + Game::WIN_WIDTH + TILE_SIDE;

	while (nextObject < objectQueue.size() && objectQueue[nextObject]->getXPos() < rightThreshold)
	{
		addObject(objectQueue[nextObject++]->clone()); // se hace a partir del 2
	}

	for (auto obj : stateList) obj->update();
	//for (auto obj : sceneObjects) obj->update();
}

void PlayState::loadLevel(int l)
{
	string root = "../assets/maps/world" + to_string(l) + ".csv";

	/// ===== CREACION DEL TILEMAP =====
	tilemap = new TileMap(game, this, root);
	addObject(tilemap);

	loadObjectMap("../assets/maps/world" + to_string(l) + ".txt");
}

void PlayState::loadObjectMap(const string& mapFile)
{
	ifstream file(mapFile);

	if (!file.is_open()) {
		throw string("fichero de mapa worldX.txt no encontrado");
	}

	string line;

	getline(file, line); // lectura primera linea

	// Usamos un stringstream para leer la linea como si fuera un flujo
	stringstream lineStream(line);

	lineStream >> r >> g >> b;

	while (getline(file, line))
	{
		stringstream lineStream(line);

		char tipo, atrib, accion;
		double x, y, sp;

		lineStream >> tipo >> x >> y;

		if (tipo == 'B') lineStream >> atrib >> accion;
		if (tipo == 'L') lineStream >> sp;

		// conversion
		x = x * TILE_SIDE;
		y = y * TILE_SIDE;

		SceneObject* obj;

		switch (tipo) {
		case 'M':
			/// ===== CREACION DE MARIO =====
			if (player == nullptr) 
			{
				player = new Player(game, this, x, y);
				//player = new Player(game, this, 6166, 448); // para probar bandera

				addObject(player);

				addEventListener(player); // se encarga del input
			}
			else
			{
				// reposicionar en el siguiente nivel
				player->setInitPos(x, y);
				player->resetPlayer();
			}
			break;
		case 'B':
			obj = new Block(game, this, x, y, atrib, accion);
			break;
		case 'G':
			obj = new Goomba(game, this, x, y);
			break;
		case 'K':
			obj = new Koopa(game, this, x, y);
			break;
		case 'L':
			obj = new Lift(game, this, x, y, sp);
			break;
		case 'C':
			obj = new Coin(game, this, x, y);
			break;
		}

		if (tipo != 'M') {
			objectQueue.push_back(obj);
		}
	}

	file.close();
}

void PlayState::addObject(SceneObject* o)
{
	sceneObjects.push_back(o);
	stateList.push_back(o);
}

void PlayState::resetLevel()
{
	for (auto obj : sceneObjects)
	{
		if (obj != player)
		{
			delete obj;
		}
	}

	objectQueue.clear();
	nextObject = 0;
	mapOffset = 0;

	// recarga nivel
	loadLevel(level);
}

Collision PlayState::checkCollision(const SDL_Rect& rect, Collision::Target target)
{
	Collision collision;

	for (SceneObject* obj : sceneObjects)
	{
		collision = obj->hit(rect, target);

		if (collision.result != Collision::NONE)
		{
			return collision;
		}
	}

	collision = tilemap->hit(rect, target);

	if (collision.result != Collision::NONE)
	{
		return collision;
	}

	return { collision.NONE, 0, 0 };
}

void PlayState::spawnMushroom(int x, int y)
{
	SceneObject* m = new Mushroom(game, this, x, y);
	addObject(m);
}

void PlayState::spawnCoin(int x, int y)
{
	SceneObject* m = new Coin(game, this, x, y);
	addObject(m);
}


void PlayState::playerHit()
{
	player->hit();
}

bool PlayState::getMarioImmunity()
{
	return player->getImmunity();
}
