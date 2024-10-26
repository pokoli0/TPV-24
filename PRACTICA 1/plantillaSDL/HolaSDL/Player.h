#pragma once
#include "checkML.h"

#include <string>
#include <iostream>
#include <fstream>

#include "Texture.h"
#include "Game.h"

using namespace std;

class Game;

class Player
{
private:
	Texture* texture = nullptr;
	Game* game = nullptr;

	int x, y;

	// 1 si mario se mueve hacia la derecha, 
	// -1 si es hacia la izquierda
	int dir;

	int lives;

	enum Aspect {
		MARIO,
		SUPERMARIO
	};

	Aspect actualAspect;

public:
	Player();
	Player(Game* g, int x, int y);
	~Player();

	void render();
	void update();

	// maneja eventos de teclado y determina el estado del movimiento
	void handleEvents();

	//detecta colisiones y recibe daño
	//Cuando Mario colisione con un enemigo o caiga en una fosa del mapa se reducirá su número de vidas
	//y volverá a su posición inicial en el nivel.Super Mario, en cambio, al chocar con un enemigo se convertirá
	//en Mario, permanecerá donde está y se mantendrá invulnerable durante un par de segundos.
	void hit(Aspect m);

	// devuelve el numero de vidas actuales
	int getLives() const { return lives; }

};

