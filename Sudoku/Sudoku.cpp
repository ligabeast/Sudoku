#include "Sudoku.h"
#include <iostream>
#include <iomanip>

Block& Sudoku::findBlock(short x, short y) {
	short row = int(x / 3);
	short col = int(y / 3);
	return this->sudoku[((row * 3) + col)];
}

bool Sudoku::changeValue(short x, short y, short value) {
	if (x < 0 || x > 8 || y < 0 || y > 8) { return false; }
	short row_block = x % 3;
	short col_block = y % 3;
	findBlock(x, y).change(row_block, col_block, value);
	return true;
}

Sudoku::Sudoku() {

}

void Sudoku::generateSudoku() {


}

void Sudoku::print() {
	for (short x = 0; x < 9; x++) {
		if (x % 3 == 0) {
			std::cout << std::setfill('-') << std::setw(35) << "" << std::endl;
		}
		for (short y = 0; y < 9; y++) {
			short row_block = x % 3;
			short col_block = y % 3;
			std::cout << " " << this->findBlock(x, y).getValue(row_block, col_block) << " ";
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
