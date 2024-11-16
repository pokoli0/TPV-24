#include "Mushroom.h"

Mushroom::Mushroom()
{
}

Mushroom::Mushroom(Game* g, int x, int y)
{
	game = g;
	pos = Point2D<int>(x, y - TILE_SIDE);

	xSpeed = -6;
	speed = Point2D<int>(xSpeed, 0);

	onGround = false;
	isAlive = true;

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
	checkAlive();

	// Caida por gravedad
	speed.setY(speed.getY() + GRAVITY);

	// Colisiones verticales
	SDL_Rect verticalRect;
	verticalRect.x = rect.x + game->getMapOffset();
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
		if (speed.getY() > 0)
		{
			pos.setY(pos.getY() + speed.getY() - col.intersectionRect.h);
			onGround = true;

		}
		speed.setY(0);
	}

	// Colisiones horizontales
	SDL_Rect horizontalRect;
	horizontalRect.x = rect.x + speed.getX() + game->getMapOffset();
	horizontalRect.y = rect.y;
	horizontalRect.h = rect.h;
	horizontalRect.w = rect.w;

	col = game->checkCollision(horizontalRect, false);

	if(col) 
	{
		speed.setX(speed.getX() * -1);
	}

	pos.setX(pos.getX() + speed.getX());

}

Collision Mushroom::hit(const SDL_Rect& rect, bool fromPlayer)
{
	Collision col;

	SDL_Rect mushRect{
		pos.getX() + speed.getX(), // se mueve en el mapa asiq ya se aplica el offset en el render
		pos.getY(),
		TILE_SIDE,
		TILE_SIDE
	};

	// si hay colision, devolvemos true
	if (SDL_IntersectRect(&rect, &mushRect, &col.intersectionRect) && fromPlayer)
	{
		col.collides = true;
	}

	if (col.collides && fromPlayer) // si la colision es del player
	{
		if (game->getMarioState() == 0) 
		{
			game->setMarioState(1);
		}
		isAlive = false;
	}

	return col;
}

void Mushroom::checkAlive()
{
	if (pos.getY() >= MAX_HEIGHT || pos.getX() <= 0) 
	{
		isAlive = false;
	}
}
