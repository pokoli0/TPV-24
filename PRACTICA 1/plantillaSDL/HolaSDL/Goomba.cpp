#include "Goomba.h"

Goomba::Goomba(Game* g, int x, int y)
{
	game = g;
	pos = Point2D<int>(x, y);

	texture = game->getTexture(Game::GOOMBA);

	frameCounter = 0;

	dir = -1; //izda
	speed = 5; // def: 8
	backgroundScrollSpeed = 5; // def: 5

	flipSprite = true; // izda = 1

	frozen = true;

	cout << "Goomba (" << x << ", " << y << ")" << endl;
}

void Goomba::render()
{
	SDL_Rect rect;
	rect.x = pos.getX() - game->getMapOffset();
	rect.y = pos.getY();
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
}

void Goomba::update()
{
	move();
}

void Goomba::move()
{
	//movimiento horizontal (si colisiona tiene que cambiar dir)
	if (!frozen) {
		pos.setX(pos.getX() + speed * dir);
	}


	// caida???
}

void Goomba::checkFrozen()
{
}


