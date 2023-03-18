#pragma once
#include <wx/wx.h>
#include "Sudoku.h"
class MainFrame : public wxFrame
{
private:
	Sudoku* instance;
	int mode;
public:
	MainFrame(const wxString& title);
	wxButton** Difficulty_buttons;
	wxButton** Sudoku_buttons;
	wxStaticText* label_Difficulty;
	void bufferNextGridEasy();
	void bufferNextGridMedium();
	void bufferNextGridHard();
	virtual void changeDifficulty(wxCommandEvent& event);
};

