#include "Koopa.h"

Koopa::Koopa(Game* g, int x, int y)
{
	game = g;
	pos = Point2D<int>(x, y);

	xSpeed = -6;
	speed = Point2D<int>(xSpeed, 0);

	if (speed.getX() > 0) flip = SDL_FLIP_HORIZONTAL;
	else flip = SDL_FLIP_NONE;

	frame = 0;
	koopaFrame = 0;
	frameCounter = 0;

	onGround = false;
	isAlive = true;

	texture = game->getTexture(Game::KOOPA);
}

void Koopa::render(SDL_Renderer* renderer)
{
	rect.x = pos.getX() - game->getMapOffset();
	rect.y = pos.getY() - TILE_SIDE;
	rect.w = texture->getFrameWidth() * 2;
	rect.h = texture->getFrameHeight() * 2;

	updateAnim();

	texture->renderFrame(rect, 0, frame, 0, nullptr, flip);

	if (DEBUG) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 128);
		SDL_RenderDrawRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}
}

void Koopa::update()
{
	checkAlive();
	if (pos.getX() - texture->getFrameWidth() * (TILE_SIDE + 5) < game->getMapOffset()) {
		frozen = false;
	}
	if (!frozen) {
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

		if (speed.getX() > 0) flip = SDL_FLIP_HORIZONTAL;
		else flip = SDL_FLIP_NONE;


		pos.setX(pos.getX() + speed.getX());

	}
	
}


Collision Koopa::hit(const SDL_Rect& rect, bool fromPlayer)
{
	Collision col;

	SDL_Rect koopaRect{
		pos.getX() + speed.getX(), // se mueve en el mapa asiq ya se aplica el offset en el render
		pos.getY() - TILE_SIDE/2, // para q atraviese un poco el collider
		TILE_SIDE,
		TILE_SIDE
	};

	// si hay colision, devolvemos true
	if (SDL_IntersectRect(&rect, &koopaRect, &col.intersectionRect) && fromPlayer)
	{
		col.collides = true;
	}

	if (col.collides && fromPlayer // si la colision es del player
		&& col.intersectionRect.y <= koopaRect.y // desde arriba
		&& col.intersectionRect.w > TILE_SIDE / 4) // para que no detecte col desde el lado
	{
		isAlive = false;
		cout << "mario col con kopa desde arriba" << endl;
	}
	else if (col.collides && fromPlayer)
	{
		col.damages = true;
		// ?=??¿ quitar vida
		game->Mariohit();
		cout << "mario col damage" << endl;
	}

	return col;
}

void Koopa::updateAnim()
{
	frameCounter++;
	if (frameCounter >= 5)
	{
		frameCounter = 0;
		koopaFrame = (koopaFrame + 1) % 2; // Alterna entre 0 y 1

		if (koopaFrame == 0) {
			frame = 0;
		}
		else if (koopaFrame == 1) {
			frame = 1;
		}
	}

}

void Koopa::checkAlive()
{
	if (pos.getY() >= MAX_HEIGHT || pos.getX() <= 0 ||pos.getX() >= MAX_MAP_OFFSET)
	{
		isAlive = false;
	}
}

