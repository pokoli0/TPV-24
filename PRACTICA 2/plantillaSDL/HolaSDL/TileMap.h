#pragma once
#include "SceneObject.h"

class TileMap : public SceneObject
{
public:
	TileMap();

	void render(SDL_Renderer* renderer) const override;
	void update() const override;

};


