#pragma once
#include "Block.h"

class Sudoku {
private:
	Block sudoku[9];
	int D = 50;
	Block& findBlock(short x, short y);
	bool checkRow(int row, int number);
	bool checkColumn(int column, int number);
public:
	Sudoku();
	bool changeValue(short x, short y, short value);
	void generateSudoku();
	void changeDifficulty(short a);
	void print();
};