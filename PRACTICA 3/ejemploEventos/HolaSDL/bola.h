#ifndef BOLA_H
#define BOLA_H

#include "game.h"
#include "texture.h"
#include "button.h"

/**
 * Bola que sigue al cursor.
 *
 * Hereda de la clase "interfaz" ButtonListener para poder
 * suscribirse como oyente en el botón.
 */
class Bola : public ButtonListener {
	Game* game;
	Texture* texture;
	SDL_Rect boundingBox;  // caja de dibujo de la bola
	bool parada;           // si la bola está parada o en movimiento

public:
	Bola(Game*);
	~Bola();

	void update();
	void render() const;

	// Método de los ButtonListener para ser informado
	// del evento de click del botón y actuar en consecuencia
	void handleClick() override;
};

#endif // BOLA_H
