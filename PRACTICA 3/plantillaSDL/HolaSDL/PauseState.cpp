#include "PauseState.h"
#include <iostream>
#include "MainMenuState.h"
#include "Game.h"

PauseState::PauseState(Game* g)
    : GameState(g)
{
    cout << "Pause State" << endl;
    setupMenu();
}

void PauseState::render(SDL_Renderer* r)
{
    for (auto s : stateList)
        s->render(r);
}

void PauseState::update()
{
    for (auto s : stateList)
        s->update();
}

void PauseState::handleEvent(const SDL_Event& event)
{
    GameState::handleEvent(event);
}

void PauseState::setupMenu()
{
    // Crear y configurar botones
    Button* resumeButton = new Button(this, getGame()->getTexture(Game::RESUME), game->getTexture(Game::MUSHROOM), { 100, 100 });
    resumeButton->connect([this]() {
        game->getStateMachine()->popState();
        });
    Button*MenuButton = new Button(this, getGame()->getTexture(Game::BACK), game->getTexture(Game::MUSHROOM), { 100, 200 });
    MenuButton->connect([this]() {
        GameState* mainMenu = new MainMenuState(game);
        game->getStateMachine()->pushState(mainMenu);
        });
    Button* exitButton = new Button(this, getGame()->getTexture(Game::EXIT), game->getTexture(Game::MUSHROOM), { 100, 300 });
    exitButton->connect([this]() {
        getGame()->endGame();
        });

    // Añadir botones al vector y a las listas del estado
    buttons.push_back(resumeButton);
    buttons.push_back(MenuButton);
    buttons.push_back(exitButton);

    for (Button* button : buttons) {
        addObject(button);
        addEventListener(button);
    }
}
