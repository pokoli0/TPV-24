#pragma once
#include "checkML.h"

#include "SceneObject.h"

class TileMap : public SceneObject
{
public:
	TileMap(Game* game, PlayState* s, const std::string& mapFile, int x = 0, int y = 0);

	void render(SDL_Renderer* renderer) override;
	void update() override;

	Collision hit(const SDL_Rect& region, Collision::Target target) override;

	// para cuando se reinicie el nivel (el tilemap no hace falta reiniciarlo)
	SceneObject* clone() const override;

	void checkAlive() override {};
	void updateAnim() override {};

	void loadTilemap(std::string fichero);
	
private:
	std::vector<std::vector<int>> matrix;

};


