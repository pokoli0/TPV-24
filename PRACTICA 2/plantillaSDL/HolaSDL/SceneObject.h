#pragma once

#include "GameObject.h"

#include "GameList.h"
#include "Collision.h"

class SceneObject : public GameObject
{
protected:
    Vector2D<int> _position;    // Coordenadas (x, y)
    Vector2D<int> _speed;       // Velocidad (vx, vy)
    int _width, _height;        // Tama�o del objeto

    int _scale;

    Texture* _texture = nullptr;
    SDL_Rect _rect;

    bool _isAlive;

    Collision collision;
    bool canMove;

    // Ancla a la lista de objetos del juego
    GameList<SceneObject>::anchor _anchor;

    int _frame;
    int _frameCounter;
    bool _flipSprite;
    SDL_RendererFlip _flip;

public:
    SceneObject(Game* game, int x, int y, int width, int height, Texture* texture)
        : GameObject(game), _position(x, y), _width(width), _height(height), _scale(1),
        _speed(0, 0), _texture(texture), _isAlive(true), _rect(),
        _frame(0), _frameCounter(0) 
    {

    }

    virtual ~SceneObject() {}

    virtual void render(SDL_Renderer* renderer) override;
    virtual void update() override {}

    // Recibe rectangulo que se vera afectado y si viene del jugador
    virtual Collision hit(const SDL_Rect& region, Collision::Target target) = 0;

    // igual este metodo aqui no tiene mucho sentido por el tilemap
    virtual void checkAlive() = 0;
    virtual void updateAnim() = 0;

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
    // El m�todo protegido tryToMove concentra el c�digo de la comprobaci�n
    // de las colisiones para todos los objetos del juego. Recibe un vector
    // con el movimiento que se quiere aplicar al objeto, prueba el movimiento
    // en cambos ejes y devuelve la informaci�n de tipo Collision.
    // Target: a qu� hace da�o. 
    // - Si lo usamos en goomba, target sera player.
    // - Si lo usamos en caparazon, target sera both.
    // - Si lo usamos en player, target sera none.
    Collision tryToMove(const Vector2D<int>& speed, Collision::Target target);

    void setScale(int n) { _scale = n; }
};


