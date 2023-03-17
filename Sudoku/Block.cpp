#include "Block.h"
#include <iostream>

Block::Block(short (&c)[3][3]) {

	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			this->i[x][y] = c[x][y];
		}
	}
}

bool Block::NumberDontExists(short tmp) {
	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 3; b++) {
			if (this->i[a][b] == tmp) {
				return false;
			}
		}
	}
	return true;
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