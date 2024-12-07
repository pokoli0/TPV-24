#pragma once
#include "checkML.h"

#include "SceneObject.h"

class Pickable : public SceneObject
{
public:
	Pickable(Game* game, PlayState* s, int x, int y, Texture* t);

	void update() override;

	virtual Collision hit(const SDL_Rect& region, Collision::Target target) override;
	virtual SceneObject* clone() const override;

	void checkAlive() override {};
	virtual void updateAnim() override;

protected:
	
	// llama a delete this , y hace accion correspondiente
	virtual void triggerAction() = 0;
};