#pragma once
#include "checkML.h"

#include "GameObject.h"

#include "GameList.h"
#include "Collision.h"

class PlayState;

class SceneObject : public GameObject
{
protected:
    Point2D<double> _position;    // Coordenadas (x, y)
    Point2D<int> _speed;       // Velocidad (vx, vy)
    int _width, _height;        // Tamaño del objeto

    int _scale;

    Texture* _texture = nullptr;
    SDL_Rect _rect;

    PlayState* _playState;

    bool _isAlive;

    Collision collision;

    // para que no se salga de la pantalla por la izquierda
    bool canMove;

    // Ancla a la lista de objetos del juego
    GameList<SceneObject>::anchor _anchor;

    int _frame;
    int _frameCounter;
    bool _flipSprite;
    SDL_RendererFlip _flip;

public:
    SceneObject(Game* game, PlayState* state, int x, int y, int width, int height, Texture* texture);

    // Constructora por copia
    SceneObject(const SceneObject& other)
        : GameObject(other.game),
        _position(other._position),
        _speed(other._speed),
        _width(other._width),
        _height(other._height),
        _scale(other._scale),
        _texture(other._texture),
        _rect(other._rect),
        _isAlive(other._isAlive),
        collision(other.collision),
        canMove(other.canMove),
        _frame(other._frame),
        _frameCounter(other._frameCounter),
        _flipSprite(other._flipSprite),
        _flip(other._flip),
        _playState(other._playState)
    {}

    virtual ~SceneObject() {}

    virtual void render(SDL_Renderer* renderer) override;
    virtual void update() override {}

    // Recibe rectangulo que se vera afectado y si viene del jugador
    virtual Collision hit(const SDL_Rect& region, Collision::Target target) = 0;

    //virtual void onLevelReload() = 0;

    virtual void checkAlive() = 0;
    virtual void updateAnim() = 0;

    // devuelva una copia del objeto sobre el que 
    // se aplica (solo se aplicará sobre los objetos de objectQueue)
    virtual SceneObject* clone() const = 0;


    /// ===== Metodos de Mario =====
    virtual void hit() {}
    virtual bool getImmunity() const { return false; }


    /// ===== Getters y setters =====

    virtual SDL_Rect getCollisionRect() const;
    virtual  bool getAlive() const;
    virtual SDL_Rect getRenderRect() const;

    // para el "frozen"
    double getXPos() { return _position.getX(); }

    // Cuando el objeto SceneObject se destruya, siguiendo la secuencia natural de 
    // eliminación de los objetos, se destruirá su atributo anchor y esto implicará 
    // automáticamente su eliminación de la lista
    void setListAnchor(GameList<SceneObject>::anchor&& anchor) {
        _anchor = std::move(anchor);
    }

protected:
    // El método protegido tryToMove concentra el código de la comprobación
    // de las colisiones para todos los objetos del juego. Recibe un vector
    // con el movimiento que se quiere aplicar al objeto, prueba el movimiento
    // en cambos ejes y devuelve la información de tipo Collision.
    // Target: a qué hace daño. 
    // - Si lo usamos en goomba, target sera player.
    // - Si lo usamos en caparazon, target sera both.
    // - Si lo usamos en player, target sera none.
    Collision tryToMove(const Vector2D<int>& speed, Collision::Target target);

    void setScale(int n) { _scale = n; }
};


