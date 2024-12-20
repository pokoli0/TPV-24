#include "checkML.h"

#include "Pickable.h"
#include "Game.h"

Pickable::Pickable(Game* game, PlayState* s, int x, int y, Texture* t)
	: SceneObject(game, s, x, y, TILE_SIDE, TILE_SIDE, t)
{
	setScale(2);
}

void Pickable::update()
{
}

Collision Pickable::hit(const SDL_Rect& region, Collision::Target target)
{
	SDL_Rect ownRect = getCollisionRect();

	if (target == Collision::ENEMIES && SDL_HasIntersection(&ownRect, &region)) 
	{
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

