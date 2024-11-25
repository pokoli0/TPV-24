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
	// Calcula la intersección
	SDL_Rect intersection;
	SDL_Rect ownRect = getCollisionRect();
	bool hasIntersection = SDL_IntersectRect(&ownRect, &region, &intersection);

	if (hasIntersection) {
		Collision collision{ Collision::DAMAGE, intersection.w, intersection.h };
		if (target == Collision::PLAYER){
			if (!game->getMarioImmunity()) // si mario no es inmune
			{

				if ( intersection.y <= ownRect.y // desde arriba
					&& intersection.w > TILE_SIDE / 4) // para que no detecte col desde el lado
				{
					_isAlive = false;
				}
				else if (target == Collision::PLAYER)
				{
					game->playerHit();
				}
			}

			return collision;
		}
		
	}

	return Collision{ Collision::NONE }; // constante Collision{}
}

SceneObject* Goomba::clone() const
{
	return nullptr;
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
