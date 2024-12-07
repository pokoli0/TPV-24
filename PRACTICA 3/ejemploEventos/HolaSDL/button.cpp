#include "checkML.h"
#include "button.h"
#include "method.h"

Button::Button(Game* game) 
  : game(game)
  , boundingBox{50, 50, 200, 100}
{
	// Conectamos el handleEvent con el Game

	// (1) Con expresión lambda (véase Counter)
	game->connect([this](auto event) { handleEvent(event); });
	// (2) Con bind_front (C++20)
	// game->connect(std::bind_front(&Button::handleEvent, this));
	// (3) Con bind (C++11), pero hay que utilizar std::placeholders
	// game->connect(std::bind(&Button::handleEvent, this, std::placeholders::_1));
	// (4) Con el envoltorio de métodos de method.h
	// game->connect(Method(&Button::handleEvent, this));
}

void 
Button::addClickListener(ButtonListener* lis)
{
	clickListeners.push_back(lis);
}

void
Button::update()
{
	SDL_Point point;
	SDL_GetMouseState(&point.x, &point.y);

	// Comprueba si el ratón está sobre el rectángulo
	hover = SDL_PointInRect(&point, &boundingBox);
}

void
Button::render() const
{
	// Fija el color del rectángulo dependiendo de si el ratón está sobre él
	int r = 0, b = 255;

	if (hover) std::swap(r, b);

	SDL_SetRenderDrawColor(game->getRenderer(), r, 0, b, 225);

	// Rellena el rectángulo con el color fijado
	SDL_RenderFillRect(game->getRenderer(), &boundingBox);

	// Restablece el color de fondo (para el SDL_RenderClear)
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 225);
}

void
Button::handleEvent(const SDL_Event& event)
{
	// Evento de pulsación de un botón del ratón (y botón izquierdo)
	// (véase https://wiki.libsdl.org/SDL2/SDL_MouseButtonEvent)
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		// Posición del ratón cuando se pulsó
		SDL_Point point{event.button.x, event.button.y};

		// Función que comprueba si un punto está en un rectángulo
		// (véase https://wiki.libsdl.org/SDL2/SDL_PointInRect)
		if (SDL_PointInRect(&point, &boundingBox))
			emit();
	}
}

void
Button::emit() const
{
	// Llama al método virtual handleClick de cada oyente
	for (ButtonListener* lis : clickListeners)
		lis->handleClick();
}
