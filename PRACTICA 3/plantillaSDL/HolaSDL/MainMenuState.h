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
	void handleEvent(const SDL_Event& event) override;

private:

	void setupMenu();
	std::vector<Button*> buttons;
};

