#include "SceneObject.h"
#include "Game.h"

SceneObject::SceneObject(Game* game, int x, int y, int width, int height, Texture* texture)
    : GameObject(game), _position(x, y), _width(width), _height(height), _scale(1),
    _speed(0, 0), _texture(texture), _isAlive(true), _rect(),
    _frame(0), _frameCounter(0)
{
}

void SceneObject::render(SDL_Renderer* renderer)
{
    _rect.x = _position.getX() - game->getMapOffset();
    _rect.y = _position.getY();
    _rect.w = _texture->getFrameWidth() * _scale;
    _rect.h = _texture->getFrameHeight() * _scale;

    _texture->renderFrame(_rect, 0, _frame, 0, nullptr, _flip);

    if (DEBUG) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 128);
        SDL_RenderDrawRect(renderer, &_rect);
        SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
    }
}

SDL_Rect SceneObject::getCollisionRect() const
{
    return SDL_Rect{
        _position.getX(),
        _position.getY(), // - _height,
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
        _position.getX() - game->getMapOffset(),
        _position.getY() - _height,
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
        collision = game->checkCollision(rect, target);
        
        // Cantidad que se ha entrado en el obstáculo (lo que hay que deshacer)
        int fix = collision.vertical * (speed.getY() > 0 ? 1 : -1);
        _position += {0, speed.getY() - fix};

        rect.y -= fix; // recoloca la caja para la siguiente colisión
    }

    collision.horizontal = 0;

    // Intenta moverse en horizontal
    // (podría ser conveniente comprobar colisiones incluso aunque el objeto estuviera parado)
    if (speed.getX() != 0) {
        rect.x += speed.getX();

        Collision partial = game->checkCollision(rect, target);

        // Copia la información de esta colisión a la que se devolverá
        collision.horizontal = partial.horizontal;

        if (partial.result == Collision::DAMAGE)
            collision.result = Collision::DAMAGE;

        _position += {speed.getX() - collision.horizontal * (speed.getX() > 0 ? 1 : -1), 0};
    }

    return collision;
}
