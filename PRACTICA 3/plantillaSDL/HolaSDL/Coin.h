#pragma once
#include "Pickable.h"

class Coin : public Pickable
{
public:
	Coin(Game* game, PlayState* s, int x, int y);

	void render(SDL_Renderer* renderer) override;
	void update() override;

	Collision hit(const SDL_Rect& region, Collision::Target target) override;
	SceneObject* clone() const override;

	void updateAnim() override;
	void triggerAction() override;

private:
	int coinFrame;
};
