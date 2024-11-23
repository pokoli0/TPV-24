#pragma once
#include "SceneObject.h"

class Player : public SceneObject
{

public:
	Player(Game* game, int x, int y);

	void update() override;

	Collision hit(const SDL_Rect& region, Collision::Target target) override;
	SceneObject* clone() const override;

	void checkAlive() override;

	void resetPlayer();
	void updateAnim() override;
	void jump();

	int getLives() { return lives; }
	void setLives(int n) { lives = n; }

	void isSupermario();
	void handleEvent(SDL_Event e);

	void debug();

private:
	int lives;
	bool immune;

	int marioSpeed;
	bool onGround, jumping;

	int walkFrame;


	// background speed multiplier para el debug mode
	int bgSpeed;
	bool debugMode, fastMode;
};

