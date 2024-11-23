#pragma once

struct Collision
{
	// �A qui�n afecta esta colisi�n? Se puede usar en lugar del
	// bool fromPlayer para objetos que atacan tanto a enemigos
	// como al jugador (caparaz�n opcional).
	enum Target {
		ENEMIES = 1,	// afecta a enemigos
		PLAYER = 2,	// afecta al jugador
		BOTH = 3,	// afecta a ambos
	};

	// Tipo de resultado de la colisi�n
	enum Result {
		NONE,		// no ha habido colisi�n
		DAMAGE,		// la colisi�n produce da�o
		OBSTACLE,	// la colisi�n impide el movimiento
	};

	Result result = NONE; // default
	int horizontal = 0;   // profundidad de la colisi�n horizontal
	int vertical = 0;     // profundidad de la colisi�n vertical

	SDL_Rect intersectionRect;

	operator bool() const { 
		bool c = false;
		if (result != NONE) {
			return true;
		}
	};
};