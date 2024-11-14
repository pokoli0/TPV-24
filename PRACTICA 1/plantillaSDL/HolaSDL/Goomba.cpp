#include "Goomba.h"

Goomba::Goomba(Game* g, int x, int y)
{
	game = g;
	pos = Point2D<int>(x, y);

	texture = game->getTexture(Game::GOOMBA);

	frameCounter = 0;

	dir = Point2D<int>(-1, 0); //izda
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

	//Collision col = game->checkCollision(rect, false);

	//if (!col) {
	//	// caida
	//	pos.setY(pos.getY() + GRAVITY);
	//}

}

Collision Goomba::hit(const SDL_Rect& rect, bool fromPlayer)
{
	Collision col;
	SDL_Rect arribarect{ pos.getX(), pos.getY() - TILE_SIDE, TILE_SIDE, TILE_SIDE };
	col.collides = SDL_IntersectRect(&rect, &arribarect, &col.intersectionRect);
	if (col)
	{
		if (fromPlayer)
		{
			if (col.intersectionRect.y <= arribarect.y)
			{
				isAlive = false;
			}
			else {
				col.damages = true;
			}
		}
		/*else {
			col.damages = true;
		}*/
	}
	return col;
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
		pos.setX(pos.getX() + speed * dir.getX());
	}
	//colisones
	//SDL_Rect auxrect{ pos.getX(), pos.getY() - TILE_SIDE, TILE_SIDE, TILE_SIDE };
	//Collision col = game->checkCollision(auxrect, false);

	//if (col)
	//{
	//	if (dir.getY() == -1) // si esta bajando
	//	{
	//		pos.setY(pos.getY() - TILE_SIDE / 4 - 1);
	//	}
	//}
	//else {
	//	dir.setY(-1);
	//}
	//if (col)
	//{
	//	if (dir.getX() == 1) // si esta yendo hacia la derecha
	//	{
	//		pos.setX(pos.getX() - TILE_SIDE / 4 - 1);				
	//	}
	//	else if (dir.getX() == -1) // si esta yendo hacia la izquierda
	//	{
	//		pos.setX(pos.getX() + TILE_SIDE / 4 - 1);
	//	}

	//	dir.setX(0);
	//}
 
	// caida???
}

void Goomba::checkFrozen()
{
}


