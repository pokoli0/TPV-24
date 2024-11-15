#include "Block.h"

Block::Block(Game* g, int x, int y, char tipo, char accion)
{
	game = g;
	pos = Point2D<int>(x, y);

	switch (tipo) {
	case '?':
		tipoBloque = SORPRESA;
		break;
	case 'B':
		tipoBloque = LADRILLO;
		break;
	case 'H':
		tipoBloque = OCULTO;
		break;
	}

	switch (accion) {
	case 'C':
		accionBloque = MONEDA;
		break;
	case 'P':
		accionBloque = POTENCIADOR;
		break;
	default:
		accionBloque = NADA;
		break;
	}

	texture = game->getTexture(Game::BLOCKS);

	frameCounter = 0;
	surpriseFrame = 0;

	isAlive = true;
}

void Block::render(SDL_Renderer* renderer)
{
	rect.x = pos.getX() - game->getMapOffset();
	rect.y = pos.getY();
	rect.w = TILE_SIDE;
	rect.h = TILE_SIDE;

	// columna 0 - frame 0
	switch (tipoBloque) {
	case SORPRESA:
		frame = 0;
		break;
	case LADRILLO:
		frame = 5;
		break;
	case OCULTO:
		frame = 7;
		break;
	case VACIO:
		frame = 4;
		break;
	}

	if (tipoBloque == SORPRESA) 
	{
		updateAnim();
	}

	texture->renderFrame(rect, 0, frame);



	if (DEBUG) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 128, 128);
		SDL_RenderDrawRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}
}

void Block::update()
{

}

Collision Block::hit(const SDL_Rect& rect, bool fromPlayer)
{
	Collision col;

	SDL_Rect blockRect { 
		pos.getX() - game->getMapOffset(), 
		pos.getY(), 
		TILE_SIDE, 
		TILE_SIDE
	};

	// si hay colision, devolvemos true
	if (SDL_IntersectRect(&rect, &blockRect, &col.intersectionRect))
	{
		col.collides = true;
		cout << "block col" << endl;
	}

	return col;
}

void Block::updateAnim()
{
	frameCounter++;
	if (frameCounter >= 5)
	{
		frameCounter = 0;
		surpriseFrame = (surpriseFrame + 1) % 4; // para que se repita el ciclo

		if (surpriseFrame == 0) {
			frame = 1;
		}
		else if (surpriseFrame == 1) {
			frame = 2;
		}
		else if (surpriseFrame == 2) {
			frame = 3;
		}
		else if (surpriseFrame == 3) {
			frame = 0;
		}
	}
}



