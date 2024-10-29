#pragma once
#include "checkML.h"

#include <string>
#include <iostream>
#include <fstream>

#include "Texture.h"
#include "Game.h"
#include "Vector2D.h"

using namespace std;

class Game;

class Player
{
private:
	Texture* texture = nullptr;
	Game* game = nullptr;

	Point2D<int> pos;
	int speed;
	int maxHeight;

	// 1 si mario se mueve hacia la derecha, 
	// -1 si es hacia la izquierda
	int dir;

	int lives;

	enum Aspect {
		MARIO,
		SUPERMARIO
	};

	Aspect actualAspect;
	
	// --- para las animaciones
	// textura actual de mario
	int frame;
	// frame de andado 
	int walkFrame;
	// contador de frames
	int frameCounter;
	// true izquierda, false derecha
	bool flipSprite;
	// para la animacion de salto
	bool jumping;

public:
	Player();
	Player(Game* g, int x, int y);
	~Player();

	void render();
	void update();

	void move();
	void jump();

	void updateAnim();

	// maneja eventos de teclado y determina el estado del movimiento
	void handleEvents(const SDL_Event& event);

	//detecta colisiones y recibe da�o
	//Cuando Mario colisione con un enemigo o caiga en una fosa del mapa se reducir� su n�mero de vidas
	//y volver� a su posici�n inicial en el nivel.Super Mario, en cambio, al chocar con un enemigo se convertir�
	//en Mario, permanecer� donde est� y se mantendr� invulnerable durante un par de segundos.
	void hit(Aspect m);

	/// GETTERS --------------------------------
	// devuelve el numero de vidas actuales
	int getLives() const { return lives; }

};

