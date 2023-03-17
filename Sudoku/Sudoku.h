#pragma once
#include "Block.h"
#include <vector>

class Sudoku {
private:
	Block sudoku[9];
	int maxCells;
	int minCells;
	Block& findBlock(short x, short y);
	bool checkRow(int row, int number);
	bool checkColumn(int column, int number);
	std::vector<int> findPlacebles(int row, int col);
	void getNextEmptyCell(int& row, int& col);
public:
	Sudoku();
	Sudoku(const Sudoku& cpy);
	int sumBlankCells();
	bool changeValue(short x, short y, short value);
	void generateSudoku();
	void changeDifficulty(short min, short max);
	void print();
	void printSudoku();
	bool solveSudoku(int row, int col);
	bool checkSudoku(int row, int col, int number);
	int QuantityOfSolutions(int row, int col);
	short getValue(short x, short y);
	void initializeSudoku();
};