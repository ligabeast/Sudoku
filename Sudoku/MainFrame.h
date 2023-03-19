#pragma once
#include <wx/wx.h>
#include "Sudoku.h"
class MainFrame : public wxFrame
{
private:
	Sudoku* instance;
	int mode;
	std::clock_t start = std::clock();
	wxStaticText* Quantity;
	wxButton* selected;
	bool* timer;
public:
	MainFrame(const wxString& title);
	wxButton** Difficulty_buttons;
	wxButton** Sudoku_buttons;
	wxStaticText* Time;
	wxStaticText* label_Difficulty;
	void bufferNextGrid();
	void update_Timer();
	void loadSudokuField();
	void updateValue(int row, int col, int val);
	void print();
	void boostStart();
	void finished();

	virtual void changeDifficulty(wxCommandEvent& event);
	virtual void input(wxCommandEvent& event);
	virtual void selectField(wxCommandEvent& event);
	virtual void generate(wxCommandEvent& event);
	virtual void solve(wxCommandEvent& event);
	virtual void deleteCell(wxCommandEvent& event);
};

