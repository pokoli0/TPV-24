#include "Block.h"
#include "Game.h"

Block::Block(Game* game, int x, int y, char variant, char action)
	: SceneObject(game, x, y, TILE_SIDE, TILE_SIDE, game->getTexture(Game::BLOCKS))
{
	setScale(2);

	_flip = SDL_FLIP_NONE;
}


void Block::update()
{
}

Collision Block::hit(const SDL_Rect& region, Collision::Target target)
{
	// Calcula la intersección
	SDL_Rect intersection;
	SDL_Rect ownRect = getCollisionRect();
	bool hasIntersection = SDL_IntersectRect(&ownRect, &region, &intersection);

	if (hasIntersection) {
		Collision collision{ Collision::OBSTACLE, intersection.w, intersection.h };

		// [...] Manejo del efecto del bloque

		return collision;
	}

	return Collision{};
}

SceneObject* Block::clone() const
{
	return nullptr;
}

void Block::updateAnim()
{
}
