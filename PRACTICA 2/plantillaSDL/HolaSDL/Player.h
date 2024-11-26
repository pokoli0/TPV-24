#pragma once
#include "checkML.h"

#include "SceneObject.h"

class Player : public SceneObject
{
public:
	Player(Game* game, int x, int y);

	void render(SDL_Renderer* renderer) override;
	void update() override;

	Collision hit(const SDL_Rect& region, Collision::Target target) override;
	SceneObject* clone() const override;

	void hit();

	void checkAlive() override;

	void resetPlayer();
	void updateAnim() override;
	void jump();

	int getLives() { return lives; }
	void setLives(int n) { lives = n; }

	void handleEvent(SDL_Event e);

	bool getImmunity() { return immune; }


private:
	int lives;
	bool immune;

	int temp = 0;
	int immuneTime = 50;

	int marioSpeed;
	bool onGround, jumping;

	int walkFrame;

	Point2D<double> initPos;

};

