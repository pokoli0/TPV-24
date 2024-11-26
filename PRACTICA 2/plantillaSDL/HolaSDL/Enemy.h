#pragma once
#include "checkML.h"

#include "SceneObject.h"

class Enemy : public SceneObject
{
public:
	Enemy(Game* game, int x, int y, Texture* t);

	//void render(SDL_Renderer* renderer) override {};
	void update() override;

	// Mario está aplastando al goomba o es el goomba el que está hiriendo a 
	// Mario. Habrá que seguir comprobando si Mario viene desde arriba o no 
	virtual Collision hit(const SDL_Rect& region, Collision::Target target) override;
	virtual SceneObject* clone() const override;

	void checkAlive() override;
	virtual void updateAnim() {};

private:
	bool frozen;

};

