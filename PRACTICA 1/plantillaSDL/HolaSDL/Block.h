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

	enum AccionBloque {
		POTENCIADOR,
		MONEDA
	};

	//Texture* texturaBloque;
	//Game* game;

public:

	Block();
	Block(Point2D<int> pos, TipoBloque tipo, AccionBloque accion, std::istream& archivo);

	void render();
	void update();
	void hit();

};

