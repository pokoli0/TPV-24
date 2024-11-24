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
	case '?':
		_frame = 0;
		break;
	case 'B':
		_frame = 5;
		break;
	case 'H':
		_frame = 7;
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

	if (hasIntersection) {
		Collision collision{ Collision::OBSTACLE, intersection.w, intersection.h };
		
		// [...] Manejo del efecto del bloque

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
	_frameCounter++;
	if (_frameCounter >= 1) {
		_frameCounter = 0;

		surpriseFrame = (surpriseFrame + 1) % 4;
		_frame = surpriseFrame;
	}
}
