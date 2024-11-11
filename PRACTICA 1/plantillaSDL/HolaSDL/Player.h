#pragma once
#include "checkML.h"

#include <string>
#include <iostream>
#include <fstream>

#include "Texture.h"
#include "Game.h"
#include "Vector2D.h"

#include "Collision.h"

using namespace std;

class Game;

class Player
{
private:
	Texture* texture = nullptr;
	Texture* supertexture = nullptr;
	Game* game = nullptr;

	//SDL_Rect rect;

	Point2D<int> pos;
	Point2D<int> initPos;
	int speed;

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

	// cuando supermario sea golpeado inmune = true durante un par de segundos
	bool inmune;

	int backgroundScrollSpeed;

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
	bool debugMode = false;
	bool fastMode = false;

public:
	Player();
	Player(Game* g, int x, int y);
	~Player();

	void render();
	void update();

	// movimiento
	void move();
	//activa el salto
	void jump();

	// actualiza el frame de la textura
	void updateAnim();

	// cambia el aspecto a SUPERMARIO
	void grow();

	// reinicia el nivel
	void resetLevel();

	// maneja eventos de teclado y determina el estado del movimiento
	void handleEvents(const SDL_Event& event);

	/*
	detecta colisiones y recibe daño
	MARIO colisiona con un enemigo o caiga 
	-> lives--
	-> volverá a su posición inicial en el nivel
	  SUPERMARIO al chocar con un enemigo 
	-> se convertirá en MARIO
	-> permanecerá donde está
	-> se mantendrá invulnerable durante un par de segundos
	[ Cosas de Ruben ]
	Utiliza los métodos SDL_HasIntersection o SDL_IntersectRect 
	con su caja de colisión y la que recibe para determinar si hay colisión.
	*/
	Collision hit(const SDL_Rect& rect, bool fromPlayer);

	/// GETTERS --------------------------------
	// devuelve el numero de vidas actuales
	int getLives() const { return lives; }

	// d = true: para mostrar en consola debugs y poder usar fastMode
	void debug();
};

