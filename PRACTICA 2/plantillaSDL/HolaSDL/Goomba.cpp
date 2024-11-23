#include "Goomba.h"
#include "Game.h"

Goomba::Goomba(Game* game, int x, int y, Texture* t)
	: Enemy(game, x, y, game->getTexture(Game::GOOMBA))
{

}

void Goomba::render(SDL_Renderer* renderer)
{
}

void Goomba::update()
{
}

Collision Goomba::hit(const SDL_Rect& region, Collision::Target target)
{
	return Collision();
}

SceneObject* Goomba::clone() const
{
	return nullptr;
}
