#include "Game.h"

Game::Game() {
	window_ = nullptr;
	renderer_ = nullptr;

	srand((unsigned int)time(NULL));

	gameData = GameData::getInstatce();
}

Game::~Game() {
	Clean();
	SDL_Quit();
}

bool Game::Init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
		return false;
	}

	window_ = SDL_CreateWindow("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 474, 474, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (window_ == nullptr) {
		std::cout << "Error creating window: " << SDL_GetError() << std::endl;
		return false;
	}

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (renderer_ == nullptr) {
		std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window_);
		return false;
	}

	return true;
}

void Game::Clean() {
	// clean resources
//	SDL_DestroyTexture(texture);

	// clean renderer and window
	if (renderer_ != nullptr) {
		SDL_DestroyRenderer(renderer_);
		renderer_ = nullptr;
	}
	if (window_ != nullptr) {
		SDL_DestroyWindow(window_);
		window_ = nullptr;
	}
}

void Game::onQuit() {
	isRunning = false;
}

void Game::onKeyDown(SDL_Event* e) {
	if (e->key.repeat = 0) {
		keys[e->key.keysym.sym] = 1;
	}
}

void Game::onKeyUp(SDL_Event* e) {
	keys[e->key.keysym.sym] = 0;
}

void Game::Run() {
	board = new Board(renderer_);

	NewGame();

	SDL_Event e;

	// main loop
	while(isRunning) {
		// handler events
		if (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				{
					onQuit();
					break;
				}
			case SDL_KEYDOWN:
				{
					onKeyDown(&e);
					break;
				}
			case SDL_KEYUP:
				{
					onKeyUp(&e);
					break;
				}
			}
		}

		// Обновление и перерисовка игры
		Update();
		Render();
	}

	delete board;

	Clean();

	SDL_Quit();
}

void Game::MoveLeft() {
	for ( int row = 0; row < DATA_SIZE; row++ ) {
		// Проверяемая (опорная) ячейка
		int pivot = 0;
		// Текущая ячейка
		int column = 1;
		while ( column < DATA_SIZE ) {
			// Если текущая ячейка пустая, то переходим на следующую
			if ( gameData->GetValue(row, column) == 0 ) {
				column++;
			}
			// Если опорная ячейка пустая, то переносим в неё значение из текущей ячейки
			else if ( gameData->GetValue(row, pivot) == 0 ) {
				gameData->SetValue( row, pivot, gameData->GetValue(row, column) );
				gameData->SetValue( row, column, 0 );
				column++;
			}
			// Если значения опорной и текущей ячеек совпадают, то 
			// складываем их и переходим к следующей ячейке
			else if ( gameData->GetValue(row, pivot) == gameData->GetValue(row, column) ) {
				gameData->SetValue( row, pivot, gameData->GetValue(row, pivot) + gameData->GetValue(row, column) );
				gameData->SetValue( row, column, 0 );
				pivot++;
				column++;
			}
			// Нечего двигать, продолжаем
			else if (++pivot == column) {
				column++;
			}
		}
	}
}

void Game::MoveRight() {
	for ( int row = 0; row < DATA_SIZE; row++ ) {
		// Проверяемая (опорная) ячейка
		int pivot = 3;
		// Текущая ячейка
		int column = 2;
		while ( column >= 0 ) {
			// Если текущая ячейка пустая, то переходим на следующую
			if ( gameData->GetValue(row, column) == 0 ) {
				column--;
			}
			// Если опорная ячейка пустая, то переносим в неё значение из текущей ячейки
			else if ( gameData->GetValue(row, pivot) == 0 ) {
				gameData->SetValue( row, pivot, gameData->GetValue(row, column) );
				gameData->SetValue( row, column, 0 );
				column--;
			}
			// Если значения опорной и текущей ячеек совпадают, то 
			// складываем их и переходим к следующей ячейке
			else if ( gameData->GetValue(row, pivot) == gameData->GetValue(row, column) ) {
				gameData->SetValue( row, pivot, gameData->GetValue(row, pivot) + gameData->GetValue(row, column) );
				gameData->SetValue( row, column, 0 );
				pivot--;
				column--;
			}
			// Нечего двигать, продолжаем
			else if (--pivot == column) {
				column--;
			}
		}
	}
}

void Game::MoveUp() {
	for ( int column = 0; column < DATA_SIZE; column++ ) {
		// Проверяемая (опорная) ячейка
		int pivot = 0;
		// Текущая ячейка
		int row = 1;
		while ( row < DATA_SIZE ) {
			// Если текущая ячейка пустая, то переходим на следующую
			if ( gameData->GetValue(row, column) == 0 ) {
				row++;
			}
			// Если опорная ячейка пустая, то переносим в неё значение из текущей ячейки
			else if ( gameData->GetValue(pivot, column) == 0 ) {
				gameData->SetValue( pivot, column, gameData->GetValue(row, column) );
				gameData->SetValue( row, column, 0 );
				row++;
			}
			// Если значения опорной и текущей ячеек совпадают, то 
			// складываем их и переходим к следующей ячейке
			else if ( gameData->GetValue(pivot, column) == gameData->GetValue(row, column) ) {
				gameData->SetValue( pivot, column, gameData->GetValue(pivot, column) + gameData->GetValue(row, column) );
				gameData->SetValue( row, column, 0 );
				pivot++;
				row++;
			}
			// Нечего двигать, продолжаем
			else if (++pivot == row) {
				row++;
			}
		}
	}
}

