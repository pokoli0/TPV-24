#include "checkML.h"

#include "Goomba.h"
#include "Game.h"

Goomba::Goomba(Game* game, int x, int y)
	: Enemy(game, x, y, game->getTexture(Game::GOOMBA))
{
	cout << "Goomba (" << x << ", " << y << ")" << endl;
}

void Goomba::render(SDL_Renderer* renderer)
{
	Enemy::render(renderer);
	updateAnim();
}


Collision Goomba::hit(const SDL_Rect& region, Collision::Target target)
{
	return Enemy::hit(region, target);

}

SceneObject* Goomba::clone() const
{
	return new Goomba(*this);
}

void Goomba::updateAnim()
{
	_frameCounter++;
	if (_frameCounter >= 5)
	{
		_frameCounter = 0;
		goombaFrame = (goombaFrame + 1) % 2;

		_frame = (goombaFrame == 0 ? 0 : 1);
	}
}
