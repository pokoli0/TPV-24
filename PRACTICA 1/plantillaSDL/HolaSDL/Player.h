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
	Texture* supertexture = nullptr;
	Game* game = nullptr;

	Point2D<int> pos;
	int speed;
	int backgroundScrollSpeed;

	// 1 si mario se mueve hacia la derecha, 
	// -1 si es hacia la izquierda
	int dir;

	int lives;

	enum Aspect {
		MARIO,
		SUPERMARIO
	};

	// 0: MARIO
	// 1: SUPERMARIO
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

	// --- salto
	bool jumping;
    int jumpVelocity;
	int gravity;         
	int groundY;


	// --- DEBUGGING
	bool fastMode = false;

public:
	Player();
	Player(Game* g, int x, int y);
	~Player();

	void render();
	void update();

	// movimiento
	void move();
	void jump();

	// actualiza el frame de la textura
	void updateAnim();

	// cambia el aspecto a SUPERMARIO
	void grow();

	// maneja eventos de teclado y determina el estado del movimiento
	void handleEvents(const SDL_Event& event);

	//detecta colisiones y recibe daño
	//Cuando Mario colisione con un enemigo o caiga en una fosa del mapa se reducirá su número de vidas
	//y volverá a su posición inicial en el nivel.Super Mario, en cambio, al chocar con un enemigo se convertirá
	//en Mario, permanecerá donde está y se mantendrá invulnerable durante un par de segundos.
	void hit(Aspect m);

	/// GETTERS --------------------------------
	// devuelve el numero de vidas actuales
	int getLives() const { return lives; }

	// d = true: para mostrar en consola debugs y poder usar fastMode
	void debug(bool d);
};

