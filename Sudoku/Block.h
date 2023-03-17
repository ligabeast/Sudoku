#pragma once

class Block {
private:
	short i[3][3];
public:

	Block();
	Block(short(&c)[3][3]);
	bool change(short x, short y, short value);
	void setBlock(short arr[3][3]);
	short getValue(short x, short y);
	bool numberDontExists(short tmp);
	void print();
};