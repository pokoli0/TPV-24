#pragma once
#include "checkML.h"

#include "Pickable.h"

class Mushroom : public Pickable
{
public:
	Mushroom(Game* game, int x, int y);

	void render(SDL_Renderer* renderer) override;
	void update() override;

	Collision hit(const SDL_Rect& region, Collision::Target target) override;
	SceneObject* clone() const override;

	void updateAnim() override {};

	void triggerAction() override;
private:

};
