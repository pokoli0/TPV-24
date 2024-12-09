#include "checkML.h"
#include "Button.h"

Button::Button(GameState* gameState, Texture* texture, Texture* texture2, Point2D<double> pos)
	: GameObject(gameState), texture(texture), mushroomTexture(texture2), position(pos)
{
	currentFrame = DEFAULT;

	point.x = 0;
	point.y = 0;

	//mushroomTexture = // necesito acceder a la clase game
}

void Button::emit() const
{
	// llama a las funciones registradas
	for (Callback c : callbacks) c();
}

void Button::render(SDL_Renderer* renderer)
{
	rect.x = (int)position.getX();
	rect.y = (int)position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();

	mushRect.x = (int)position.getX() - 50;
	mushRect.y = (int)position.getY() - 5;
	mushRect.w = mushroomTexture->getFrameWidth() * 2;
	mushRect.h = mushroomTexture->getFrameHeight() * 2;

	if (currentFrame == OVER)
	{
		texture->render(rect, SDL_Color{ 0, 255, 0, 255 }); // cambia color
		mushroomTexture->render(mushRect);
		// cambia pos del mushroomtexture aqui
	}
	else texture->render(rect);
}

void Button::update()
{
	// actualiza pos del cursor
	SDL_GetMouseState(&point.x, &point.y);

	// comprueba si el cursor esta sobre el rectangulo
	if (SDL_PointInRect(&point, &rect)) currentFrame = OVER;
	else currentFrame = DEFAULT;
}

void Button::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) // boton izq
	{
		// pos del cursor al pulsar
		point.x = event.button.x;
		point.y = event.button.y;

		// si el punto esta en el rect del boton
		if (SDL_PointInRect(&point, &rect))
		{
			currentFrame = CLICK;
			emit();
		}
	}
}

void Button::connect(const Callback& c)
{
	callbacks.push_back(c);
}