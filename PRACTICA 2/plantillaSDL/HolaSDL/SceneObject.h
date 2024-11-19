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
    SceneObject(Game* game, int x, int y, int width, int height)
        : GameObject(game), _position(x, y), _width(width), _height(height), _speed(0, 0) {}

    virtual ~SceneObject() {}

    // En clases hijas
    virtual Collision hit(const SDL_Rect& region, Collision::Target target) = 0;

    // Getters virtuales
    virtual SDL_Rect getCollisionRect() const;

    virtual SDL_Rect getRenderRect() const;

    // Cuando el objeto SceneObject se destruya, siguiendo la secuencia natural de 
    // eliminación de los objetos, se destruirá su atributo anchor y esto implicará 
    // automáticamente su eliminación de la lista
    void setListAnchor(GameList<SceneObject>::anchor&& anchor) {
        _anchor = std::move(anchor);
    }

protected:
    // Intenta mover el objeto y gestiona colisiones
    Collision tryToMove(const Vector2D<int>& speed, Collision::Target target);
};


