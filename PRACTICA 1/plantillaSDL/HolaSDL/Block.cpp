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
	cout << "Bloque " << x << ", " << y << "," << tipo << "," << accion << endl;
}

void Block::render()
{
	SDL_Rect rect;
	rect.x = pos.getX();
	rect.y = pos.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();

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

void Block::hit()
{
	// El bloque sera obstaculo si se choca desde arriba o lateral.
	// Si Mario toca desde abajo:
	//    - Si es tipo LADRILLO y Mario es GRANDE el bloque se destruye.
	//    - Si es tipo SORPRESA/OCULTO, Mario es GRANDE y la accion es POTENCIADOR, aparece un Superchampi y lo convierte en tipo VACIO.
}
