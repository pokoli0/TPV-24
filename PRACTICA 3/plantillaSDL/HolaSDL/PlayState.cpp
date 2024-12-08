#include "PlayState.h"
#include <iostream>

PlayState::PlayState(Game* g, int level)
	: GameState(g)
{
	cout << "Play State " << level << endl;

	mapOffset = 0;
	//mapOffset = 5880; // para probar cambio de nivel
	//mapOffset = 4080; // para probar el lift en level 2

	gameWon = false;

	nextObject = 0;

	loadLevel(level);
}

void PlayState::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);

	//for (auto obj : stateList) obj->render(renderer);
	for (auto obj : sceneObjects) obj->render(renderer);
}

void PlayState::update()
{
	// Borde derecho del mapa (+ una casilla)
	const int rightThreshold = mapOffset + Game::WIN_WIDTH + TILE_SIDE;

	while (nextObject < objectQueue.size() && objectQueue[nextObject]->getXPos() < rightThreshold)
	{
		addObject(objectQueue[nextObject++]->clone()); // se hace a partir del 2
	}

	//for (auto obj : stateList) obj->update();
	for (auto obj : sceneObjects) obj->update();
}

void PlayState::loadLevel(int l)
{
	string root = "../assets/maps/world" + to_string(l) + ".csv";

	tilemap = new TileMap(game, this, root);

	objectQueue.push_back(tilemap);
	addObject(objectQueue[nextObject++]); // tilemap = 1

	//cout << "Tile:" << nextObject << endl;

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
				//player = new Player(this, 4366, 300); // para probar el lift
				//player = new Player(game, this, 6166, 448); // para probar bandera

				objectQueue.push_back(player);
				addObject(objectQueue[nextObject++]); // player = 2

				addEventListener(player); // se encarga del input

				//cout << "Mario:" << nextObject << endl;
			}
			else
			{
				cout << "No se crea nuevo Mario. " << endl;
				// Reposicionar?¿
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

	if (gameWon)
	{
		mapOffset = 0;
		nextObject = 2;
	}
}

void PlayState::addObject(SceneObject* o)
{
	if (nextObject == 1)
	{
		sceneObjects.push_front(o);
		stateList.push_front(o);
	}
	else if (nextObject == 2)
	{
		sceneObjects.push_back(player); /// esto puede estar mal al hacer el cambio de nivel 1!!!1
		stateList.push_back(player);
	}
	else
	{
		sceneObjects.push_back(o);
		stateList.push_back(player);
	}
}

void PlayState::resetLevel()
{
	for (auto obj : stateList)
	{
		if (obj != player && obj != tilemap)
		{
			delete obj; // POSIBLE FALLO -> NO SE BORRAN ENTIDADES ANTERIORES
		}
	}

	// reinicia mapoffset y lista de objetos
	nextObject = 2;
	mapOffset = 0;

	// recarga nivel
	loadLevel(level); // POSIBLE FALLO -> SE HACE LOAD DE ENTIDADES ANTERIORES + NUEVAS ??¿¿?
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
