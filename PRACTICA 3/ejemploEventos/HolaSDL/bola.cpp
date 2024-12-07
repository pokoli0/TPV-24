#include "checkML.h"
#include "bola.h"

using namespace std;

Bola::Bola(Game* game) 
  : game(game)
  , boundingBox{0, 0, 70, 70} // mejor no poner números fijos
  , parada(false)
{
	// Por simplicidad, cargamos la textura en la propia clase
	texture = new Texture(game->getRenderer(), "../../images/bola.png", 1, 1);
}

Bola::~Bola()
{
	// Como hemos cargado la textura aquí tenemos que borrarla aquí
	delete texture;
}

void
Bola::update()
{
	// Mueve la bola al cursor si no está parada
	if (!parada) {
		int x, y;

		// Esta función obtiene la posición del ratón
		// (véase https://wiki.libsdl.org/SDL2/SDL_GetMouseState)
		SDL_GetMouseState(&x, &y);

		// Centramos la bola en el cursor
		boundingBox.x = x - boundingBox.w / 2;
		boundingBox.y = y - boundingBox.h / 2;
	}
}

void
Bola::render() const
{
	texture->render(boundingBox);
}

void
Bola::handleClick() {
	// La bola se para o reactiva cuando se hace click en el botón
	parada = !parada;
}
