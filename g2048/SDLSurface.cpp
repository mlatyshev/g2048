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

void SDLSurface::SetDrawColorRGB(Uint32 color, Uint8 r, Uint8 g, Uint8 b)
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

void SDLSurface::DrawRoundRect(Uint16 x1, Uint16 x2, Uint16 y1, Uint16 y2, Uint16 radius)
{
	Sint16 dx = 0;
	Sint16 dy = radius;
	Sint16 d = 3 - radius - radius;
	Sint16 xl = x1 + radius;
	Sint16 xr = x2 - radius;
	Sint16 yu = y1 + radius;
	Sint16 yd = y2 - radius;
	Sint16 xlmdx, xlmdy, xrpdx, xrpdy;
	Sint16 yumdy, yumdx, ydpdx, ydpdy;
	SDL_Rect rect;
	// Когда dx == dy линии дублируются, можно (нужно?) оптимизировать
	while (dx <= dy) {
		xlmdx = xl - dx;
		xlmdy = xl - dy;
		xrpdx = xr + dx;
		xrpdy = xr + dy;
		yumdy = yu - dy;
		yumdx = yu - dx;
		ydpdx = yd + dx;
		ydpdy = yd + dy;
		DrawHLine(xlmdx, xrpdx, yumdy);
		DrawHLine(xlmdy, xrpdy, yumdx);
		DrawHLine(xlmdy, xrpdy, ydpdx);
		DrawHLine(xlmdx, xrpdx, ydpdy);
		if (d < 0) d += 4 * dx + 6;
		else d += 4 * (dx - --dy) + 10;
		dx++;
	}
	rect.x = x1;
	rect.y = y1 + radius + 1;
	rect.w = x2 - x1 + 1;
	rect.h = y2 - y1 - radius - radius - 1;
	SDL_FillRect(surface_, &rect, drawColor_);
}
