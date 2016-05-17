#include "SDLTexture.h"

SDLTexture::SDLTexture()
{
	texture_ = nullptr;
}


SDLTexture::~SDLTexture()
{
	if (texture_ != nullptr) {
		SDL_DestroyTexture(texture_);
		texture_ = nullptr;
	}
}
