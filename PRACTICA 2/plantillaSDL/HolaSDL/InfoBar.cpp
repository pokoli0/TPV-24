#include "InfoBar.h"

InfoBar::InfoBar(Game* game, Texture* t)
    : GameObject(game), _texture(t), _position(0, 0), _width(_texture->getFrameWidth()), _height(_texture->getFrameHeight()), 
    _scale(1), _speed(0, 0), _isAlive(true), _rect(),
    _frame(0), _frameCounter(0)
{
}


void InfoBar::render(SDL_Renderer* renderer)
{
    _rect.x = _position.getX();
    _rect.y = _position.getY();
    _rect.w = _width * _scale;
    _rect.h = _height * _scale;

    _texture->renderFrame(_rect, 0, _frame);
}

void InfoBar::update()
{
}
