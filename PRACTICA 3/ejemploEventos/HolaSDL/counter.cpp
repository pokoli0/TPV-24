#include "checkML.h"
#include "counter.h"

Counter::Counter(Game* game)
 : game(game)
 , counter(0)
{
	// Por simplicidad, cargamos la textura en la propia clase
	texture = new Texture(game->getRenderer(), "../../images/numbers.png", 1, 10);

	// Se registra para recibir eventos de teclado (r resetea el contador)
	// ([this] significa que la expresión lambda captura el this de Counter)
	game->connect([this](const SDL_Event& event) {
		// Si se ha pulado la tecla r pone el contador a cero
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r)
			counter = 0;
	});
}

Counter::~Counter()
{
	delete texture;
}

void
Counter::render() const
{
	SDL_Rect target{720, 50, 50, 50};

	// Pinta el contador con la textura de los números
	int num = counter;

	while (num > 0) {
		texture->renderFrame(target, 0, num % 10);
		target.x -= 60;
		num /= 10;
	}
}

void
Counter::handleClick()
{
	// Incremental el contador que se muestra
	++counter;
}

