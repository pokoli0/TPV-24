#include "Mushroom.h"

Mushroom::Mushroom()
{
}

Mushroom::Mushroom(Game* g, int x, int y)
{
	game = g;
	pos = Point2D<int>(500, 100);

	xSpeed = 6;
	speed = Point2D<int>(xSpeed, 0);

	onGround = false;

	texture = game->getTexture(Game::MUSHROOM);
}

void Mushroom::render(SDL_Renderer* renderer)
{
	rect.x = pos.getX() - game->getMapOffset();
	rect.y = pos.getY();
	rect.w = TILE_SIDE;
	rect.h = TILE_SIDE;

	texture->renderFrame(rect, 0, 0);

	if (DEBUG) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 128);
		SDL_RenderDrawRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}
}

void Mushroom::update()
{
	// Caida por gravedad
	speed.setY(speed.getY() + GRAVITY);

	// Colisiones verticales
	SDL_Rect verticalRect;
	verticalRect.x = rect.x;
	verticalRect.y = rect.y + speed.getY();
	verticalRect.h = rect.h;
	verticalRect.w = rect.w;

	Collision col = game->checkCollision(verticalRect, false);


	if (!col) // si no hay col, cae normal
	{
		pos.setY(pos.getY() + speed.getY());
		onGround = false;
	}
	else 
	{
		onGround = true;
		speed.setY(0);
	}

	// Colisiones horizontales
	SDL_Rect horizontalRect;
	horizontalRect.x = rect.x + speed.getX();
	horizontalRect.y = rect.y;
	horizontalRect.h = rect.h;
	horizontalRect.w = rect.w;

	col = game->checkCollision(horizontalRect, true);

	if(col) 
	{
		if (speed.getX() > 0)
		{
			pos.setX(pos.getX() - col.intersectionRect.w / game->getMapOffset() - 1);
		}
		else
		{
			pos.setX(pos.getX() + col.intersectionRect.w / game->getMapOffset() - 1);
		}
		speed.setX(speed.getY() * -1);
	}

	pos.setX(pos.getX() + speed.getX());

}

Collision Mushroom::hit(const SDL_Rect& rect, bool fromPlayer)
{
	Collision col;

	//SDL_Rect mushRect{
	//	pos.getX() - game->getMapOffset(),
	//	pos.getY(),
	//	TILE_SIDE,
	//	TILE_SIDE
	//};

	//// si hay colision, devolvemos true
	//if (SDL_IntersectRect(&rect, &mushRect, &col.intersectionRect))
	//{
	//	col.collides = true;
	//}

	//if (col && fromPlayer)// si la colision es del player
	//{
	//	cout << "mario col con mush" << endl;
	//}



	return col;
}

void Mushroom::move()
{
	
}
