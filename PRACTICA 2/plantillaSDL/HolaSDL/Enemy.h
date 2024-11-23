#pragma once
#include "SceneObject.h"

class Enemy : public SceneObject
{
public:
	Enemy(Game* game, int x, int y, Texture* t);

	virtual void render(SDL_Renderer* renderer) override;
	void update() override {};

	virtual Collision hit(const SDL_Rect& region, Collision::Target target) override;
	virtual SceneObject* clone() const override;

	void checkAlive() override {};


private:

};

