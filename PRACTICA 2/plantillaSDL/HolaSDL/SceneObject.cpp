#include "SceneObject.h"
#include "Game.h"

Collision SceneObject::tryToMove(const Vector2D<int>& speed, Collision::Target target)
{
    {
        // Implementación basada en el enunciado
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
}
