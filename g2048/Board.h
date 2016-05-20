#pragma once

#include <SDL2\SDL.h>

#include "GameData.h"
#include "SDLSurface.h"

#include <iostream>
#include <string>
#include <map>

namespace Board {

#define TILE_SIZE 96
#define INTERVAL 18
#define BOARD_SIZE TILE_SIZE * 4 + INTERVAL * 5
#define RADIUS 8

	struct Tile {
		SDL_Texture *texture;
		std::string text;
		Uint32 txtColor;
		Uint32 bgColor;
	};

	class Board {
	public:
		Board(SDL_Renderer *renderer);
		~Board();

		SDL_Texture *LoadTextureFromFile(std::string path);
		SDL_Texture *CreateBGTexture(int width, int height, int radius);
		SDL_Texture *CreateTileTexture(int width, int height, int radius, Uint32 bgColor, Uint32 txtColor);
		void CreateTileTexture(int tileNumber);

		void Update();
		void Render();
	private:
		SDL_Texture *deskTexture;
		std::map<int, Tile> tiles;
		SDL_Renderer *renderer_;

		GameData::GameData *gameData;
	};

}