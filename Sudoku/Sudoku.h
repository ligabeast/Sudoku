#pragma once
#include "Block.h"
#include <vector>
#include <queue>
#include <thread>

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
	std::deque<Sudoku>* hardGrid;
	std::deque<Sudoku>* mediumGrid;
	std::deque<Sudoku>* easyGrid;
	Sudoku();
	Sudoku(const Sudoku& cpy);
	int sumBlankCells();
	void cpySudokuField(const Sudoku& cpy);
	bool changeValue(short x, short y, short value);
	void generateSudoku();
	void setSudoku(int Difficulty);
	void changeDifficulty(short min, short max);
	void print();
	bool solveSudoku(int row, int col);
	bool checkSudoku(int row, int col, int number);
	int QuantityOfSolutions(int row, int col);
	short getValue(short x, short y);
};

enum {
	myID_NEXT
};