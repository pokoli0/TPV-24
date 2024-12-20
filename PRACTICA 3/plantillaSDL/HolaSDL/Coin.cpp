#include "checkML.h"

#include "Coin.h"
#include "Game.h"

Coin::Coin(Game* game, PlayState* s, int x, int y)
	: Pickable(game, s, x, y, game->getTexture(Game::COIN))
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
	return Pickable::hit(region,target);
}

SceneObject* Coin::clone() const
{
	return new Coin(*this);
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
	game->givePoints(200);
	cout << "Points: " << game->getPoints() << endl;
	delete this;
}
