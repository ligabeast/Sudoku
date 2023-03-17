#pragma once
#include "Block.h"
#include <vector>

class Sudoku {
private:
	Block sudoku[9];
	int D = 50;
	Block& findBlock(short x, short y);
	bool checkRow(int row, int number);
	bool checkColumn(int column, int number);
	std::vector<int> findPlacebles(int row, int col);
	void getNextEmptyCell(int& row, int& col);
public:
	Sudoku();
	bool changeValue(short x, short y, short value);
	void generateSudoku();
	void changeDifficulty(short a);
	void print();
	void printSudoku();
	bool checkSudoku(int row, int col, int number);
	bool solveSudoku(int row, int col);
	short getValue(short x, short y);
	void initializeSudoku();
};