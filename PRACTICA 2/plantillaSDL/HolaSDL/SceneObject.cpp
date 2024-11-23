#include "SceneObject.h"
#include "Game.h"

SDL_Rect SceneObject::getCollisionRect() const
{
    return SDL_Rect{
        _position.getX(),
        _position.getY() - _height,  // Esquina superior izquierda de la caja
        _width,
        _height
    };
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
        
        int fix = collision.vertical * (speed.getY() > 0 ? 1 : -1);
        _position += {0, speed.getY() - fix};
    }

    // Movimiento horizontal
    if (speed.getX() != 0) {
        rect.x += speed.getX();
        Collision partial = game->checkCollision(rect, target);
        collision.horizontal = partial.horizontal;
        if (partial.result == Collision::DAMAGE)
            collision.result = Collision::DAMAGE;
        _position += {speed.getX() - collision.horizontal * (speed.getX() > 0 ? 1 : -1), 0};
    }

    return collision;
}
