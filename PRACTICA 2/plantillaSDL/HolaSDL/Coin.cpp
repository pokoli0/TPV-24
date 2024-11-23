#include "Coin.h"
#include "Game.h"

Coin::Coin(Game* game, int x, int y)
	: Pickable(game, x, y, game->getTexture(Game::COIN))
{
}

void Coin::render(SDL_Renderer* renderer)
{
	Pickable::render(renderer);
	updateAnim();
}

void Coin::update()
{
}

Collision Coin::hit(const SDL_Rect& region, Collision::Target target)
{
	return Collision();
}

SceneObject* Coin::clone() const
{
	return nullptr;
}

void Coin::updateAnim()
{
	_frameCounter++;
	if (_frameCounter >= 5)
	{
		_frameCounter = 0;
		coinFrame = (coinFrame + 1) % 4;

		if (coinFrame == 0) {
			_frame = 0;
		}
		else if (coinFrame == 1) {
			_frame = 1;
		}
		else if (coinFrame == 2) {
			_frame = 2;
		}
		else if (coinFrame == 3) {
			_frame = 3;
		}
	}
}

void Coin::triggerAction()
{
	Pickable::triggerAction();
	game->givePoints(200);
}
