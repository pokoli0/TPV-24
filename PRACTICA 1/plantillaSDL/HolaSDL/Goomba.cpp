#include "Goomba.h"

Goomba::Goomba(Game* g, int x, int y)
{
	game = g;
	pos = Point2D<int>(x, y);

	texture = game->getTexture(Game::GOOMBA);

	frameCounter = 0;

	cout << "Goomba (" << x << ", " << y << ")" << endl;
}

void Goomba::render()
{
	SDL_Rect rect;
	rect.x = pos.getX() - game->getMapOffset();
	rect.y = pos.getY();
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

void Goomba::update()
{
}
