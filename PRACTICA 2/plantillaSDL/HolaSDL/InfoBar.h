#pragma once

#include "GameObject.h"


class InfoBar : public GameObject
{
public:
	InfoBar(Game* game, Texture* t);

	void render(SDL_Renderer* renderer) override;
	void update() override;

private:
    Vector2D<int> _position;    // Coordenadas (x, y)
    Vector2D<int> _speed;       // Velocidad (vx, vy)
    int _width, _height;        // Tamaño del objeto

    int _scale;

    Texture* _texture = nullptr;
    SDL_Rect _rect;

    bool _isAlive;

    int _frame;
    int _frameCounter;
};

