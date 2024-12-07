#pragma once
#include "checkML.h"

#include "SceneObject.h"

using namespace std;

class TileMap : public SceneObject
{
public:
	TileMap(Game* game, PlayState* s, const string& mapFile, int x = 0, int y = 0);

	void render(SDL_Renderer* renderer) override;
	void update() override;

	Collision hit(const SDL_Rect& region, Collision::Target target) override;

	// para cuando se reinicie el nivel (el tilemap no hace falta reiniciarlo)
	SceneObject* clone() const override;

	void checkAlive() override {};
	void updateAnim() override {};

	void loadTilemap(string fichero);
	
private:
	vector<vector<int>> matrix;

};


