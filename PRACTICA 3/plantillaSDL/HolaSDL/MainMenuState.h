#pragma once
#include "GameState.h"
#include "Button.h"
#include <vector>
class MainMenuState : public GameState
{
public:
	MainMenuState(Game* g);
	virtual ~MainMenuState() = default;

	void render(SDL_Renderer* r) override;
	void update() override;

private:
	void setupMenu();

	// callbacks
	void loadLevel();
	void exit();

	std::vector<Button*> buttons;
};

