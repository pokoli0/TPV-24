#pragma once
#include "checkML.h"

#include "SceneObject.h"
#include "EventHandler.h"

class Player : public SceneObject, public EventHandler
{
public:
	Player(Game* game, int x, int y);

	void render(SDL_Renderer* renderer) override;
	void update() override;

	Collision hit(const SDL_Rect& region, Collision::Target target) override;
	SceneObject* clone() const override;

	// resta vidas y cambia el estado de mario
	void hit() override;

	// comprueba si se ha caido, resta vidas si es el caso
	void checkAlive() override;

	void updateAnim() override;

	// recoloca al principio del nivel actual
	void resetPlayer();

	// comprueba si se ha llegado a la posicion de la bandera
	void finishLevel();

	/// ===== Gestion de movimiento =====

	void handleEvent(const SDL_Event& event) override;
	void jump();
	

	/// ===== Getters y Setters =====

	int getLives() { return lives; }
	void setLives(int n) { lives = n; }

	bool getImmunity() { return immune; }


private:
	int lives;

	bool immune;
	int temp = 0;
	int immuneTime = 50;

	int marioSpeed;
	bool onGround, jumping;

	int walkFrame;

	Point2D<double> initPos;

	// posicion de la bandera (peruvian)
	double winPosition = 6306;
};

