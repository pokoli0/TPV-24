#include "PlayState.h"
#include <iostream>

PlayState::PlayState(Game* g, int level)
	: GameState(g)
{
	cout << "Play State " << level << endl;

	mapOffset = 0;
	//mapOffset = 5880; // para probar cambio de nivel
	//mapOffset = 4080; // para probar el lift en level 2

	nextObject = 0;

	loadLevel(level);
}

void PlayState::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);

	for (auto obj : stateList) obj->render(renderer);
	//for (auto obj : sceneObjects) obj->render(r);
}

void PlayState::update()
{
	// Borde derecho del mapa (+ una casilla)
	const int rightThreshold = mapOffset + Game::WIN_WIDTH + TILE_SIDE;

	while (nextObject < objectQueue.size() && objectQueue[nextObject]->getXPos() < rightThreshold)
	{
		addObject(objectQueue[nextObject++]->clone());
	}

	for (auto obj : stateList) obj->update();
	//for (auto obj : sceneObjects) obj->update();

}

void PlayState::loadLevel(int l)
{
	string root = "../assets/maps/world" + to_string(l) + ".csv";

	tilemap = new TileMap(game, this, root);

	objectQueue.push_back(tilemap);
	addObject(tilemap);
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

		switch (tipo) {
		case 'M':
			/// ===== CREACION DE MARIO =====
			if (player == nullptr) 
			{
				player = new Player(game, this, x, y);
				//player = new Player(this, 4366, 300); // para probar el lift
				//player = new Player(this, 6166, 448); // para probar bandera



				objectQueue.push_back(player);
				addObject(player);
				nextObject++;

				addEventListener(player);
				//cout << "Mario:" << nextObject << endl;
			}
			else
			{
				cout << "No se crea nuevo Mario. " << endl;
				// Reposicionar?�
			}

			break;
		case 'B':
			objectQueue.push_back(new Block(game, this, x, y, atrib, accion));
			break;
		case 'G':
			objectQueue.push_back(new Goomba(game, this, x, y));
			break;
		case 'K':
			objectQueue.push_back(new Koopa(game, this, x, y));
			break;
		case 'L':
			objectQueue.push_back(new Lift(game, this, x, y, sp));
			break;
		case 'C':
			objectQueue.push_back(new Coin(game, this, x, y));
			break;
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
		stateList.push_front(o);
	}
	else if (nextObject == 2)
	{
		//player = o;
		stateList.push_back(player); /// esto puede estar mal al hacer el cambio de nivel 1!!!1
	}
	else
	{
		stateList.push_back(o);
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
	loadLevel(level); // POSIBLE FALLO -> SE HACE LOAD DE ENTIDADES ANTERIORES + NUEVAS ??��?
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
	sceneObjects.push_back(m);
	stateList.push_back(m);
}

void PlayState::spawnCoin(int x, int y)
{
	SceneObject* m = new Coin(game, this, x, y);
	sceneObjects.push_back(m);
	stateList.push_back(m);
}


void PlayState::playerHit()
{
	player->hit();
}

bool PlayState::getMarioImmunity()
{
	return player->getImmunity();
}
