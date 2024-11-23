#include "Block.h"
#include "Game.h"

Block::Block(Game* game, int x, int y)
	: SceneObject(game, x, y, TILE_SIDE, TILE_SIDE, game->getTexture(Game::BLOCKS))
{

}

void Block::render(SDL_Renderer* renderer)
{

}

void Block::update()
{
}

Collision Block::hit(const SDL_Rect& region, Collision::Target target)
{
	return Collision();
}

SceneObject* Block::clone() const
{
	return nullptr;
}

void Block::updateAnim()
{
}
