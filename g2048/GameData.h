#pragma once

#define DATA_SIZE 4

namespace GameData {

	struct Tile {
	public:
		int row, column, value;
		bool isRemoved;
	};

	class GameData {
	public:
		static GameData* getInstatce() {
			if (!p_instance) p_instance = new GameData();
			return p_instance;
		};

		int GetValue(int row, int column);
		void SetValue(int row, int column, int value);
	private:
		static GameData* p_instance;
		GameData() {};
		GameData(const GameData&);
		//GameData& operator= (GameData&);

		Tile tiles[DATA_SIZE][DATA_SIZE];
	};

}