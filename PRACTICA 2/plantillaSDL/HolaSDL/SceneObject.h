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
    int _width, _height;        // Tamaño del objeto

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
    // se aplica (solo se aplicará sobre los objetos de objectQueue)
    virtual SceneObject* clone() const = 0;

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


