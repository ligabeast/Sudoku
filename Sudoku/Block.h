#pragma once

class Block {
private:
	short i[3][3];
public:

	Block();
	Block(short(&c)[3][3]);
	bool change(short x, short y, short value);
	short getValue(short x, short y);
	void print();
};