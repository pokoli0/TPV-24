#pragma once
#include "checkML.h"

#include "SceneObject.h"

class Enemy : public SceneObject
{
public:
	Enemy(Game* game, int x, int y, Texture* t);

	//void render(SDL_Renderer* renderer) override {};
	void update() override;

	// Mario est� aplastando al goomba o es el goomba el que est� hiriendo a 
	// Mario. Habr� que seguir comprobando si Mario viene desde arriba o no 
	virtual Collision hit(const SDL_Rect& region, Collision::Target target) override;
	virtual SceneObject* clone() const override;

	void checkAlive() override;
	virtual void updateAnim() {};

private:
	bool frozen;

};

