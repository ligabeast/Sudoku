#include "Sudoku.h"
#include <iostream>
#include <iomanip>

Block& Sudoku::findBlock(short x, short y) {
	short row = int(x / 3);
	short col = int(y / 3);
	return this->sudoku[((row * 3) + col)];
}

short Sudoku::getValue(short x, short y) {
	short row_block = x % 3;
	short col_block = y % 3;
	return findBlock(x, y).getValue(row_block, col_block);
}

bool Sudoku::changeValue(short x, short y, short value) {
	if (x < 0 || x > 8 || y < 0 || y > 8) { return false; }
	short row_block = x % 3;
	short col_block = y % 3;
	findBlock(x, y).change(row_block, col_block, value);
	return true;
}

Sudoku::Sudoku() {
	this->maxCells = 50;
	this->minCells = 40;
}

Sudoku::Sudoku(const Sudoku& cpy) {
	for (int i = 0; i < 9; i++) {
		this->sudoku[i].copy(cpy.sudoku[i]);
	}
	this->maxCells = cpy.maxCells;
}


void Sudoku::changeDifficulty(short min, short max) { // 40 < easy <= 45, easy < medium <= 45, medium < hard <= 50
	this->minCells = min;
	this->maxCells = max;
}

bool Sudoku::checkRow(int row, int number) {
	for (int x = 0; x < 9; x++) {
		if (this->getValue(row, x) == number) { return false; }
	}
	return true;
}

bool Sudoku::checkColumn(int col, int number) {
	for (int x = 0; x < 9; x++) {
		if (this->getValue(x, col) == number) { return false; }
	}
	return true;
}

void Sudoku::initializeSudoku(){
	short a[3][3] = {
		{ 0,3,0 },
		{ 0,0,0 },
		{ 0,0,8 }
	};
	short b[3][3] = {
		{ 0,0,0 },
		{ 1,9,5 },
		{ 0,0,0 }
	};
	short c[3][3] = {
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,6,0 }
	};
	short d[3][3] = {
		{ 8,0,0 },
		{ 4,0,0 },
		{ 0,0,0 }
	};
	short e[3][3] = {
		{ 0,6,0 },
		{ 8,0,0 },
		{ 0,2,0 }
	};
	short f[3][3] = {
		{ 0,0,0 },
		{ 0,0,1 },
		{ 0,0,0 }
	};
	short g[3][3] = {
		{ 0,6,0 },
		{ 0,0,0 },
		{ 0,0,0 }
	};
	short h[3][3] = {
		{ 0,0,0 },
		{ 4,1,9 },
		{ 0,0,0 }
	};
	short i[3][3] = {
		{ 2,8,0 },
		{ 0,0,5 },
		{ 0,7,0 }
	};
	sudoku[0].setBlock(a);
	sudoku[1].setBlock(b);
	sudoku[2].setBlock(c);
	sudoku[3].setBlock(d);
	sudoku[4].setBlock(e);
	sudoku[5].setBlock(f);
	sudoku[6].setBlock(g);
	sudoku[7].setBlock(h);
	sudoku[8].setBlock(i);
}

void Sudoku::generateSudoku() {
	
	do {
		do {
			for (int i = 0; i < 9; i++) {
				sudoku[i] = Block();
			}
			for (int i = 0; i < 5; i++) {
				for (int row = 0; row < 9; row++) {
					int col = 0;
					int val = 0;
					do {
						col = rand() % 9;
						val = rand() % 9 + 1;
					} while (!(checkSudoku(row, col, val)));
					changeValue(row, col, val);
				}
			}
		} while (QuantityOfSolutions(0, 0) == 0);

		Sudoku tmp(*this);
		tmp.solveSudoku(0, 0);

		do {
			int row = 0;
			int col = 0;
			int oldValue = 0;
			do {
				row = rand() % 9;
				col = rand() % 9;
			} while (this->getValue(row, col) != 0);
			oldValue = this->getValue(row, col);
			this->changeValue(row, col, tmp.getValue(row, col));

			if (QuantityOfSolutions(0, 0) == 0) {
				this->changeValue(row, col, oldValue);
			}
		} while (QuantityOfSolutions(0, 0) > 1);
	} while (!(sumBlankCells() <= this->maxCells && sumBlankCells() >= this->minCells));
}

bool Sudoku::checkSudoku(int row, int col, int number) {
	return (checkColumn(col, number) && checkRow(row, number) && findBlock(row, col).numberDontExists(number));
}

int Sudoku::sumBlankCells() {
	int c = 0;
	for (short i = 0; i < 9; i++) {
		c += this->sudoku[i].getSumOfBlankCells();
	}
	return c;
}

std::vector<int> Sudoku::findPlacebles(int row, int col) {

	std::vector<int> placebles;

	for (int i = 1; i <= 9; i++) {
		if (checkSudoku(row, col, i)) {
			placebles.push_back(i);
		}
	}
	return placebles;
}

void Sudoku::getNextEmptyCell(int& row, int& col) {

	for (int i = (row * 9) + col + 1; i <= 81; i++) {
		int r = ((i-1) / 9);
		int c = ((i-1) % 9);
		if (getValue(r, c) == 0) { row = r; col = c; return; }
	}
	row = 999; // fertig
}

bool Sudoku::solveSudoku(int row, int col) {

	if (getValue(row, col) != 0) {
		getNextEmptyCell(row, col);
	}

	if (row > 8) { return true; }

	std::vector<int> placebles = findPlacebles(row, col);

	if (placebles.size() <= 0) { return false; }

	int oldValue = getValue(row, col);
	getNextEmptyCell(row, col);

	for (auto it = placebles.begin(); it != placebles.end(); it++) {

		changeValue(row, col, *it);
		if (solveSudoku(row, col)) { return true; }
	}
	changeValue(row, col, oldValue);
	return false;
}

int Sudoku::QuantityOfSolutions(int row, int col) {

	if (getValue(row, col) != 0) {
		getNextEmptyCell(row, col);
	}

	if (row > 8) { 
		return 1; 
	}

	std::vector<int> placebles = findPlacebles(row, col);

	if (placebles.size() <= 0) { return false; }

	int oldValue = getValue(row, col);
	getNextEmptyCell(row, col);
	int counter = 0;

	for (auto it = placebles.begin(); it != placebles.end(); it++) {

		changeValue(row, col, *it);
		counter += QuantityOfSolutions(row, col);
	}
	changeValue(row, col, oldValue);
	return counter;
}

void Sudoku::printSudoku() {
	for (short x = 0; x < 9; x++) {
		for (short y = 0; y < 9; y++) {

			if (getValue(x,y) != 0) {
				std::cout << getValue(x,y);
			}
			else{
				std::cout << ".";
			}
		}
	}
}

void Sudoku::print() {
	for (short x = 0; x < 9; x++) {
		if (x % 3 == 0) {
			std::cout << std::setfill('-') << std::setw(35) << "" << std::endl;
		}
		for (short y = 0; y < 9; y++) {
			short row_block = x % 3;
			short col_block = y % 3;
			std::cout << " " << this->getValue(x,y) << " ";
			if ((y+1) % 3 == 0) {
				std::cout << " ";
			}
			else if (y < 8) {
				std::cout << "|";
			}
			
		}
		std::cout << std::endl;
	}
	std::cout << std::setfill('-') << std::setw(35) << "" << std::endl;
}
