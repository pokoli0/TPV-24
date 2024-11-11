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
		frame = 3;
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


