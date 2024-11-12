#include "Player.h"

Player::Player()
{
}

Player::Player(Game* g, int posx, int posy)
{
	game = g;
	actualAspect = MARIO;
	lives = 3;
	
	initPos = Point2D<int>(posx, posy);
	pos = initPos;

	dir = Point2D<int>(0, 0);

	speed = 8; // def: 8
	
	groundY = posy;
	onGround = true;
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
	pos.setY(pos.getY() + 1);

	move();

	updateAnim();

	pos.setY(pos.getY() + dir.getY());// Comprobación vertical

	SDL_Rect rectY{ pos.getX(), pos.getY(),
		texture->getFrameWidth(), texture->getFrameHeight() };

	Collision coll = game->checkCollision(rectY, true);

	if (coll) {
		if (dir.getY() > 0)
		{
			pos.setY(pos.getY() + coll.rect.h);// empujar hacia arriba
			onGround = true;
		}
		else {
			pos.setY(pos.getY() - coll.rect.h); // empujar hacia abajo
		}
		dir.setY(0.0f);
	}


	pos.setX(pos.getX() + dir.getX());// Comprobación horizontal
	SDL_Rect rectX{ pos.getX(), pos.getY() - texture->getFrameHeight(),
		texture->getFrameWidth(), texture->getFrameHeight() };

	coll = game->checkCollision(rectX, true);
	if (coll) {
		if (dir.getX() > 0)
		{
			pos.setX(pos.getX() - coll.rect.w);// empujar hacia izquierda
		}
		else {
			pos.setX(pos.getX() + coll.rect.w);// empujar hacia derecha
		}
		dir.setX(0.0f);
	}


	if (coll.damages) // si hace daño restar vida
	{
		lives--;
	}



	if(debugMode) debug();
}

void Player::move()
{
	int offset = game->getMapOffset();

	// movimiento horizontal
	if (dir.getX() == 1) {
		flipSprite = false;
		if (pos.getX() >= Game::WIN_WIDTH / 2)
		{
			if (game->getMapOffset() <= MAX_MAP_OFFSET) {
				game->setMapOffset(offset + BACKGROUND_SCROLL_SPEED);
			}
		}
		else {
			pos.setX(pos.getX() + speed);
		}
	}
	else if (dir.getX() == -1) {
		flipSprite = true;
		if (pos.getX() > 0) {
			pos.setX(pos.getX() - speed);
		}
	}

	// salto
	if (dir.getY() == 1) 
	{
		pos.setY(pos.getY() + jumpVelocity);
		jumpVelocity += gravity;
	}
	else if(dir.getY() == 0) {
		onGround = true;
		jumping = false;
		jumpVelocity = 0;
	}	

	//pos.setY(pos.getY() + 1);
}

void Player::jump()
{
	if (!jumping && onGround) 
	{
		dir.setY(1);
		onGround = false;
		jumping = true;
		jumpVelocity = -15; 
	}
}

void Player::updateAnim()
{
	if (dir.getX() != 0 && !jumping) // si se esta moviendo
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
			dir.setX(1);
			break;

		case SDLK_LEFT:
			dir.setX(-1);
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
			dir.setX(0);
			break;

		case SDLK_LEFT:
			dir.setX(0);
			break;

		}
	}
}

void Player::hit()
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
	



}

void Player::debug()
{
	system("cls"); //limpia consola

	cout << "-- DEBUG MODE ON --" << endl << endl;
	cout << "Pulsa + para activar Fast Mode." << endl << endl;

	cout << "Mario Window Position: (" << pos.getX() << ", " << pos.getY() << ")" << endl;
	cout << "Mario X Position On Tilemap: " << pos.getX() + game->getMapOffset() << endl;
	cout << "Direction: " << dir.getX() << endl;
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
		//backgroundScrollSpeed = 15;
	}
	else {
		speed = 8;
		//backgroundScrollSpeed = 5;
	}

}
