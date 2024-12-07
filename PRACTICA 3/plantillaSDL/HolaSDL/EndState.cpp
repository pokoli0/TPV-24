#include "EndState.h"
#include <iostream>

EndState::EndState(Game* g)
    : GameState(g)
{
    setupMenu();
}

void EndState::render() const
{
    //poner si has ganado o no
    GameState::render();
}

void EndState::update()
{
    GameState::update();
}

void EndState::handleEvent(const SDL_Event& event)
{
    GameState::handleEvent(event);
}

void EndState::setupMenu()
{
    // Crear y configurar botones
    Button* volverButton = new Button(this, getGame()->getTexture(Game::BACK), { 100, 200 });
    volverButton->connect([this]() {
        //getGame()->getgsMachine()->changeState(new MainMenuState(getGame())); // Cambia al menú principal
        });

    Button* exitButton = new Button(this, getGame()->getTexture(Game::EXIT), { 100, 300 });
    exitButton->connect([this]() {
        getGame()->Quit();
        });

    // Añadir botones al vector y a las listas del estado
    buttons.push_back(volverButton);
    buttons.push_back(exitButton);

    for (Button* button : buttons) {
        addObject(button);
        addEventListener(button);
    }
}
