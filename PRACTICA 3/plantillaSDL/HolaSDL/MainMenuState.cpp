#include "MainMenuState.h"
#include <iostream>
MainMenuState::MainMenuState(Game* g)
    : GameState(g)
{
    setupMenu();
}
void MainMenuState::render() const
{
    getGame()->getTexture(Game::BG)->render();
    GameState::render();
}

void MainMenuState::update()
{
    GameState::update();
}

void MainMenuState::handleEvent(const SDL_Event& event)
{
    GameState::handleEvent(event);
}
void MainMenuState::setupMenu()
{
    // Crear y configurar botones
    Button* startLevel1 = new Button(this,getGame()->getTexture(Game::LVL1), {100, 200});
    startLevel1->connect([this]() {
        //getGame()->getgsMachine()->pushState(new PlayState(game, file, "../assets/maps/world"));
        });

    Button* startLevel2 = new Button(this, getGame()->getTexture(Game::LVL2), { 100, 300 });
    startLevel2->connect([this]() {
        //getGame()->getgsMachine()->pushState(new PlayState(game, file, "../assets/maps/world2"));
        });

    Button* exitButton = new Button(this, getGame()->getTexture(Game::EXIT), { 100, 400 });
    exitButton->connect([this]() {
        getGame()->Quit();
        });

    // Añadir botones al vector y a las listas del estado
    buttons.push_back(startLevel1);
    buttons.push_back(startLevel2);
    buttons.push_back(exitButton);

    for (Button* button : buttons) {
        addObject(button);
        addEventListener(button);
    }
}