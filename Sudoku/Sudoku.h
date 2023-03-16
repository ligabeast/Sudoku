#pragma once
#include "Block.h"

class Sudoku {
private:
	Block sudoku[9];
	Block& findBlock(short x, short y);
public:
	Sudoku();
	bool changeValue(short x, short y, short value);
	void generateSudoku();
	void print();
};