#pragma once
#include "GameState.h"
#include "Button.h"
#include <vector>

class PauseState : public GameState
{
public:
    PauseState(Game* g);
    virtual ~PauseState() = default;

    void render() const override;
    void update() override;
    void handleEvent(const SDL_Event& event) override;

private:
    void setupMenu();
    std::vector<Button*> buttons;
};
