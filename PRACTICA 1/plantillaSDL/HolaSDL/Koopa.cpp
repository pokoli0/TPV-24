#include "Koopa.h"

Koopa::Koopa(Game* g, int x, int y)
{
	game = g;
	pos = Point2D<int>(x, y);

	texture = game->getTexture(Game::KOOPA);

	frameCounter = 0;

	cout << "Koopa (" << x << ", " << y << ")" << endl;
}

void Koopa::render()
{
	SDL_Rect rect;
	rect.x = pos.getX() - game->getMapOffset();
	rect.y = pos.getY() - TILE_SIDE;
	rect.w = texture->getFrameWidth() * 2;
	rect.h = texture->getFrameHeight() * 2;

	frameCounter++;
	if (frameCounter == 5) {
		frameCounter = 0;

		frame = 0;
	}
	else {
		frame = 1;
	}

	texture->renderFrame(rect, 0, frame);
}

void Koopa::update()
{
}
