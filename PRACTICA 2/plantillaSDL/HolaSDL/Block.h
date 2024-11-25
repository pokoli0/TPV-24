#pragma once
#include "SceneObject.h"

class Block : public SceneObject
{
public:
	Block(Game* game, int x, int y, char v, char act);

	void render(SDL_Renderer* renderer) override;
	void update() override;

	Collision hit(const SDL_Rect& region, Collision::Target target) override;
	SceneObject* clone() const override;

	void checkAlive() override {};
	void updateAnim() override;

private:
	char variant;
	char action;
	enum AccionBloque {
		POTENCIADOR,
		MONEDA,
		NADA,
	};
	AccionBloque accionBloque;
	int surpriseFrame;
};

