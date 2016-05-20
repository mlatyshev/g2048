#include "Board.h"

namespace Board {

	Board::Board(SDL_Renderer* renderer) {
		renderer_ = renderer;

		tiles[2] = { nullptr,    "2", 0x776E65, 0xEEE4DA };
		tiles[4] = { nullptr,    "4", 0x776E65, 0xEDE0C8 };
		tiles[8] = { nullptr,    "8", 0xF9F9F2, 0xF2B179 };
		tiles[16] = { nullptr,   "16", 0xF9F9F2, 0xF59563 };
		tiles[32] = { nullptr,   "32", 0xF9F9F2, 0xF67C5F };
		tiles[64] = { nullptr,   "64", 0xF9F9F2, 0xF65E3B };
		tiles[128] = { nullptr,  "128", 0xF9F9F2, 0xEDCF72 };
		tiles[256] = { nullptr,  "256", 0xF9F9F2, 0xEDCC61 };
		tiles[512] = { nullptr,  "512", 0xF9F9F2, 0xEDC850 };
		tiles[1024] = { nullptr, "1024", 0xF9F9F2, 0xEDC53f };
		tiles[2048] = { nullptr, "2048", 0xF9F9F2, 0xEDC22E };

		deskTexture = CreateBGTexture(BOARD_SIZE, BOARD_SIZE, RADIUS);

		gameData = GameData::GameData::getInstatce();
	}

	Board::~Board() {
		SDL_DestroyTexture(deskTexture);
		for (std::map<int, Tile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
			if (it->second.texture != nullptr) {
				SDL_DestroyTexture(it->second.texture);
			}
		}
	}

	SDL_Texture* Board::LoadTextureFromFile(std::string path) {
		SDL_Texture* newTexture = nullptr;
		SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
		if (loadedSurface == nullptr) {
			std::cout << "Error SDL_LoadBMB: " << SDL_GetError() << std::endl;
		}
		else {
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
			newTexture = SDL_CreateTextureFromSurface(renderer_, loadedSurface);
			SDL_FreeSurface(loadedSurface);
		}
		return newTexture;
	}

	SDL_Texture * Board::CreateBGTexture(int width, int height, int radius)
	{
		SDLSurface *surface = new SDLSurface();
		surface->CreateSurface(width, height);
		surface->LockSurface();
		//surface->SetDrawColorRGB(0xAD, 0x9D, 0x8F);
		surface->SetDrawColor(0x00AD9D8F);
		surface->DrawRoundRect(0, 0, width, height, radius);
		//surface->SetDrawColorRGB(0xC1, 0xB3, 0xA4);
		surface->SetDrawColor(0x00C1B3A4);
		for (int row = 0; row < 4; row++) {
			for (int column = 0; column < 4; column++) {
				int x = INTERVAL * (column + 1) + column * TILE_SIZE;
				//int x2 = x1 + TILE_SIZE - 1;
				int y = INTERVAL * (row + 1) + row * TILE_SIZE;
				//int y2 = y1 + TILE_SIZE - 1;
				surface->DrawRoundRect(x, y, TILE_SIZE, TILE_SIZE, radius);
			}
		}
		surface->UnlockSurface();
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_, surface->Get());
		delete surface;
		return texture;
	}

	SDL_Texture * Board::CreateTileTexture(int width, int height, int radius, Uint32 bgColor, Uint32 txtColor)
	{
		SDLSurface *surface = new SDLSurface();
		surface->CreateSurface(width, height);
		surface->LockSurface();
		surface->SetDrawColor(bgColor);
		surface->DrawRoundRect(0, 0, width, height, radius);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_, surface->Get());
		delete surface;
		return texture;
	}

	void Board::CreateTileTexture(int tileNumber)
	{
		if (tiles.find(tileNumber) != tiles.end()) {

		}
	}

	void Board::Update() {
	}

	void Board::Render() {

		//	SDL_Rect srcrect;
		SDL_Rect dstrect;
		SDL_Texture *tileTexture;

		dstrect.x = 0;
		dstrect.y = 0;
		dstrect.w = BOARD_SIZE;
		dstrect.h = BOARD_SIZE;
		SDL_RenderCopy(renderer_, deskTexture, 0, &dstrect);

		for (int row = 0; row < DATA_SIZE; row++) {
			for (int column = 0; column < DATA_SIZE; column++) {
				switch (gameData->GetValue(row, column)) {
				//case 2: tileTexture = tile2Texture; break;
				//case 4: tileTexture = tile4Texture; break;
				//case 8: tileTexture = tile8Texture; break;
				//case 16: tileTexture = tile16Texture; break;
				//case 32: tileTexture = tile32Texture; break;
				//case 64: tileTexture = tile64Texture; break;
				//case 128: tileTexture = tile128Texture; break;
				//case 256: tileTexture = tile256Texture; break;
				//case 512: tileTexture = tile512Texture; break;
				//case 1024: tileTexture = tile1024Texture; break;
				//case 2048: tileTexture = tile2048Texture; break;
				default: tileTexture = nullptr;
				}
				if (tileTexture != nullptr) {
					dstrect.x = column * TILE_SIZE + INTERVAL * (column + 1);
					dstrect.y = row * TILE_SIZE + INTERVAL * (row + 1);
					dstrect.w = TILE_SIZE;
					dstrect.h = TILE_SIZE;
					SDL_RenderCopy(renderer_, tileTexture, 0, &dstrect);
				}
			}
		}
	}

}