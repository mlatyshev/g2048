#include "SDLSurface.h"

SDLSurface::SDLSurface()
{
	surface_ = nullptr;
	width_ = 0;
	height_ = 0;
	depth_ = 0;
}


SDLSurface::~SDLSurface()
{
	Free();
}

void SDLSurface::Free()
{
	if (surface_ != nullptr) {
		SDL_FreeSurface(surface_);
		width_ = 0;
		height_ = 0;
	}
}

int SDLSurface::CreateRGBSurface(Uint32 flags, int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask)
{
	Free();
	surface_ = SDL_CreateRGBSurface(flags, width, height, depth, Rmask, Gmask, Bmask, Amask);
	if (surface_ == nullptr) {
		return 1;
	}
	width_ = surface_->w;
	height_ = surface_->h;
	return 0;
}

int SDLSurface::CreateSurface(int width, int height)
{
	return CreateRGBSurface(0, width, height, DEFAULT_DEPTH, DEFAULT_RMASK, DEFAULT_GMASK, DEFAULT_AMASK, DEFAULT_AMASK);
}

SDL_Surface * SDLSurface::Get()
{
	return surface_;
}

void SDLSurface::SetDrawColor(Uint32 color)
{
	drawColor_ = color;
}

void SDLSurface::LockSurface()
{
	if (SDL_MUSTLOCK(surface_)) {
		SDL_LockSurface(surface_);
	}
}

void SDLSurface::UnlockSurface()
{
	if (SDL_MUSTLOCK(surface_)) {
		SDL_UnlockSurface(surface_);
	}
}

void SDLSurface::PutPixel32(int x, int y)
{
	// Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32 *)surface_->pixels;

	// Set the pixel
	pixels[(y * height_) + x] = drawColor_;
}

void SDLSurface::DrawHLine(int x1, int x2, int y)
{
	for (int x = x1; x < x2; x++) {
		PutPixel32(x, y);
	}
}
