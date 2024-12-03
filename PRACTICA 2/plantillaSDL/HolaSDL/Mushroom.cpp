#include "checkML.h"

#include "Mushroom.h"
#include "Game.h"

Mushroom::Mushroom(Game* game, int x, int y)
	: Pickable(game, x, y, game->getTexture(Game::MUSHROOM))
{
	_speed.setX(3);
}

void Mushroom::render(SDL_Renderer* renderer)
{
	Pickable::render(renderer);
}

void Mushroom::update()
{
	checkAlive();

	//if (_position.getX() - _texture->getFrameWidth() * (TILE_SIDE + 5) < game->getMapOffset()) {
		//frozen = false;
	//}

	collision = tryToMove(_speed, Collision::PLAYER);

	if (_speed.getY() < SPEED_LIMIT) _speed += {0, GRAVITY};

	if (collision.vertical) _speed.setY(0);
	if (collision.horizontal) _speed.setX(-_speed.getX()); // cambio de direccion
}

Collision Mushroom::hit(const SDL_Rect& region, Collision::Target target)
{
	return Pickable::hit(region,target);
}

SceneObject* Mushroom::clone() const
{
	return new Mushroom(*this);
}

void Mushroom::triggerAction()
{
	game->setMarioState(1);
	game->givePoints(1000);
	cout << "Points: " << game->getPoints() << endl;
	delete this;
}

void Mushroom::checkAlive()
{
	if (_position.getY() >= MAX_HEIGHT || _position.getX() <= 0)
	{
		delete this;
		cout << "byebe" << endl;
		//_isAlive = false;
	}
}
