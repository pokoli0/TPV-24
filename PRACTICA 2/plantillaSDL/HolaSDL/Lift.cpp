#include "Lift.h"
#include "Game.h"

Lift::Lift(Game* game, int x, int y, int speed)
	: SceneObject(game, x, y, _texture->getFrameWidth(), _texture->getFrameHeight(), game->getTexture(Game::LIFT))
{
	setScale(2);
	_speed.setY(speed);
}

void Lift::update()
{
}

Collision Lift::hit(const SDL_Rect& region, Collision::Target target)
{
	return Collision();
}

SceneObject* Lift::clone() const
{
	return nullptr;
}