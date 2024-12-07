#include "game.h"
#include "button.h"
#include "texture.h"

/**
 * Contador que se subscribe al botón.
 */
class Counter : public ButtonListener {
	Game* game;
	Texture* texture;
	int counter;

public:
	Counter(Game* game);
	~Counter();

	void render() const;
	void handleClick() override;
};
