#ifndef BUTTON_H
#define BUTTON_H

#include <functional>

#include "GameObject.h"
#include "EventHandler.h"

#include "GameState.h"

// alias
using Callback = std::function<void(void)>;

class Button : public GameObject, public EventHandler
{
public:
	Button(GameState* gameState, Texture* texture, Texture* texture2, Point2D<double> pos);

	// Metodos de GameObject
	void render(SDL_Renderer* renderer) override;
	void update() override;

	// Metodo de EventHandler
	void handleEvent(const SDL_Event& event) override;

	// registra callback
	void connect(const Callback& c);

private:
	Texture* texture;
	Texture* mushroomTexture;
	SDL_Rect mushRect;
	Point2D<double> position;

	// estados del boton para render y animacion
	int currentFrame;
	enum buttonState {
		DEFAULT = 0, 
		OVER = 1, // cuando el raton este sobre el rect
		CLICK = 2 // cuando el raton haga click
	};

	// lista de funciones a ejecutar
	std::list<Callback> callbacks;

	SDL_Point point; // posicion del click
	SDL_Rect rect;

	void emit() const;
};

#endif