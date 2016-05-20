#pragma once

#include <SDL2\SDL.h>
#include <ctime>
#include <map>

#include "Board.h"
#include "GameData.h"

class Game {
public:
	Game();
	~Game();

	bool Init();
	void Run();
private:
	SDL_Window *window_;
	SDL_Renderer *renderer_;
	SDL_Texture *texture = nullptr;

	Board::Board *board = nullptr;
	GameData::GameData *gameData;

	bool isRunning = false;
	bool isCanSpawn;
	bool isCanMoveLeft = false;
	bool isCanMoveRight = false;
	bool isCanMoveUp = false;
	bool isCanMoveDown = false;
	bool isGameOwer = true;

	std::map<int, int> keys;

	void onQuit();
	void onKeyDown(SDL_Event* e);
	void onKeyUp(SDL_Event* e);

	void Clean();
	void Update();
	void Render();

	void NewGame();
	void SpawnNumber();
	void ifGameOver();
	bool doMoveLeft();
	bool doMoveRight();
	bool doMoveUp();
	bool doMoveDown();

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	// Debug functions
	void PrintStatus();
};