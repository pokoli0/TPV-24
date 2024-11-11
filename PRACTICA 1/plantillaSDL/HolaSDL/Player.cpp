#include "Player.h"

Player::Player()
{
}

Player::Player(Game* g, int posx, int posy)
{
	game = g;
	actualAspect = MARIO;
	lives = 3;
	dir = 0;
	
	initPos = Point2D<int>(posx, posy);
	pos = initPos;

	speed = 8; // def: 8
	backgroundScrollSpeed = 5; // def: 5
	
	groundY = posy;
	jumping = false;
	jumpVelocity = 0;
	gravity = 1;

	texture = game->getTexture(Game::MARIO);
	supertexture = game->getTexture(Game::SUPERMARIO);
	
	frame = 0;
	walkFrame = 0;
	frameCounter = 0;
	flipSprite = false;

	cout << "Mario (" << posx << ", " << posy << ")" << endl;
}

Player::~Player()
{
	//texture = nullptr;
	delete texture;
}

void Player::render()
{
	SDL_Rect rect;
	rect.x = pos.getX();

	// Flipear al mario segun la direccion
	SDL_RendererFlip flip;
	if (flipSprite) flip = SDL_FLIP_HORIZONTAL;
	else flip = SDL_FLIP_NONE;

	// renderframe con flipeado
	if (actualAspect == MARIO) 
	{
		rect.y = pos.getY();
		rect.w = texture->getFrameWidth();
		rect.h = texture->getFrameHeight();
		texture->renderFrame(rect, 0, frame, 0, nullptr, flip);
	}
	else 
	{
		rect.y = pos.getY() - TILE_SIDE; // si no se sale del suelo
		rect.w = supertexture->getFrameWidth() * 2;
		rect.h = supertexture->getFrameHeight() * 2;
		supertexture->renderFrame(rect, 0, frame, 0, nullptr, flip);
	}
}

void Player::update()
{
	move();

	updateAnim();

	//game->checkCollision

	if(debugMode) debug();
}

void Player::move()
{
	int offset = game->getMapOffset();

	// movimiento horizontal
	if (dir == 1) {
		flipSprite = false;
		if (pos.getX() >= Game::WIN_WIDTH / 2)
		{
			if (game->getMapOffset() <= MAX_MAP_OFFSET) {
				game->setMapOffset(offset + backgroundScrollSpeed);
			}
		}
		else {
			pos.setX(pos.getX() + speed);
		}
	}
	else if (dir == -1) {
		flipSprite = true;
		if (pos.getX() > 0) {
			pos.setX(pos.getX() - speed);
		}
	}

	// salto
	if (jumping) {
		pos.setY(pos.getY() + jumpVelocity);
		jumpVelocity += gravity; // Aumenta velocidad hacia abajo

		// Comprobamos si ha alcanzado el suelo
		if (pos.getY() >= groundY) {
			pos.setY(groundY);
			jumping = false;
			jumpVelocity = 0;
		}
	}
}

void Player::jump()
{
	if (!jumping) 
	{
		jumping = true;
		jumpVelocity = -15; 
	}
}

void Player::updateAnim()
{
	if (dir != 0 && !jumping) // si se esta moviendo
	{
		frameCounter++;
		if (frameCounter >= 1)
		{		
			frameCounter = 0;
			walkFrame = (walkFrame + 1) % 4; // para que se repita el ciclo

			if (walkFrame == 0 || walkFrame == 3) {
				frame = 2;
			}
			else if (walkFrame == 1) {
				frame = 3;
			}
			else if (walkFrame == 2) {
				frame = 4;
			}
		}
	}
	else if (jumping) {
		frame = 6;
	}
	else {
		frame = 0;
	}
}

void Player::grow()
{
	actualAspect = SUPERMARIO;
}

void Player::resetLevel()
{
	cout << "Level Reset" << endl;
	game->setMapOffset(0);
	pos = initPos;
	actualAspect = MARIO;

	if (lives == 0) {
		cout << "Game Lost" << endl;
		lives = 3; // resetGame
	}
}

void Player::handleEvents(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym) {
		case SDLK_RIGHT:
			dir = 1;
			break;

		case SDLK_LEFT:
			dir = -1;
			break;

		case SDLK_SPACE:
			jump();
			break;

		case SDLK_g:
			grow();
			break;

		case SDLK_h:
			//hit(actualAspect);
			break;

		case SDLK_r:
			resetLevel();
			break;

		case SDLK_PLUS:
			if (!fastMode) fastMode = true;
			else { fastMode = false; }
			break;

		case SDLK_d:
			if (!debugMode) debugMode = true;
			else { debugMode = false; system("cls");
			}
			break;
		}
	}
	else if (event.type == SDL_KEYUP) // soltar teclas
	{
		switch (event.key.keysym.sym) {
		case SDLK_RIGHT:
			dir = 0;
			break;

		case SDLK_LEFT:
			dir = 0;
			break;

		}
	}
}

Collision Player::hit(const SDL_Rect& rect, bool fromPlayer)
{
	//	Utiliza los métodos SDL_HasIntersection o SDL_IntersectRect 
	// con su caja de colisión y la que recibe para determinar si hay colisión.

	/*if (m == MARIO)
	{
		lives--;
		resetLevel();
	}
	else 
	{
		actualAspect = MARIO;
		inmune = true;
	}*/

	return Collision();
}

void Player::debug()
{
	system("cls"); //limpia consola

	cout << "-- DEBUG MODE ON --" << endl << endl;
	cout << "Pulsa + para activar Fast Mode." << endl << endl;

	cout << "Mario Window Position: (" << pos.getX() << ", " << pos.getY() << ")" << endl;
	cout << "Mario X Position On Tilemap: " << pos.getX() + game->getMapOffset() << endl;
	cout << "Direction: " << dir << endl;
	cout << "Mario & Scrolling Speed: " << speed << endl;

	cout << "Texture frame: " << frame << endl;
	cout << "Jumping: " << jumping << endl;
	cout << "Aspect: " << actualAspect << endl;
	cout << "Lives: " << lives << endl;

	cout << "Map Offset: " << game->getMapOffset() << endl;

	cout << endl;
	cout << "Fast Mode: " << fastMode << endl;

	if (fastMode) {
		speed = 15;
		backgroundScrollSpeed = 15;
	}
	else {
		speed = 8;
		backgroundScrollSpeed = 5;
	}

}
