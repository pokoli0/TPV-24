#include "Player.h"
#include "Game.h"

Player::Player(Game* game, int x, int y)
	: SceneObject(game, x, y, TILE_SIDE, TILE_SIDE, game->getTexture(Game::MARIO))
{
	game->setMarioState(0);

	lives = 3;

	onGround = false;
	jumping = false;

	frame = 0;
	walkFrame = 0;
	frameCounter = 0;
	flipSprite = true;

	bgSpeed = 1;



	//cout << "Mario (" << posx << ", " << posy << ")" << endl;
}

void Player::render(SDL_Renderer* renderer) const
{
	SDL_Rect rect;

	rect.x = _position.getX();

	// renderframe con flipeado
	if (game->getMarioState() == 0)
	{
		rect.y = _position.getY();
		rect.w = TILE_SIDE;
		rect.h = TILE_SIDE;
		_texture->renderFrame(rect, 0, frame, 0, nullptr, flip);
	}
	else
	{
		Texture* t = game->getTexture(Game::SUPERMARIO);

		rect.y = _position.getY() - TILE_SIDE; // si no se sale del suelo
		rect.w = t->getFrameWidth() * 2;
		rect.h = t->getFrameHeight() * 2;
		t->renderFrame(rect, 0, frame, 0, nullptr, flip);
	}

	//updateAnim();

	if (DEBUG) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128); // red
		SDL_RenderDrawRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);
	}
}

void Player::update()
{
}

Collision Player::hit(const SDL_Rect& region, Collision::Target target)
{
	return Collision();
}

SceneObject* Player::clone() const
{
	return nullptr;
}

void Player::updateAnim()
{
	if (_speed.getX() != 0 && onGround) // si se esta moviendo EN HORIZONTAL
	{
		frameCounter++;
		if (frameCounter >= 1)
		{
			frameCounter = 0;
			if (!immune) {
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
			else
			{
				walkFrame = (walkFrame + 1) % 5; // para que se repita el ciclo

				if (walkFrame == 0 || walkFrame == 4) {
					frame = 2;
				}
				else if (walkFrame == 1) {
					frame = 3;
				}
				else if (walkFrame == 2) {
					frame = 4;
				}
				else if (walkFrame == 3) {
					frame = -1;
				}
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
