#pragma once
#include "checkML.h"

#include "Enemy.h"

class Koopa : public Enemy
{
public:
	Koopa(Game* game, int x, int y);

	void render(SDL_Renderer* renderer) override;

	Collision hit(const SDL_Rect& region, Collision::Target target) override;
	SceneObject* clone() const override;

	void updateAnim() override;

private:

	int koopaFrame;
};
