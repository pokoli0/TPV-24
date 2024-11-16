#include "Player.h"

Player::Player()
{
}

Player::Player(Game* g, int posx, int posy)
{
	game = g;

	game->setMarioState(0);

	lives = 3;

	initPos = Point2D<int>(posx, posy);
	pos = initPos;

	speed = Point2D<int>(0, 0);
	xSpeed = 8;

	onGround = false;
	jumping = false;

	frame = 0;
	walkFrame = 0;
	frameCounter = 0;
	flipSprite = true;

	bgSpeed = 1;

	//cout << "Mario (" << posx << ", " << posy << ")" << endl;
}

Player::~Player()
{
	//texture = nullptr;
	delete texture;
}

void Player::render(int marioState, SDL_Renderer* renderer)
{
	rect.x = pos.getX();

	// renderframe con flipeado
	if (marioState == 0)
	{
		texture = game->getTexture(Game::MARIO);

		rect.y = pos.getY();
		rect.w = TILE_SIDE;
		rect.h = TILE_SIDE;
		texture->renderFrame(rect, 0, frame, 0, nullptr, flip);
	}
	else
	{
		texture = game->getTexture(Game::SUPERMARIO);

		rect.y = pos.getY() - TILE_SIDE; // si no se sale del suelo
		rect.w = texture->getFrameWidth() * 2;
		rect.h = texture->getFrameHeight() * 2;
		texture->renderFrame(rect, 0, frame, 0, nullptr, flip);
	}

	updateAnim();

	if (DEBUG) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128); // red
		SDL_RenderDrawRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}
}

void Player::update()
{
	checkAlive();

	// Caida por gravedad
	speed.setY(speed.getY() + GRAVITY);

	// Colisiones verticales
	SDL_Rect verticalRect;
	verticalRect.x = rect.x + game->getMapOffset();
	verticalRect.y = rect.y + speed.getY();
	verticalRect.h = rect.h;
	verticalRect.w = rect.w;

	Collision col = game->checkCollision(verticalRect, true);

	if (!col) // si no hay col, cae normal
	{
		pos.setY(pos.getY() + speed.getY());
	}
	else // si hay col, vemos limites segun la direccion de mario
	{
		if (speed.getY() > 0)
		{
			pos.setY(pos.getY() + speed.getY() - col.intersectionRect.h);
			onGround = true;

		}
		else if (speed.getY() < 0)
		{
			pos.setY(pos.getY() + speed.getY() + col.intersectionRect.h);
		}
		jumping = false;
		speed.setY(0);
	}

	// Colisiones horizontales
	SDL_Rect horizontalRect;
	horizontalRect.x = pos.getX() + speed.getX() + game->getMapOffset();
	horizontalRect.y = rect.y;
	horizontalRect.h = rect.h;
	horizontalRect.w = rect.w;

	col = game->checkCollision(horizontalRect, true);

	if (!col)
	{
		if (speed.getX() > 0) // derecha
		{
			flip = SDL_FLIP_NONE;
			if (pos.getX() >= Game::WIN_WIDTH / 2) // si pasa la mitad de la pantalla
			{
				// mueve el fondo
				if (game->getMapOffset() <= MAX_MAP_OFFSET)
				{
					game->setMapOffset(game->getMapOffset() + BACKGROUND_SCROLL_SPEED * bgSpeed);
				}
			}
			else // mueve a mario
			{
				pos.setX(pos.getX() + speed.getX());
			}

		}
		else if (speed.getX() < 0)  // izquierda
		{
			flip = SDL_FLIP_HORIZONTAL;
			if (pos.getX() > 0) pos.setX(pos.getX() + speed.getX());
		}
	}
	else // COLISION
	{
		if (speed.getX() > 0)
		{
			pos.setX(pos.getX() + speed.getX() - col.intersectionRect.w);// empujar hacia izquierda
		}
		else
		{
			pos.setX(pos.getX() + speed.getX() + col.intersectionRect.w);// empujar hacia derecha
		}

	}

	if (debugMode) debug();
}


void Player::jump()
{
	if (!jumping && onGround)
	{
		onGround = false;
		jumping = true;

		speed.setY(-30);
	}
}

void Player::updateAnim()
{
	if (speed.getX() != 0 && onGround) // si se esta moviendo EN HORIZONTAL
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
	else if (!onGround) {
		frame = 6;
	}
	else {
		frame = 0;
	}
}

void Player::grow()
{
	game->setMarioState(1);
}

void Player::checkAlive()
{
	if (pos.getY() >= MAX_HEIGHT) {
		lives--;

		cout << "Caida" << endl;
		cout << "Vidas: " << lives << endl;

		isAlive = false;
	}

	if (lives == 0) {
		cout << "Game Lost" << endl;
		lives = 3; // resetGame
		isAlive = false;
	}

	if (!isAlive) resetLevel();
}

void Player::resetLevel()
{
	cout << "Level Reset" << endl;
	game->setMapOffset(1);
	pos = initPos;
	isAlive = true;
	game->setMarioState(0);
}

void Player::handleEvents(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym) {
		case SDLK_RIGHT:
			speed.setX(xSpeed);
			break;

		case SDLK_LEFT:
			speed.setX(-xSpeed);
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
			else {
				debugMode = false; system("cls");
			}
			break;
		}
	}
	else if (event.type == SDL_KEYUP) // soltar teclas
	{
		switch (event.key.keysym.sym) {
		case SDLK_RIGHT:
			speed.setX(0);
			break;

		case SDLK_LEFT:
			speed.setX(0);
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
	//cout << "Mario X Position On Tilemap: " << pos.getX() + game->getMapOffset() << endl;
	//cout << "Direction: " << dir.getX() << endl;
	//cout << "Mario & Scrolling Speed: " << speed << endl;

	//cout << "Texture frame: " << frame << endl;
	cout << "Jumping: " << jumping << endl;
	cout << "On Ground: " << onGround << endl;
	//cout << "On Wall: " << onWall << endl;
	cout << "Speed Y: " << speed.getY() << endl;
	cout << "Speed X: " << speed.getX() << endl;
	/*cout << "Aspect: " << actualAspect << endl;
	cout << "Lives: " << lives << endl;*/

	//cout << "Map Offset: " << game->getMapOffset() << endl;

	cout << endl;
	cout << "Fast Mode: " << fastMode << endl;

	if (fastMode) {
		xSpeed = 15;
		bgSpeed = 2;
	}
	else {
		xSpeed = 8;
		bgSpeed = 1;
	}

}
void Player::checkc() {
	if (game->getMarioState() == 1) {
	game->setMarioState(0);
	}
	else if (game->getMarioState() == 0) {
	isAlive = false;
	}
}
