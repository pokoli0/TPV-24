#include "Goomba.h"

Goomba::Goomba(Game* g, int x, int y)
{
	game = g;
	pos = Point2D<int>(x, y);

	xSpeed = -6;
	speed = Point2D<int>(xSpeed, 0);

	onGround = false;

	texture = game->getTexture(Game::GOOMBA);

	frame = 0;
	frameCounter = 0;

	frozen = true;

	//cout << "Goomba (" << x << ", " << y << ")" << endl;
}

void Goomba::render(SDL_Renderer* renderer)
{
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

	if (DEBUG) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 128);
		SDL_RenderDrawRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}
}

void Goomba::update()
{
	
	if (pos.getX() - texture->getFrameWidth() * (TILE_SIDE + 5) < game->getMapOffset()) {
		frozen = false;
	}
	if (!frozen)
	{
		Alive();
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

		if (col)
		{
			speed.setX(speed.getX() * -1);
		}

		pos.setX(pos.getX() + speed.getX());


	}
	
}

Collision Goomba::hit(const SDL_Rect& rect, bool fromPlayer)
{
	Collision col;

	SDL_Rect GoombaRect{
		pos.getX() + speed.getX(), // se mueve en el mapa asiq ya se aplica el offset en el render
		pos.getY() - TILE_SIDE , // para q atraviese un poco el collider
		TILE_SIDE,
		TILE_SIDE
	};

	// si hay colision, devolvemos true
	if (SDL_IntersectRect(&rect, &GoombaRect, &col.intersectionRect) && fromPlayer)
	{
		col.collides = true;
	}

	if (col.collides && fromPlayer // si la colision es del player
		&& col.intersectionRect.y <= GoombaRect.y // desde arriba
		&& col.intersectionRect.w > TILE_SIDE / 4) // para que no detecte col desde el lado
	{
		isAlive = false;
	}
	else if (col.collides && fromPlayer)
	{
		col.damages = true;
		// ?=??� quitar vida
		//game->Mariohit();
		cout << "mario col damage" << endl;
	}

	return col;
}
void Goomba::Alive() {
	if (pos.getY() >= MAX_HEIGHT || pos.getX() <= 0 || pos.getX() >= MAX_MAP_OFFSET)
	{
		isAlive = false;
	}
}
