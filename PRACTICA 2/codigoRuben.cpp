//
// Código relativo a las colisiones
//

// collision.h

struct Collision
{
	// ¿A quién afecta esta colisión? Se puede usar en lugar del
	// bool fromPlayer para objetos que atacan tanto a enemigos
	// como al jugador (caparaszón opciona).
	enum Target {
		ENEMIES = 1,	// afecta a enemigos
		PLAYER = 2,	// afecta al jugador
		BOTH = 3,	// afecta a ambos
	};

	// Tipo de resultado de la colisión
	enum Result {
		NONE,		// no ha habido colisión
		DAMAGE,		// la colisión produce daño
		OBSTACLE,	// la colisión impide el movimiento
	};

	Result result = NONE;
	int horizontal = 0;   // profundidad de la colisión horizontal
	int vertical = 0;     // profundidad de la colisión vertical
};

// sceneObject.cpp

// El método protegido tryToMove concentra el código de la comprobación
// de las colisiones para todos los objetos del juego. Recibe un vector
// con el movimiento que se quiere aplicar al objeto, prueba el movimiento
// en cambos ejes y devuelve la información de tipo Collision.

Collision
SceneObject::tryToMove(const Vector2D<>& speed, Collision::Target target)
{
	Collision collision;
	SDL_Rect rect = getCollisionRect();

	// Intenta moverse en vertical
	if (speed.getY() != 0) {
		rect.y += speed.getY();

		collision = game->checkCollision(rect, target);

		// Cantidad que se ha entrado en el obstáculo (lo que hay que deshacer)
		int fix = collision.vertical * (speed.getY() > 0 ? 1 : -1);
		_position += {0, speed.getY() - fix};

		// Obs: a ? b : c es el operador ternario: vale b si a es cierto y c en caso contrario

		rect.y -= fix; // recoloca la caja para la siguiente colisión
	}

	collision.horizontal = 0; // la horizontal del choque vertical da igual

	// Intenta moverse en horizontal
	// (podría ser conveniente comprobar colisiones incluso aunque el objeto estuviera parado)
	if (speed.getX() != 0) {
		rect.x += speed.getX();

		Collision partial = game->checkCollision(rect, target);

		// Copia la información de esta colisión a la que se devolverá
		collision.horizontal = partial.horizontal;

		if (partial.result == Collision::DAMAGE)
			collision.result = Collision::DAMAGE;

		_position += {speed.getX() - collision.horizontal * (speed.getX() > 0 ? 1 : -1), 0};
	}

	return collision;
}

// enemy.cpp (uso del tryToMove, por ejemplo)

void
Enemy::update()
{
	// Acelra la velocidad con la gravedad
	if (speed.getY() < SPEED_LIMIT)
		speed += {0, Game::GRAVITY};

	// Velocidad en este ciclo (no siempre avanza lateralmente)
	Vector2D<> realSpeed = speed;

	if (moveDelay-- == 0)
		moveDelay = MOVE_PERIOD;
	else
		realSpeed.setX(0);

	// Intenta moverse
	Collision collision = tryToMove(realSpeed, Collision::PLAYER);

	// Si toca un objeto en horizontal cambia de dirección
	if (collision.horizontal)
		speed.setX(-speed.getX());

	// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
	if (collision.vertical)
		speed.setY(0);

	// SceneObject::update(); // si hiciera falta
}

// sceneObject.cpp (otra vez)

SDL_Rect
SceneObject::getCollisionRect() const
{
	return SDL_Rect{
		_position.getX(),
		_position.getY() - _height,  // la referencia es la esquina inferior izquierda
		_width,
		_height
	};
}

SDL_Rect
SceneObject::getRenderRect() const
{
	return SDL_Rect{
		_position.getX() - game->getMapOffset(),  // coordenadas de la ventana
		_position.getY() - _height,
		_width,
		_height
	};
}

// pickable.cpp (ejemplo de hit)

Collision
Pickable::hit(const SDL_Rect& region, Collision::Target target)
{
	// Comprueba si hay colisión
	SDL_Rect ownRect = getCollisionRect();

	if (target == Collision::ENEMIES && SDL_HasIntersection(&ownRect, &region)) {
		triggerAction();  // método protegido que implementará la subclase
		delete this;
	}

	return NO_COLLISION; // constante Collision{}
}

// coin.cpp

void
Coin::triggerAction()
{
	game->givePoints(200);
}

// block.cpp (ejemplo de hit con caja de corte)

Collision
Block::hit(const SDL_Rect& region, Collision::Target target)
{
	// Calcula la intersección
	SDL_Rect intersection;
	SDL_Rect ownRect = getCollisionRect();
	bool hasIntersection = SDL_IntersectRect(&ownRect, &region, &intersection);

	if (hasIntersection) {
		Collision collision{Collision::OBSTACLE, intersection.w, intersection.h};

		// [...] Manejo del efecto del bloque

		return collision;
	}

	return NO_COLLISION;
}