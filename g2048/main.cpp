#include "main.h"

int main(int argc, char* argv[]) {
	// Создание объекта игры
	Game* game = new Game();

	// Инициализация и запуск игры
	if (game->Init()) {
		game->Run();
	}

	// Очистка
	delete game;

	return 0;
}