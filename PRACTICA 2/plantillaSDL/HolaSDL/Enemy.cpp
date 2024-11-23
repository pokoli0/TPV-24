#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Game* game, int x, int y, Texture* t)
	: SceneObject(game, x, y, TILE_SIDE, TILE_SIDE, t)
{

}

void Enemy::render(SDL_Renderer* renderer)
{
	_rect.x = _position.getX() - game->getMapOffset();
	_rect.y = _position.getY();
	_rect.w = _texture->getFrameWidth() * 2;
	_rect.h = _texture->getFrameHeight() * 2;

	_texture->renderFrame(_rect, 0, _frame, 0, nullptr, _flip);

	if (DEBUG) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 128);
		SDL_RenderDrawRect(renderer, &_rect);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}
}


Collision Enemy::hit(const SDL_Rect& region, Collision::Target target)
{
	return Collision();
}

SceneObject* Enemy::clone() const
{
	return nullptr;
}

void Enemy::updateAnim()
{
}
