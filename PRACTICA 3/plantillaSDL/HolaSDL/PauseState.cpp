#include "PauseState.h"
#include <iostream>

#include "Game.h"

PauseState::PauseState(Game* g)
    : GameState(g)
{
    setupMenu();
}

void PauseState::render(SDL_Renderer* r)
{
    GameState::render(r);
}

void PauseState::update()
{
    GameState::update();
}

void PauseState::handleEvent(const SDL_Event& event)
{
    GameState::handleEvent(event);
}

void PauseState::setupMenu()
{
    // Crear y configurar botones
    Button* resumeButton = new Button(this, getGame()->getTexture(Game::RESUME), { 100, 200 });
    resumeButton->connect([this]() {
        //getGame()->getgsMachine()->popState(); // Vuelve al estado anterior
        });
    Button*MenuButton = new Button(this, getGame()->getTexture(Game::BACK), { 100, 200 });
    resumeButton->connect([this]() {
        //game->getgsMachine()->replaceState(new MainMenuState(game));
        });
    Button* exitButton = new Button(this, getGame()->getTexture(Game::EXIT), { 100, 300 });
    exitButton->connect([this]() {
        getGame()->endGame();
        });

    // Añadir botones al vector y a las listas del estado
    buttons.push_back(resumeButton);
    buttons.push_back(exitButton);

    for (Button* button : buttons) {
        addObject(button);
        addEventListener(button);
    }
}
