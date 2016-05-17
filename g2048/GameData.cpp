#include "GameData.h"

GameData* GameData::p_instance = 0;

/*
\
\
\
\
\
\
*/
int GameData::GetValue(int row, int column) {
	if (row >=0 && row < DATA_SIZE && column >= 0 && column < DATA_SIZE) {
		return tiles[row][column].value;
	}
	return -1;
}

void GameData::SetValue(int row, int column, int value) {
	if (row >=0 && row < DATA_SIZE && column >= 0 && column < DATA_SIZE) {
		tiles[row][column].value = value;
	}
}