#include "Pickable.h"
#include "Game.h"

Pickable::Pickable(Game* game, int x, int y, Texture* t)
	: SceneObject(game, x, y, TILE_SIDE, TILE_SIDE, t)
{
	setScale(2);
}

void Pickable::update()
{
}

Collision Pickable::hit(const SDL_Rect& region, Collision::Target target)
{
	// Comprueba si hay colisión
	SDL_Rect ownRect = getCollisionRect();

	if (target == Collision::PLAYER && SDL_HasIntersection(&ownRect, &region)) {
		triggerAction();
	}

	return Collision{}; // constante Collision{}
}

SceneObject* Pickable::clone() const
{
	return nullptr;
}

void Pickable::updateAnim()
{
}

void Pickable::triggerAction()
{
	_isAlive = false;
}
