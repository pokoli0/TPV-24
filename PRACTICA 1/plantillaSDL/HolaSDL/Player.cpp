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
	onGround = false;
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
	// gravedad: caida de mario si no esta en el suelo y si no esta saltando
	if (!onGround && !jumping) 
	{
		dir.setY(-1);
		pos.setY(pos.getY() + 5); // caida por gravedad
	}
	else if (onGround)
	{
		dir.setY(0); // no sube ni baja
	}
	
	move();

	updateAnim();

	// vemos colisiones -> ahora vienen de mario
	Collision col = game->checkCollision(rect, true);

	if (col) 
	{
		if(dir.getY() == -1) // si esta bajando
		{
			pos.setY(pos.getY() - TILE_SIDE/4 - 1);
			onGround = true;
		}
	}
	else 
	{
		onGround = false;
	}

	// segunda comprobacion
	col = game->checkCollision(rect, true);

	if (col)
	{
		if (dir.getX() == 1) // si esta yendo hacia la derecha
		{
			//pos.setX(pos.getX() - TILE_SIDE / 4);
		}
	}

	if(debugMode) debug();
}

void Player::move()
{
	int offset = game->getMapOffset();

	/// movimiento horizontal ---

	// hacia la derecha
	if (dir.getX() == 1) {
		flipSprite = false;
		if (pos.getX() >= Game::WIN_WIDTH / 2)
		{
			// mueve el fondo
			if (game->getMapOffset() <= MAX_MAP_OFFSET) {
				game->setMapOffset(offset + BACKGROUND_SCROLL_SPEED);
			}
		}
		else {
			// mueve a mario
			pos.setX(pos.getX() + speed);
		}
	}
	// hacia la izquierda
	else if (dir.getX() == -1) {
		flipSprite = true;
		if (pos.getX() > 0) {
			pos.setX(pos.getX() - speed);
		}
	}


	/// movimiento vertical ---

	// SALTO
	if (dir.getY() == 1) {
		pos.setY(pos.getY() - jumpVelocity);

		jumpVelocity -= 1;

		if(jumpVelocity <= 0) dir.setY(-1); // caida
	}
	else if (dir.getY() == -1)
	{
		jumping = false; // deja de subir
	}
}

void Player::jump()
{
	if (!jumping && onGround) 
	{
		jumping = true;
		onGround = false;

		dir.setY(1);

		jumpVelocity = 15; 
	}
}

void Player::updateAnim()
{
	if (dir.getX() != 0 && dir.getY() == 0) // si se esta moviendo EN HORIZONTAL
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
	else if (dir.getY() != 0) {
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
