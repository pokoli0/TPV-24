#pragma once
#include "SceneObject.h"

class Pickable : public SceneObject
{
public:
	Pickable(Game* game, int x, int y, Texture* t);

	void update() override;

	virtual Collision hit(const SDL_Rect& region, Collision::Target target) override;
	virtual SceneObject* clone() const override;

	void checkAlive() override {};
	virtual void updateAnim() override;

	// pone alive a false
	virtual void triggerAction();

private:

};