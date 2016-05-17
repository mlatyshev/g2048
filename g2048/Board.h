#pragma once

#include <SDL2\SDL.h>

#include "GameData.h"

#include <iostream>
#include <string>

#define BOARD_WIDTH 474
#define BOARD_HEIGHT 474

#define TILE_WIDTH 96
#define TILE_HEIGHT 96

class Board {
public:
	Board(SDL_Renderer* renderer);
	~Board();

	SDL_Texture* LoadTextureFromFile(std::string path);

	void Update();
	void Render();
private:
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