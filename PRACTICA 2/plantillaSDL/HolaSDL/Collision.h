#pragma once

struct Collision
{
	// �A qui�n afecta esta colisi�n? Se puede usar en lugar del
	// bool fromPlayer para objetos que atacan tanto a enemigos
	// como al jugador (caparasz�n opciona).
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

	Result result = NONE;
	int horizontal = 0;   // profundidad de la colisi�n horizontal
	int vertical = 0;     // profundidad de la colisi�n vertical

	operator bool() const;
};