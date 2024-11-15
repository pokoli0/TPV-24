#include "Koopa.h"

Koopa::Koopa(Game* g, int x, int y)
{
	game = g;
	pos = Point2D<int>(x, y);

	texture = game->getTexture(Game::KOOPA);

	frameCounter = 0;

	dir = -1; //izda
	speed = 5; // def: 8

	flipSprite = false; // izda

	frozen = true;

	cout << "Koopa (" << x << ", " << y << ")" << endl;
}

void Koopa::render(SDL_Renderer* renderer)
{
	rect.x = pos.getX() - game->getMapOffset();
	rect.y = pos.getY() - TILE_SIDE;
	rect.w = texture->getFrameWidth() * 2;
	rect.h = texture->getFrameHeight() * 2;

	SDL_RendererFlip flip;
	if (flipSprite) flip = SDL_FLIP_HORIZONTAL;
	else flip = SDL_FLIP_NONE;

	frameCounter++;
	if (frameCounter == 5) {
		frameCounter = 0;

		frame = 0;
	}
	else {
		frame = 1;
	}

	texture->renderFrame(rect, 0, frame, 0, nullptr, flip);

	if (DEBUG) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 128);
		SDL_RenderDrawRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}
}

void Koopa::update()
{
	move();
}


Collision Koopa::hit(const SDL_Rect& rect, bool fromPlayer)
{
	return Collision();
}

void Koopa::move()
{
	if (frozen) {
		if (pos.getX() - texture->getFrameWidth() * (TILE_SIDE + 5) < game->getMapOffset()) {
			frozen = false;
		}
	}
	else {
		pos.setX(pos.getX() + speed * dir);
	}

}
