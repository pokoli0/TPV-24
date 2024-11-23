#include "Koopa.h"
#include "Game.h"

Koopa::Koopa(Game* game, int x, int y, Texture* t)
	: Enemy(game, x, y, game->getTexture(Game::KOOPA))
{
	_height = TILE_SIDE * 2;
}

void Koopa::render(SDL_Renderer* renderer)
{
}

void Koopa::update()
{
}

Collision Koopa::hit(const SDL_Rect& region, Collision::Target target)
{
	return Collision();
}

SceneObject* Koopa::clone() const
{
	return nullptr;
}
