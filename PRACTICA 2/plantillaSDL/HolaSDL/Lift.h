#pragma once
#include "SceneObject.h"

class Lift : public SceneObject
{
public:
	Lift(Game* game, int x, int y, int speed);


	void update() override;

	Collision hit(const SDL_Rect& region, Collision::Target target) override;
	SceneObject* clone() const override;

	void checkAlive() override {};
	void updateAnim() override {};

private:

};

