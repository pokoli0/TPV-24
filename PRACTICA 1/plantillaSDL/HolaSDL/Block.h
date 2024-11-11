#pragma once
#include "checkML.h"

#include "Vector2D.h"
#include "Texture.h"
#include "Game.h"

class Block
{
private:
	Point2D<int> pos;

	enum TipoBloque {
		LADRILLO,
		SORPRESA,
		VACIO,
		OCULTO,
	};

	TipoBloque tipoBloque;

	enum AccionBloque {
		POTENCIADOR,
		MONEDA,
		NADA,
	};
	AccionBloque accionBloque;

	SDL_Rect rect;

	Texture* texture;
	int frame;
	Game* game;

public:

	Block();
	Block(Game* g, int x, int y, char tipo, char accion);

	void render();
	void update();
	Collision hit(const SDL_Rect& rect, bool fromPlayer);
};

