#pragma once

#include <SDL.h>
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
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;

	Board* board = nullptr;
	GameData* gameData = nullptr;

	bool isRunning = false;
	bool isCanSpawn;
	bool isCanMoveLeft = false;
	bool isCanMoveRight = false;
	bool isCanMoveUp = false;
	bool isCanMoveDown = false;
	bool isGameOwer = true;

	std::map<int, int> keys;
	std::map<int, int> pressedKeys;

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