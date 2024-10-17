#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>

/**
 * Object-oriented wrapper for SDL textures with frame support.
 */
class Texture
{
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;

	//texture width and height
	int width, height;
	
	int nrows, ncolumns;

	//frame width and height
	int frameWidth, frameHeight;

	static SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filename);

public:
	Texture(SDL_Renderer* renderer, const char* filename, int rows = 1, int columns = 1);
	Texture(SDL_Renderer* renderer, SDL_Texture* texture, int rows = 1, int columns = 1);
	~Texture();

	/// Width of a frame in pixels
	int getFrameWidth() const {	return frameWidth; }
	/// Height of a frame in pixels
	int getFrameHeight() const { return frameHeight; }
	/// Number of frames in each row
	int getNumRows() const { return nrows; }
	/// Number of frames in each column
	int getNumColumns() const { return ncolumns; }

	/// Render the whole picture filling the entire screen
	void render() const;
	/// Render the whole picture to the given rectangle
	void render(const SDL_Rect& target) const;
	/// Render a rectangle full screen
	void renderRect(const SDL_Rect& source) const;
	/// Render the whole picture with additional options from SDL_RenderCopyEx
	void render(const SDL_Rect& target,
		double angle,
		const SDL_Point* center = nullptr,
		SDL_RendererFlip flip = SDL_FLIP_NONE) const;

	/// Render a frame to the given rectangle
	void renderFrame(const SDL_Rect& target, int row, int col) const;
	/// Render a frame to the given rectangle
	void renderFrame(const SDL_Rect& target, int row, int col, SDL_RendererFlip flip) const;
	/// Render a frame with additional options from SDL_RenderCopyEx
	void renderFrame(const SDL_Rect& target,
		int row,
		int col,
		double angle,
		const SDL_Point* center = nullptr,
		SDL_RendererFlip flip = SDL_FLIP_NONE) const;

	/// Render the whole picture to the given rectangle with modified color
	void render(const SDL_Rect& target, SDL_Color color) const;
};


#endif // TEXTURE_H
