#pragma once
#include "SceneObject.h"

class Player : public SceneObject
{

public:
	Player(Game* game, int x, int y);

	void render(SDL_Renderer* renderer) const override;
	void update() override;
	Collision hit(const SDL_Rect& region, Collision::Target target) override;
	SceneObject* clone() const override;

	void updateAnim();

	int getLives() { return lives; }
	void setLives(int n) { lives = n; }

	void isSupermario();
	void handleEvent(SDL_Event e);

private:
	int lives;
	bool immune;

	bool onGround, jumping;

	int frame, walkFrame, frameCounter;
	bool flipSprite;
	SDL_RendererFlip flip;

	// background speed multiplier para el debug mode
	int bgSpeed;
};

