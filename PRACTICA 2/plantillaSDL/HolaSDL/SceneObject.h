#pragma once

#include <vector>
#include "GameObject.h"
#include "GameList.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Texture.h"

class SceneObject : public GameObject
{
protected:
    Vector2D<int> _position;    // Coordenadas (x, y)
    Vector2D<int> _speed;       // Velocidad (vx, vy)
    int _width, _height;        // Tama�o del objeto

    Texture* _texture = nullptr;
    SDL_Rect r;

    // Ancla a la lista de objetos del juego
    GameList<SceneObject>::anchor _anchor;

public:
    SceneObject(Game* game, int x, int y, int width, int height, Texture* texture)
        : GameObject(game), _position(x, y), _width(width), _height(height), _speed(0, 0) , _texture(texture)
    {
    
    }

    virtual ~SceneObject() {}

    virtual void render(SDL_Renderer* renderer) const override {}
    virtual void update() override {}

    // En clases hijas
    virtual Collision hit(const SDL_Rect& region, Collision::Target target) = 0;

    // devuelva una copia del objeto sobre el que 
    // se aplica (solo se aplicar� sobre los objetos de objectQueue)
    virtual SceneObject* clone() const = 0;

    // Getters virtuales
    virtual SDL_Rect getCollisionRect() const;

    virtual SDL_Rect getRenderRect() const;

    // Cuando el objeto SceneObject se destruya, siguiendo la secuencia natural de 
    // eliminaci�n de los objetos, se destruir� su atributo anchor y esto implicar� 
    // autom�ticamente su eliminaci�n de la lista
    void setListAnchor(GameList<SceneObject>::anchor&& anchor) {
        _anchor = std::move(anchor);
    }

protected:
    // Intenta mover el objeto y gestiona colisiones
    Collision tryToMove(const Vector2D<int>& speed, Collision::Target target);
};


