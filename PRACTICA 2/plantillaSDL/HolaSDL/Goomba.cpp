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

void Goomba::updateAnim()
{
	_frameCounter++;
	if (_frameCounter == 5) {
		_frameCounter = 0;
		
		_frame = 0;
	}
	else {
		_frame = 1;
	}
}
