#pragma once

#include <SDL2\SDL.h>

class SDLTexture
{
private:
	SDL_Texture *texture_;
public:
	SDLTexture();
	~SDLTexture();
};

