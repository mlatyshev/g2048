#pragma once

#include <SDL2\SDL.h>

#include "GameData.h"
#include "SDLSurface.h"

#include <iostream>
#include <string>

//#define BOARD_SIZE 474
#define TILE_SIZE 96
#define INTERVAL 18
#define BOARD_SIZE TILE_SIZE * 4 + INTERVAL * 5
#define RADIUS 8

class Board {
public:
	Board(SDL_Renderer* renderer);
	~Board();

	SDL_Texture* LoadTextureFromFile(std::string path);
	SDL_Texture *CreateBGTexture(int width, int height, int radius);

	void Update();
	void Render();
private:
	SDL_Renderer *renderer_;
	SDL_Texture* deskTexture;
	SDL_Texture* tile2Texture;
	SDL_Texture* tile4Texture;
	SDL_Texture* tile8Texture;
	SDL_Texture* tile16Texture;
	SDL_Texture* tile32Texture;
	SDL_Texture* tile64Texture;
	SDL_Texture* tile128Texture;
	SDL_Texture* tile256Texture;
	SDL_Texture* tile512Texture;
	SDL_Texture* tile1024Texture;
	SDL_Texture* tile2048Texture;

	GameData* gameData;
};