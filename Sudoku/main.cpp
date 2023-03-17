#include <iostream> 
#include "Sudoku.h"
#include <iomanip>
using namespace std;


int main() {

	short choose = 1;
	Sudoku* obj = new Sudoku;

	while (choose != 99) {
		cout << setfill('-') << setw(10) << "Sudoku" << setfill('-') << setw(10) << "" <<  endl;
		cout << "1.Print" << endl;
		cout << "2.Change Value" << endl;
		cout << "3.Generate new" << endl;
		cout << "4.Initialize Sudoku" << endl;
		cout << "5.Solve Sudoku" << endl;
		cout << "99.Exit" << endl;
		cout << "Input ?=";
		cin >> choose;

		switch (choose) {
		case 1:
			obj->print();
			break;
		case 2: {
			cout << "Please say which index (row, column)" << endl;
			cout << "First row=";
			short row;
			cin >> row;
			cout << "Second column=";
			short column;
			cin >> column;
			cout << "Which Value should it be set?=";
			short value;
			cin >> value;
			obj->changeValue(row, column, value);
			break;
		}
		case 3:
			obj->generateSudoku();
			//obj->printSudoku();
			break;
		case 4:
			obj->initializeSudoku();
			break;

		case 5:
			obj->solveSudoku(0,0);
			break;
		}

		cout << setfill('-') << setw(26) << endl;
		cout << endl << endl;
	}


	system("PAUSE");
	return 0;
}