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

	SDL_Rect rect;

	Point2D<int> pos;
	Point2D<int> initPos;
	Point2D<int> speed;
	int xSpeed;

	int lives;
	bool isAlive;

	enum Aspect {
		MARIO,
		SUPERMARIO
	};

	// 0: MARIO
	// 1: SUPERMARIO
	Aspect actualAspect;

	// cuando supermario sea golpeado inmune = true durante un par de segundos
	bool inmune;

	// --- para las animaciones
	// textura actual de mario
	int frame;
	// frame de andado 
	int walkFrame;
	// contador de frames
	int frameCounter;
	// true izquierda, false derecha
	bool flipSprite;
	// flipeador
	SDL_RendererFlip flip;

	// --- salto
	bool jumping;
	bool onGround;


	// --- DEBUGGING
	bool debugMode = false;
	bool fastMode = false;
	int bgSpeed;


public:
	Player();
	Player(Game* g, int x, int y);
	~Player();

	void render(SDL_Renderer* renderer);
	void update();

	// pone la direccion en y a 1 hasta que llega a cierta altura
	void jump();

	// actualiza el frame de la textura
	void updateAnim();

	// cambia el aspecto a SUPERMARIO
	void grow();

	// comprueba cuantas vidas le quedan o si se ha caido, para resetear el nivel
	void checkAlive();

	// reinicia el nivel, poniendo la posicion inicial de mario y las vidas a 3
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
	void hit();

	/// GETTERS --------------------------------
	// devuelve el numero de vidas actuales
	int getLives() const { return lives; }
	// devuelve el aspecto actual de mario
	Aspect getAspect() { return actualAspect; }

	// d = true: para mostrar en consola debugs y poder usar fastMode
	void debug();
};

