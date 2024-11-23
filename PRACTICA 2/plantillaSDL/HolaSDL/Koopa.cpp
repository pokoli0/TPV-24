#include "Koopa.h"
#include "Game.h"

Koopa::Koopa(Game* game, int x, int y)
	: Enemy(game, x, y, game->getTexture(Game::KOOPA))
{

	_flip = SDL_FLIP_HORIZONTAL;

	cout << "Koopa (" << x << ", " << y << ")" << endl;
}

void Koopa::render(SDL_Renderer* renderer)
{
	Enemy::render(renderer);
	updateAnim();
}

void Koopa::update()
{
	if (_speed.getX() > 0) _flip = SDL_FLIP_HORIZONTAL;
	else _flip = SDL_FLIP_NONE;
}

Collision Koopa::hit(const SDL_Rect& region, Collision::Target target)
{
	return Collision();
}

SceneObject* Koopa::clone() const
{
	return nullptr;
}

void Koopa::updateAnim()
{
	_frameCounter++;
	if (_frameCounter >= 5)
	{
		_frameCounter = 0;
		koopaFrame = (koopaFrame + 1) % 2; // Alterna entre 0 y 1

		if (koopaFrame == 0) {
			_frame = 0;
		}
		else if (koopaFrame == 1) {
			_frame = 1;
		}
	}
}
