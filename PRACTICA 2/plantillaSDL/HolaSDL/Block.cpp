#include "Block.h"
#include "Game.h"

Block::Block(Game* game, int x, int y, char v, char act)
	: SceneObject(game, x, y, TILE_SIDE, TILE_SIDE, game->getTexture(Game::BLOCKS)), 
	variant(v), action(act)
{
	setScale(2);

	_flip = SDL_FLIP_NONE; switch (action) {
	case 'C':
		accionBloque = MONEDA;
		break;
	case 'P':
		accionBloque = POTENCIADOR;
		break;
	default:
		accionBloque = NADA;
		break;
	}
}


void Block::render(SDL_Renderer* renderer)
{
	SceneObject::render(renderer);

	switch (variant) {
	case '?':
		_frame = 0;
		break;
	case 'B':
		_frame = 5;
		break;
	case 'H':
		_frame = 7;
		break;
	case 'N':
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

	if (hasIntersection ) {
		Collision collision{ Collision::OBSTACLE, intersection.w, intersection.h };
		if (target == Collision::ENEMIES && (region.y) >= (_rect.y + _rect.h) - 8)
		{
				if (_frame == surpriseFrame || _frame == 7)
				{
					if (accionBloque == POTENCIADOR)
					{
						game->spawnMushroom(_position.getX(), _position.getY() - TILE_SIDE);
						
					}
					else
					{
						game->spawnCoin(_position.getX(), _position.getY() - TILE_SIDE);
					}
					variant = 'N';
					accionBloque = NADA;
				}
				else if (_frame = 5 && game->getMarioState() == 1)
				{
					cout << "roto";
					_isAlive = false;// el bloque se destruye
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

void Block::updateAnim()
{
	if (accionBloque !=  NADA)
	{
		_frameCounter++;
		if (_frameCounter >= 1) {
			_frameCounter = 0;

			surpriseFrame = (surpriseFrame + 1) % 4;
			_frame = surpriseFrame;
		}
	}
	
}
