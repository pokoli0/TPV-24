#pragma once
#include "GameState.h"
#include "Button.h"
#include <vector>
#include "MainMenuState.h"
class EndState : public GameState
{
public:
    EndState(Game* g, int aux);
    virtual ~EndState() = default;

    void render(SDL_Renderer* r) override;
    void update() override;
    void handleEvent(const SDL_Event& event) override;

private:
    void setupMenu();
    std::vector<Button*> buttons;
    int _aux = NULL;
};

