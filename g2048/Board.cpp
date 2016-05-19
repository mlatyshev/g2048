#include "Board.h"

Board::Board(SDL_Renderer* renderer) {
	renderer_ = renderer;

	//deskTexture = LoadTextureFromFile("Img\\background.bmp");
	deskTexture = CreateBGTexture(BOARD_SIZE, BOARD_SIZE, RADIUS);
	tile2Texture = LoadTextureFromFile("Img\\2.bmp");
	tile4Texture = LoadTextureFromFile("Img\\4.bmp");
	tile8Texture = LoadTextureFromFile("Img\\8.bmp");
	tile16Texture = LoadTextureFromFile("Img\\16.bmp");
	tile32Texture = LoadTextureFromFile("Img\\32.bmp");
	tile64Texture = LoadTextureFromFile("Img\\64.bmp");
	tile128Texture = LoadTextureFromFile("Img\\128.bmp");
	tile256Texture = LoadTextureFromFile("Img\\256.bmp");
	tile512Texture = LoadTextureFromFile("Img\\512.bmp");
	tile1024Texture = LoadTextureFromFile("Img\\1024.bmp");
	tile2048Texture = LoadTextureFromFile("Img\\2048.bmp");

	gameData = GameData::getInstatce();
}

Board::~Board() {
	SDL_DestroyTexture(deskTexture);
	SDL_DestroyTexture(tile2Texture);
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
	surface->SetDrawColorRGB(0xAD, 0x9D, 0x8F);
	surface->DrawRoundRect(0, 0, width, height, radius);
	surface->SetDrawColorRGB(0xC1, 0xB3, 0xA4);
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
			case 2: tileTexture = tile2Texture; break;
			case 4: tileTexture = tile4Texture; break;
			case 8: tileTexture = tile8Texture; break;
			case 16: tileTexture = tile16Texture; break;
			case 32: tileTexture = tile32Texture; break;
			case 64: tileTexture = tile64Texture; break;
			case 128: tileTexture = tile128Texture; break;
			case 256: tileTexture = tile256Texture; break;
			case 512: tileTexture = tile512Texture; break;
			case 1024: tileTexture = tile1024Texture; break;
			case 2048: tileTexture = tile2048Texture; break;
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