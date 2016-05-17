#include "Board.h"

void PutPixel32() {
	//
}

Board::Board(SDL_Renderer* renderer): Entity(renderer) {

	deskTexture = LoadTextureFromFile("Img\\background.bmp");
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
	if ( loadedSurface == nullptr ) {
		std::cout << "Error SDL_LoadBMB: " << SDL_GetError() << std::endl;
	} else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}

void Board::Update() {
}

void Board::Render() {

//	SDL_Rect srcrect;
	SDL_Rect dstrect;
	SDL_Texture *tileTexture;

	dstrect.x = 0;
	dstrect.y = 0;
	dstrect.w = BOARD_WIDTH;
	dstrect.h = BOARD_HEIGHT;
	SDL_RenderCopy(renderer, deskTexture, 0, &dstrect);

	for (int row = 0; row < DATA_SIZE; row++){
		for (int column = 0; column < DATA_SIZE; column++) {
			dstrect.x = column * TILE_WIDTH + 18 * (column + 1);
			dstrect.y = row * TILE_WIDTH + 18 * (row + 1);
			dstrect.w = TILE_WIDTH;
			dstrect.h = TILE_WIDTH;
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
			if (tileTexture != nullptr) SDL_RenderCopy(renderer, tileTexture, 0, &dstrect);
		}
	}
}