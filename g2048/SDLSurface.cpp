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
		surface_ = nullptr;
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
	CreateRGBSurface(0, width, height, DEFAULT_DEPTH, DEFAULT_RMASK, DEFAULT_GMASK, DEFAULT_AMASK, DEFAULT_AMASK);
	if (surface_ == nullptr) {
		return 1;
	}
	SDL_Rect rect;
	Uint32 color = SDL_MapRGB(surface_->format, 0xFF, 0xFF, 0xFF);
	rect.x = 0;
	rect.y = 0;
	rect.w = width_;
	rect.h = height_;
	SDL_FillRect(surface_, &rect, color);
	SDL_SetColorKey(surface_, SDL_TRUE, color);
	return 0;
}

SDL_Surface * SDLSurface::Get()
{
	return surface_;
}

void SDLSurface::SetDrawColor(Uint32 color)
{
	drawColor_ = color;
}

void SDLSurface::SetDrawColorRGB(Uint8 r, Uint8 g, Uint8 b)
{
	drawColor_ = SDL_MapRGB(surface_->format, r, g, b);
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

void SDLSurface::DrawRoundRect(int x, int y, int width, int height, int radius)
{
	int dx = 0;
	int dy = radius;
	int d = 3 - radius - radius;
	int xl = x + radius;
	int xr = width + x - radius - 1;
	int yu = y + radius;
	int yd = height + y - radius - 1;
	int xlmdx, xlmdy, xrpdx, xrpdy;
	int yumdy, yumdx, ydpdx, ydpdy;
	SDL_Rect rect;
	while (dx < dy) {
		xlmdx = xl - dx;
		xlmdy = xl - dy;
		xrpdx = xr + dx;
		xrpdy = xr + dy;
		yumdy = yu - dy;
		ydpdy = yd + dy;
		yumdx = yu - dx;
		ydpdx = yd + dx;
		DrawHLine(xlmdx, xrpdx, yumdy);
		DrawHLine(xlmdx, xrpdx, ydpdy);
		DrawHLine(xlmdy, xrpdy, yumdx);
		DrawHLine(xlmdy, xrpdy, ydpdx);
		if (d < 0) d += 4 * dx + 6;
		else d += 4 * (dx - --dy) + 10;
		dx++;
	}
	rect.x = x;
	rect.y = y + radius + 1;
	rect.w = width;
	rect.h = height - radius - radius - 2;
	SDL_FillRect(surface_, &rect, drawColor_);
}