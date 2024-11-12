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
	isAlive = true;
}

void Block::render()
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

	texture->renderFrame(rect, 0, frame);
}

void Block::update()
{
	if (tipoBloque == SORPRESA)
	{
		frameTimer++;
		if (frameTimer >= 1050) {  // Velocidad del ciclo
			frameTimer = 0;
			frameCounter = (frameCounter + 1) % 3;  // Ciclo 0,1,2,3, y luego se reinicie 

			if (frameCounter == 0) frame = 1;
			else if (frameCounter == 1) frame = 2;
			else if (frameCounter == 2) frame = 0;
		}
	}

	rect.x = pos.getX();
	rect.y = pos.getY();
	rect.h = TILE_SIDE;
	rect.w = TILE_SIDE;

	texture->renderFrame(rect, 0, frame);
}

Collision Block::hit(const SDL_Rect& rect, bool fromPlayer)
{
	// El bloque sera obstaculo si se choca desde arriba o lateral.
	// Si Mario toca desde abajo:
	//    - Si es tipo LADRILLO y Mario es GRANDE el bloque se destruye.
	//    - Si es tipo SORPRESA/OCULTO, Mario es GRANDE y la accion es POTENCIADOR, aparece un Superchampi y lo convierte en tipo VACIO.

	Collision col;
	SDL_Rect blockRect { pos.getX(), pos.getY(), texture->getFrameWidth(), texture->getFrameHeight()};

	col.collides = SDL_IntersectRect(&rect, &blockRect, &col.rect);

	// si hay colision y es del jugador y la colision es desde abajo
	if (col && fromPlayer && 
		col.rect.y > blockRect.y + texture->getFrameHeight() / 4 && 
		col.rect.w > texture->getFrameWidth() / 4)
	{
		if (tipoBloque == SORPRESA || tipoBloque == OCULTO) 
		{
			tipoBloque = VACIO;
			if (accionBloque == POTENCIADOR) {
				//game->addMushroom(pos);
			}
		}

		// si es un bloque de ladrillos y somos supermario, lo destruye
		//if (tipoBloque == LADRILLO && player->getAspect() == 1) {
		//	isAlive = false;
		//}
	}
	return col;
}


