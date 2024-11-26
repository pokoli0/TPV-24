#include "Block.h"
#include "Game.h"

Block::Block(Game* game, int x, int y, char v, char act)
	: SceneObject(game, x, y, TILE_SIDE, TILE_SIDE, game->getTexture(Game::BLOCKS)), 
	variant(v), action(act)
{
	setScale(2);

	_flip = SDL_FLIP_NONE;
}


void Block::render(SDL_Renderer* renderer)
{
	SceneObject::render(renderer);

	switch (variant) {
	case '?':				// bloque ?
		_frame = 0;
		break;
	case 'B':				// bloque LADRILLOS
		_frame = 5;
		break;
	case 'H':				// bloque OCULTO
		_frame = 7;
		break;
	case 'N':				// bloque VACIO
		_frame = 4;
		break;
	}

	if (variant == '?')
	{
		updateAnim();
	}
}

void Block::update()
{
	game->checkCollision(_rect, Collision::PLAYER);
}

Collision Block::hit(const SDL_Rect& region, Collision::Target target)
{
	// Calcula la intersección
	SDL_Rect intersection;
	SDL_Rect ownRect = getCollisionRect();
	bool hasIntersection = SDL_IntersectRect(&ownRect, &region, &intersection);

	if (hasIntersection) 
	{
		Collision collision{ Collision::OBSTACLE, intersection.w, intersection.h };

		if (target == Collision::ENEMIES && (region.y) >= (_rect.y + _rect.h) - 8)
		{
			if (variant == '?')
			{
				if (action == 'P') // Power Up
				{
					game->spawnMushroom(_position.getX(), _position.getY() - TILE_SIDE);
				}
				else // Coin 'C'
				{
					game->spawnCoin(_position.getX(), _position.getY() - TILE_SIDE);
				}

				variant = 'N';
			}
			else if (variant == 'B' && game->getMarioState() == 1)
			{
				cout << "roto" << endl;
				_isAlive = false; // el bloque se destruye
			}
		}
		

		return collision;
	}

	return Collision{ Collision::NONE };
}

SceneObject* Block::clone() const
{
	return nullptr;
}

void Block::updateAnim() // solo se llama para el '?' en el render
{
	_frameCounter++;
	if (_frameCounter >= 1) 
	{
		_frameCounter = 0;

		surpriseFrame = (surpriseFrame + 1) % 4;
		_frame = surpriseFrame;
	}
}
