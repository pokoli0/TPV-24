#ifndef BUTTON_H
#define BUTTON_H

#include "game.h"
#include <vector>

/*
 * Oyente de eventos del botón (click).
 */
class ButtonListener {
public:
	virtual void handleClick() = 0;
};

/**
 * Botón que emite eventos con ButtonListener.
 */
class Button {
	Game* game;
	SDL_Rect boundingBox;
	bool hover;

	std::vector<ButtonListener*> clickListeners;  // lista de oyentes
	void emit() const;  // transmite el evento de click a todos los oyentes
public:
	Button(Game* game);

	void update();
	void render() const;
	void handleEvent(const SDL_Event& event);

	// Añade un oyente del evento de click
	void addClickListener(ButtonListener* lis);
};

#endif