void Game::MoveDown() {
	for ( int column = 0; column < DATA_SIZE; column++ ) {
		// Проверяемая (опорная) ячейка
		int pivot = 3;
		// Текущая ячейка
		int row = 2;
		while ( row >= 0 ) {
			// Если текущая ячейка пустая, то переходим на следующую
			if ( gameData->GetValue(row, column) == 0 ) {
				row--;
			}
			// Если опорная ячейка пустая, то переносим в неё значение из текущей ячейки
			else if ( gameData->GetValue(pivot, column) == 0 ) {
				gameData->SetValue( pivot, column, gameData->GetValue(row, column) );
				gameData->SetValue( row, column, 0 );
				row--;
			}
			// Если значения опорной и текущей ячеек совпадают, то 
			// складываем их и переходим к следующей ячейке
			else if ( gameData->GetValue(pivot, column) == gameData->GetValue(row, column) ) {
				gameData->SetValue( pivot, column, gameData->GetValue(pivot, column) + gameData->GetValue(row, column) );
				gameData->SetValue( row, column, 0 );
				pivot--;
				row--;
			}
			// Нечего двигать, продолжаем
			else if (--pivot == row) {
				row--;
			}
		}
	}
}

void Game::Update() {
	if ( keys[SDLK_LEFT] && isCanMoveLeft ) {
		// Состояние игры перед ходом
		//PrintStatus();
		//std::cout << "Move left" << std::endl;
		MoveLeft();
		keys[SDLK_LEFT] = 0;
		// Состояние игры после хода
		//PrintStatus();
		SpawnNumber();
	}
	if ( keys[SDLK_RIGHT] && isCanMoveRight ) {
		// Состояние игры перед ходом
		//PrintStatus();
		//std::cout << "Move right" << std::endl;
		MoveRight();
		keys[SDLK_RIGHT] = 0;
		// Состояние игры после хода
		//PrintStatus();
		SpawnNumber();
	}
	if ( keys[SDLK_UP] && isCanMoveUp ) {
		// Состояние игры перед ходом
		//PrintStatus();
		//std::cout << "Move up" << std::endl;
		MoveUp();
		keys[SDLK_UP] = 0;
		// Состояние игры после хода
		//PrintStatus();
		SpawnNumber();
	}
	if ( keys[SDLK_DOWN] && isCanMoveDown ) {
		// Состояние игры перед ходом
		//PrintStatus();
		//std::cout << "Move down" << std::endl;
		MoveDown();
		keys[SDLK_DOWN] = 0;
		// Состояние игры после хода
		//PrintStatus();
		SpawnNumber();
	}
}

void Game::Render() {
	SDL_RenderClear(renderer_);

	board->Render();

	SDL_RenderPresent(renderer_);
}

void Game::NewGame() {
	for (int row = 0; row < DATA_SIZE; row++) {
		for (int column = 0; column < DATA_SIZE; column++) {
			gameData->SetValue(row, column, 0);
		}
	}
	//gameData->SetValue(0, 0, 16);
	//gameData->SetValue(0, 1, 8);
	//gameData->SetValue(0, 2, 4);
	//gameData->SetValue(0, 3, 2);
	//gameData->SetValue(1, 0, 16);
	//gameData->SetValue(1, 1, 8);
	//gameData->SetValue(1, 2, 4);
	//gameData->SetValue(1, 3, 2);
	//gameData->SetValue(2, 0, 16);
	//gameData->SetValue(2, 1, 8);
	//gameData->SetValue(2, 2, 4);
	//gameData->SetValue(2, 3, 2);
	//gameData->SetValue(3, 0, 16);
	//gameData->SetValue(3, 1, 8);
	//gameData->SetValue(3, 2, 4);
	//gameData->SetValue(3, 3, 2);
	SpawnNumber();
	this->isRunning = true;
}

void Game::SpawnNumber() {
	bool flag = true;
	int randomNumbers[] = {0, 0, 1, 0, 0, 1, 0, 0, 0, 0};
	int randomSize = sizeof(randomNumbers) / sizeof(int);
	while (flag) {
		for (int row = 0; row < DATA_SIZE && flag; row++) {
			for (int column = 0; column < DATA_SIZE && flag; column++) {
				if (gameData->GetValue(row, column) == 0) {
					int rr = randomNumbers[rand() % randomSize];
					if (rr == 1) {
						gameData->SetValue(row, column, 2);
						flag = false;
						//std::cout << "SpawnNumber: row = " << row << "; column = " << column << std::endl;
					}
				}
			}
		}
	}
	ifGameOver();
}

