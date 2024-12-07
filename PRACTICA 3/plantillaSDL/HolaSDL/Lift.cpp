#include "checkML.h"

#include "Lift.h"
#include "Game.h"

Lift::Lift(Game* game, PlayState* s, int x, int y, int speed)
	: SceneObject(game, s, x, y, game->getTexture(Game::LIFT)->getFrameWidth(), 
		game->getTexture(Game::LIFT)->getFrameHeight(), game->getTexture(Game::LIFT))
{
	setScale(1);
	_speed.setY(speed);

	a = WINDOW_HEIGHT * TILE_SIDE + TILE_SIDE;
	b = 0;
}

void Lift::update()
{
	// Movimiento vertical constante
	_position.setY(_position.getY() + _speed.getY());

	//cuando llegue arriba vuelve a aparecer abajo

	if (_speed.getY() < 0 && _position.getY() <= b) {
		_position.setY(a);
	}
	else if (_speed.getY() > 0 && _position.getY() >= a)
	{
		_position.setY(b);
	}

}

Collision Lift::hit(const SDL_Rect& region, Collision::Target target)
{
	Collision colision;

	// Calcula la intersección
	SDL_Rect ownRect = getCollisionRect();
	bool hasIntersection = SDL_IntersectRect(&ownRect, &region, &colision.intersectionRect);


	if (hasIntersection)
	{
		colision.result = Collision::OBSTACLE;
		colision.horizontal = colision.intersectionRect.w;
		colision.vertical = colision.intersectionRect.h; // raro

		return colision;
	}

	return Collision{ Collision::NONE };
}

SceneObject* Lift::clone() const
{
	return new Lift(*this);
}
