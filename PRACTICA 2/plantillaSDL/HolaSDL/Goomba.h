#pragma once
#include "Enemy.h"

class Goomba : public Enemy
{
public:
	Goomba(Game* game, int x, int y, Texture* t);

	void render(SDL_Renderer* renderer) override;
	void update() override;

	Collision hit(const SDL_Rect& region, Collision::Target target) override;
	SceneObject* clone() const override;


private:

};

