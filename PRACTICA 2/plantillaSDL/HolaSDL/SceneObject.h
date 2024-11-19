#pragma once

#include "GameObject.h"
#include "GameList.h"
#include "Vector2D.h"
#include "Collision.h"

class SceneObject : public GameObject
{
protected:
    Vector2D<int> _position;    // Coordenadas (x, y)
    Vector2D<int> _speed;       // Velocidad (vx, vy)
    int _width, _height;        // Tamaño del objeto

    // Ancla a la lista de objetos del juego
    GameList<SceneObject>::anchor _anchor;

public:
    // Constructor
    SceneObject(Game* game, int x, int y, int width, int height)
        : GameObject(game), _position(x, y), _width(width), _height(height), _speed(0, 0) {}

    // Destructor virtual
    virtual ~SceneObject() {}

    // Métodos abstractos (deben implementarse en subclases)
    virtual Collision hit(const SDL_Rect& region, Collision::Target target) = 0;

    // Métodos concretos
    virtual SDL_Rect getCollisionRect() const {
        return SDL_Rect{
            _position.getX(),
            _position.getY() - _height,  // Esquina superior izquierda de la caja
            _width,
            _height
        };
    }

    virtual SDL_Rect getRenderRect() const {
        return SDL_Rect{
            _position.getX() - game->getMapOffset(),
            _position.getY() - _height,
            _width,
            _height
        };
    }

    void setListAnchor(GameList<SceneObject>::anchor&& anchor) {
        _anchor = std::move(anchor);
    }

protected:
    // Método para intentar mover el objeto y gestionar colisiones
    Collision tryToMove(const Vector2D<int>& speed, Collision::Target target);
};


