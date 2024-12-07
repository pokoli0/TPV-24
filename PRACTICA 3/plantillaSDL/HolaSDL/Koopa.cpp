#include "checkML.h"

#include "Koopa.h"
#include "Game.h"

#include "PlayState.h"

Koopa::Koopa(Game* game, PlayState* s, int x, int y)
	: Enemy(game, s, x, y, game->getTexture(Game::KOOPA))
{
	_flip = SDL_FLIP_HORIZONTAL;
	cout << "Koopa (" << x << ", " << y << ")" << endl;
}

void Koopa::render(SDL_Renderer* renderer)
{
	_height = 64;
	_rect.x = _position.getX() - _playState->getMapOffset();
	_rect.y = _position.getY() - _height; // hago el render aqui porque el koopa tiene distinta altura
	_rect.w = _texture->getFrameWidth() * _scale;
	_rect.h = _texture->getFrameHeight() * _scale;

	_texture->renderFrame(_rect, 0, _frame, 0, nullptr, _flip);

	if (DEBUG) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 128);
		SDL_RenderDrawRect(renderer, &_rect);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}

	updateAnim();
}

Collision Koopa::hit(const SDL_Rect& region, Collision::Target target)
{
	return Enemy::hit(region, target);
}

SceneObject* Koopa::clone() const
{
	return new Koopa(*this);
}

void Koopa::updateAnim()
{
	_frameCounter++;
	if (_frameCounter >= 5)
	{
		_frameCounter = 0;
		koopaFrame = (koopaFrame + 1) % 2; // Alterna entre 0 y 1

		_frame = (koopaFrame == 0 ? 0 : 1);
	}
}
