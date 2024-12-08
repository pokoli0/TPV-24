#include "MainMenuState.h"
#include <iostream>

#include "Game.h"
#include "PlayState.h"

MainMenuState::MainMenuState(Game* g)
    : GameState(g)
{
    cout << "MainMenu State" << endl;

    setupMenu();
}
void MainMenuState::render(SDL_Renderer* r)
{
    getGame()->getTexture(Game::BG)->render();

    for (auto s : stateList) 
        s->render(r);
}

void MainMenuState::update()
{
    for (auto s : stateList)
        s->update();
}

void MainMenuState::setupMenu()
{
    // Crear y configurar botones
    Button* startLevel1 = new Button(this, game->getTexture(Game::LVL1), {100, 200});
    Button* startLevel2 = new Button(this, game->getTexture(Game::LVL2), { 100, 300 });
    Button* exitButton = new Button(this, game->getTexture(Game::EXIT), { 100, 400 });

    startLevel1->connect([this]() { loadLevel(1); });
    startLevel2->connect([this]() { loadLevel(2); });
    exitButton->connect([this]() { game->endGame(); });

    // Añadir botones al vector y a las listas del estado
    buttons.push_back(startLevel1);
    buttons.push_back(startLevel2);
    buttons.push_back(exitButton);

    for (Button* button : buttons) {
        addObject(button);
        addEventListener(button);
    }
}

void MainMenuState::loadLevel(int n)
{
    GameState* playS = new PlayState(game, n);

    game->getStateMachine()->pushState(playS);
}