bool Game::doMoveLeft() {
	for( int row = 0; row < DATA_SIZE; row++ ) {
		// Проверяемая (опорная) ячейка
		int pivot = 0;
		// Текущая ячейка
		int column = 1;
		while ( column < DATA_SIZE ) {
			// Если текущая ячейка пустая, то переходим на следующую
			if ( gameData->GetValue(row, column) == 0 ) {
				column++;
			}
			// Если опорная ячейка пустая, то можно перенести в неё значение из текущей ячейки
			else if ( gameData->GetValue(row, pivot) == 0 ) {
				return true;
			}
			// Если значения опорной и текущей ячеек совпадают,
			// то можно сложить их
			else if ( gameData->GetValue(row, pivot) == gameData->GetValue(row, column) ) {
				return true;
			}
			// Нечего двигать, продолжаем
			else if (++pivot == column) {
				column++;
			}
		}
	}
	return false;
}

bool Game::doMoveRight() {
	for( int row = 0; row < DATA_SIZE; row++ ) {
		// Проверяемая (опорная) ячейка
		int pivot = 3;
		// Текущая ячейка
		int column = 2;
		while ( column >= 0 ) {
			// Если текущая ячейка пустая, то переходим на следующую
			if ( gameData->GetValue(row, column) == 0 ) {
				column--;
			}
			// Если опорная ячейка пустая, то можно перенести в неё значение из текущей ячейки
			else if ( gameData->GetValue(row, pivot) == 0 ) {
				return true;
			}
			// Если значения опорной и текущей ячеек совпадают,
			// то можно сложить их
			else if ( gameData->GetValue(row, pivot) == gameData->GetValue(row, column) ) {
				return true;
			}
			// Нечего двигать, продолжаем
			else if (--pivot == column) {
				column--;
			}
		}
	}
	return false;
}

bool Game::doMoveUp() {
	for( int column = 0; column < DATA_SIZE; column++ ) {
		// Проверяемая (опорная) ячейка
		int pivot = 0;
		// Текущая ячейка
		int row = 1;
		while ( row < DATA_SIZE ) {
			// Если текущая ячейка пустая, то переходим на следующую
			if ( gameData->GetValue(row, column) == 0 ) {
				row++;
			}
			// Если опорная ячейка пустая, то можно перенести в неё значение из текущей ячейки
			else if ( gameData->GetValue(pivot, column) == 0 ) {
				return true;
			}
			// Если значения опорной и текущей ячеек совпадают,
			// то можно сложить их
			else if ( gameData->GetValue(pivot, column) == gameData->GetValue(row, column) ) {
				return true;
			}
			// Нечего двигать, продолжаем
			else if (++pivot == row) {
				row++;
			}
		}
	}
	return false;
}

bool Game::doMoveDown() {
	for( int column = 0; column < DATA_SIZE; column++ ) {
		// Проверяемая (опорная) ячейка
		int pivot = 3;
		// Текущая ячейка
		int row = 2;
		while ( row >= 0 ) {
			// Если текущая ячейка пустая, то переходим на следующую
			if ( gameData->GetValue(row, column) == 0 ) {
				row--;
			}
			// Если опорная ячейка пустая, то можно перенести в неё значение из текущей ячейки
			else if ( gameData->GetValue(pivot, column) == 0 ) {
				return true;
			}
			// Если значения опорной и текущей ячеек совпадают,
			// то можно сложить их
			else if ( gameData->GetValue(pivot, column) == gameData->GetValue(row, column) ) {
				return true;
			}
			// Нечего двигать, продолжаем
			else if (--pivot == row) {
				row--;
			}
		}
	}
	return false;
}

void Game::ifGameOver() {
	isCanMoveLeft = doMoveLeft();
	//std::cout << "isCanMoveLeft = " << isCanMoveLeft << std::endl;
	isCanMoveRight = doMoveRight();
	//std::cout << "isCanMoveRight = " << isCanMoveRight << std::endl;
	isCanMoveUp = doMoveUp();
	//std::cout << "isCanMoveUp = " << isCanMoveUp << std::endl;
	isCanMoveDown = doMoveDown();
	//std::cout << "isCanMoveDown = " << isCanMoveDown << std::endl;
	isGameOwer = !isCanMoveLeft && !isCanMoveRight && !isCanMoveUp && !isCanMoveDown;
	//std::cout << "isGameOwer = " << isGameOwer << std::endl;
}

void Game::PrintStatus() {
	for ( int row = 0; row < DATA_SIZE; row++ ) {
		for ( int column = 0; column < DATA_SIZE; column++ ) {
			std::cout << gameData->GetValue(row, column) << " ";
		}
		std::cout << std::endl;
	}
}