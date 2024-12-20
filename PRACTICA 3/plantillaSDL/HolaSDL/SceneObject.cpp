#include "checkML.h"

#include "SceneObject.h"
#include "Game.h"
#include "PlayState.h"

SceneObject::SceneObject(Game* game, PlayState* state, int x, int y, int width, int height, Texture* texture)
    : GameObject(game), _position(x, y), _width(width), _height(height), _scale(1),
    _speed(0, 0), _texture(texture), _isAlive(true), _rect(),
    _frame(0), _frameCounter(0), _playState(state)
{
}

void SceneObject::render(SDL_Renderer* renderer)
{
    _rect.x = _position.getX() - _playState->getMapOffset();
    _rect.y = _position.getY() - _height;
    _rect.w = _texture->getFrameWidth() * _scale;
    _rect.h = _texture->getFrameHeight() * _scale;

    _texture->renderFrame(_rect, 0, _frame, 0, nullptr, _flip);

    SDL_Rect r = getCollisionRect();
    if (DEBUG) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 128);
        SDL_RenderDrawRect(renderer, &r);
        SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
    }
}

SDL_Rect SceneObject::getCollisionRect() const
{
    return SDL_Rect{
        (int)_position.getX(),
        (int)_position.getY() - _height,
        _width,
        _height
    };
}

bool SceneObject::getAlive() const
{
    return _isAlive;
}

SDL_Rect SceneObject::getRenderRect() const
{
    return SDL_Rect{
        (int)_position.getX() - _playState->getMapOffset(),
        (int)_position.getY() - _height,
        _width,
        _height
    };
}

Collision SceneObject::tryToMove(const Vector2D<int>& speed, Collision::Target target)
{
    // Enunciado
    Collision collision;
    SDL_Rect rect = getCollisionRect();

    // Movimiento vertical
    if (speed.getY() != 0) {
        rect.y += speed.getY();
        collision = _playState->checkCollision(rect, target);
        
        // Cantidad que se ha entrado en el obst�culo (lo que hay que deshacer)
        int fix = collision.vertical * (speed.getY() > 0 ? 1 : -1);
        _position.setY(_position.getY() + speed.getY() - fix);

        rect.y -= fix; // recoloca la caja para la siguiente colisi�n
    }

    collision.horizontal = 0;

    // Intenta moverse en horizontal
    // (podr�a ser conveniente comprobar colisiones incluso aunque el objeto estuviera parado)
    if (speed.getX() != 0) {
        rect.x += speed.getX();

        Collision partial = _playState->checkCollision(rect, target);

        // Copia la informaci�n de esta colisi�n a la que se devolver�
        collision.horizontal = partial.horizontal;

        if (partial.result == Collision::DAMAGE)
            collision.result = Collision::DAMAGE;

        _position.setX(_position.getX() + speed.getX() - collision.horizontal * (speed.getX() > 0 ? 1 : -1));
    }

    return collision;
}
