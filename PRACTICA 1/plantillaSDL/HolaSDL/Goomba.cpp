#include "Goomba.h"

Goomba::Goomba(Game* g, int x, int y)
{
	game = g;
	pos = Point2D<int>(x, y);

	texture = game->getTexture(Game::GOOMBA);

	frameCounter = 0;

	dir = -1; //izda
	speed = 5; // def: 8

	flipSprite = true; // izda = 1

	frozen = true;

	cout << "Goomba (" << x << ", " << y << ")" << endl;
}

void Goomba::render()
{
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

Collision Goomba::hit(const SDL_Rect& rect, bool fromPlayer)
{
	return Collision();
}

void Goomba::move()
{ 
	//movimiento horizontal
	// si la pos del goomba es menor que el offset mas el ancho de la pantalla -> se defrozea
	if (frozen) {
		if (pos.getX() - texture->getFrameWidth() * (TILE_SIDE+5) < game->getMapOffset()) {
			frozen = false; 
		}
	}
	else {
		pos.setX(pos.getX() + speed * dir);
	}


	// caida???
}

void Goomba::checkFrozen()
{
}


