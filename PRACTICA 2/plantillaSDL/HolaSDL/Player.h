#pragma once
#include "SceneObject.h"

class Player : public SceneObject
{

public:
	void getLives();
	void isSupermario();
	void handleEvent(SDL_Event e);
};

