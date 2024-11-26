#include "Mushroom.h"
#include "Game.h"

Mushroom::Mushroom(Game* game, int x, int y)
	: Pickable(game, x, y, game->getTexture(Game::MUSHROOM))
{
}

void Mushroom::render(SDL_Renderer* renderer)
{
	Pickable::render(renderer);
}

void Mushroom::update()
{

}

Collision Mushroom::hit(const SDL_Rect& region, Collision::Target target)
{
	return Pickable::hit(region,target);
}

SceneObject* Mushroom::clone() const
{
	return nullptr;
}

void Mushroom::triggerAction()
{
	game->setMarioState(1);
	game->givePoints(1000);
	cout << "Points: " << game->getPoints() << endl;
	delete this;
}
