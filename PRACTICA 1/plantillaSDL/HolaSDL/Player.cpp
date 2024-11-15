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

	speed = Point2D<int>(0, 0);
	
	groundY = posy;
	onGround = false;
	//onWall = false;
	jumping = false;
	jumpVelocity = 0;

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

void Player::render(SDL_Renderer* renderer)
{
	rect.x = pos.getX();

	// Flipear al mario segun la direccion
	SDL_RendererFlip flip;
	if (speed.getX() > 0) flip = SDL_FLIP_HORIZONTAL;
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

	if (DEBUG) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
		SDL_RenderDrawRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}
}

void Player::update()
{
	// Caida por gravedad
	speed.setY(speed.getY() + GRAVITY);


	// Colisiones verticales
	SDL_Rect verticalRect;
	verticalRect.x = rect.x;
	verticalRect.y = rect.y + speed.getY();
	verticalRect.h = rect.h;
	verticalRect.w = rect.w;

	Collision col = game->checkCollision(verticalRect, true);

	if (!col) {
		pos.setY(pos.getY() + speed.getY());
	}
	else
	{
		pos.setY(pos.getY() + speed.getY() - col.intersectionRect.h);
		onGround = true;

	}
	speed.setY(0);


	// Colisiones horizontales
	SDL_Rect horizontalRect;
	horizontalRect.x = rect.x + speed.getX();
	horizontalRect.y = rect.y;
	horizontalRect.h = rect.h;
	horizontalRect.w = rect.w;

	col = game->checkCollision(horizontalRect, true);

	if (!col) {
		// derecha
		if (speed.getX() > 0)
		{
			if (pos.getX() >= Game::WIN_WIDTH / 2)
			{
				// mueve el fondo
				if (game->getMapOffset() <= MAX_MAP_OFFSET) {
					game->setMapOffset(game->getMapOffset() + BACKGROUND_SCROLL_SPEED);
				}
			}
			else
			{
				// mueve a mario
				pos.setX(pos.getX() + speed.getX());
			}

		}
		else if (speed.getX() < 0)  // izquierda
		{
			if (pos.getX() > 0) {
				pos.setX(pos.getX() + speed.getX());
			}
		}
	}
	else
	{
		if (speed.getX() > 0)
		{
			pos.setX(pos.getX() - col.intersectionRect.w / game->getMapOffset());// empujar hacia izquierda
		}
		else {
			pos.setX(pos.getX() + col.intersectionRect.w / game->getMapOffset());// empujar hacia derecha
		}

	}
	speed.setX(0.0f);



	//updateAnim();

	if(debugMode) debug();
}


void Player::jump()
{
	if (!jumping && onGround) 
	{
		jumping = true;
		onGround = false;	
		
		speed.setY(15);
	}
}

void Player::updateAnim()
{
	if (speed.getX() != 0 && speed.getY() == 0) // si se esta moviendo EN HORIZONTAL
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
	else if (speed.getY() != 0) {
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
			speed.setX(8);
			break;

		case SDLK_LEFT:
			speed.setX(-8);
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

	//cout << "Mario Window Position: (" << pos.getX() << ", " << pos.getY() << ")" << endl;
	//cout << "Mario X Position On Tilemap: " << pos.getX() + game->getMapOffset() << endl;
	//cout << "Direction: " << dir.getX() << endl;
	//cout << "Mario & Scrolling Speed: " << speed << endl;

	//cout << "Texture frame: " << frame << endl;
	cout << "Jumping: " << jumping << endl;
	cout << "On Ground: " << onGround << endl;
	//cout << "On Wall: " << onWall << endl;
	cout << "Speed Y: " << speed.getY() << endl;
	//cout << "Speed X: " << speed.getX() << endl;
	/*cout << "Aspect: " << actualAspect << endl;
	cout << "Lives: " << lives << endl;*/

	//cout << "Map Offset: " << game->getMapOffset() << endl;

	cout << endl;
	cout << "Fast Mode: " << fastMode << endl;

	//if (fastMode) {
	//	speed = 15;
	//	//backgroundScrollSpeed = 15;
	//}
	//else {
	//	speed = 8;
	//	//backgroundScrollSpeed = 5;
	//}

}
