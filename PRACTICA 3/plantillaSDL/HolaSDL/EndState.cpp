#include "EndState.h"
#include <iostream>

#include "Game.h"

EndState::EndState(Game* g, int aux)
    : GameState(g), _aux(aux)
{
    cout << "End State" << endl;
    cout << _aux << endl;
    setupMenu();
}

void EndState::render(SDL_Renderer* r)
{
    if (_aux == 0)
    {
        getGame()->getTexture(Game::LOOSE)->render({ 200, 50, 200, 100 });
    }
    else {
        getGame()->getTexture(Game::WIN)->render({ 200, 50, 200, 100 });
    }

    for (auto s : stateList)
        s->render(r);
}

void EndState::update()
{
    for (auto s : stateList)
        s->update();
}

void EndState::handleEvent(const SDL_Event& event)
{
    GameState::handleEvent(event);
}

void EndState::setupMenu()
{
    // Crear y configurar botones
    Button* volverButton = new Button(this, getGame()->getTexture(Game::BACK), game->getTexture(Game::MUSHROOM), { 100, 200 });
    volverButton->connect([this]() {
        GameState* mainMenu = new MainMenuState(game);
        game->getStateMachine()->pushState(mainMenu);
        });

    Button* exitButton = new Button(this, getGame()->getTexture(Game::EXIT), game->getTexture(Game::MUSHROOM), { 100, 300 });
    exitButton->connect([this]() {
        getGame()->endGame();
        });

    // Añadir botones al vector y a las listas del estado
    buttons.push_back(volverButton);
    buttons.push_back(exitButton);

    for (Button* button : buttons) {
        addObject(button);
        addEventListener(button);
    }
}
