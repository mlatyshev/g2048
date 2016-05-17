#pragma once

#include <SDL2\SDL.h>

#define DEFAULT_DEPTH 32
#define DEFAULT_RMASK 0
#define DEFAULT_GMASK 0
#define DEFAULT_BMASK 0
#define DEFAULT_AMASK 0xFF

class SDLSurface
{
private:
	SDL_Surface *surface_;
	int width_;
	int height_;
	int depth_;
	Uint32 drawColor_;
public:
	SDLSurface();
	~SDLSurface();

	void Free();

	int CreateRGBSurface(Uint32 flags,int width,int height, int depth, Uint32 Rmask,Uint32 Gmask,Uint32 Bmask,Uint32 Amask);
	int CreateSurface(int width, int height);
	SDL_Surface *Get();
	void SetDrawColor(Uint32 color);
	void SetDrawColorRGB(Uint32 color, Uint8 r, Uint8 g, Uint8 b);
	void LockSurface();
	void UnlockSurface();
	void PutPixel32(int x, int y);
	void DrawHLine(int x1, int x2, int y);
	void DrawRoundRect(Uint16 x1, Uint16 x2, Uint16 y1, Uint16 y2, Uint16 radius);
};