#pragma once
#include "SceneObject.h"
#include <vector>

using namespace std;

class TileMap : public SceneObject
{
public:
	TileMap(Game* game, int x, int y, int width, int height) 
		: SceneObject(game, x, y, width, height) {}

	void render(SDL_Renderer* renderer) const override;
	void update() override;

	Collision hit(const SDL_Rect& region, Collision::Target target) override;
	
private:
	vector<vector<int>> matrix;

};


