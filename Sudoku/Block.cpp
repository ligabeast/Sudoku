#include "Block.h"
#include <iostream>

Block::Block(short (&c)[3][3]) {

	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			this->i[x][y] = c[x][y];
		}
	}
}

bool Block::numberDontExists(short tmp) {
	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 3; b++) {
			if (this->i[a][b] == tmp) {
				return false;
			}
		}
	}
	return true;
}

void Block::setBlock(short arr[3][3]) {
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			this->i[x][y] = arr[x][y];
		}
	}
}

Block::Block() {
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			this->i[x][y] = 0;
		}
	}
}

bool Block::change(short x, short y, short value) {
	if (x < 0 || y < 0 || x > 2 || y > 2) { return false; }
	this->i[x][y] = value;
	return true;
}

short Block::getValue(short x, short y) {
	return this->i[x][y];
}

Block& Block::copy(const Block& c) {
	for (short row = 0; row < 3; row++) {
		for (short col = 0; col < 3; col++) {
			this->i[row][col] = c.i[row][col];
		}
	}
	return *this;
}

int Block::getSumOfBlankCells() {
	int c = 0;
	for (short row = 0; row < 3; row++) {
		for (short col = 0; col < 3; col++) {
			if (this->i[row][col] == 0) { c++; }
		}
	}
	return c;
}

void Block::print() {
	for (short r = 0; r < 3; r++) {
		for (short c = 0; c < 3; c++) {
			std::cout << " " <<  getValue(r, c) << " ";
			if (c < 2) {
				std::cout << "|";
			}
		}
		std::cout << std::endl;
	}
}