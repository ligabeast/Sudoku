#include "MainFrame.h"
#include <queue>
#include <thread>
using namespace std;

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	instance = new Sudoku();
	mode = 0; // easy

	wxFont font;
	font.SetPointSize(10);
	font.SetWeight(wxFONTWEIGHT_BOLD);

	wxPanel* rightside = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(400, 200));
	rightside->SetBackgroundColour(*wxBLUE);

	wxBoxSizer* MainSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* LeftSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* RightSizer = new wxBoxSizer(wxVERTICAL);

	MainSizer->Add(LeftSizer, 2, wxEXPAND, 10);
	MainSizer->Add(rightside, 1, wxEXPAND, 10);

	this->SetSizerAndFit(MainSizer);
	this->SetInitialSize(wxSize(1000, 600));

	Difficulty_buttons = new wxButton * [3];
	Sudoku_buttons = new wxButton * [81];

	wxGridSizer* grid_Difficulty = new wxGridSizer(1, 4, 5, 5);
	wxGridSizer* sudoku = new wxGridSizer(3, 3, 0, 0);

	LeftSizer->Add(grid_Difficulty, 0, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
	LeftSizer->Add(sudoku, 1, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);


	label_Difficulty = new wxStaticText(this, wxID_ANY, "Difficulty:");
	label_Difficulty->SetFont(font);
	grid_Difficulty->Add(label_Difficulty, 0, wxALIGN_CENTER);

	Difficulty_buttons[0] = new wxButton(this, wxID_ANY, "easy", wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	Difficulty_buttons[0]->SetBackgroundColour(*wxBLUE);
	Difficulty_buttons[0]->SetForegroundColour(*wxWHITE);
	Difficulty_buttons[1] = new wxButton(this, wxID_ANY, "medium", wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	Difficulty_buttons[2] = new wxButton(this, wxID_ANY, "hard", wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);

	for (int i = 0; i < 3; i++) {
		Difficulty_buttons[i]->SetFont(font);
		Difficulty_buttons[i]->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::changeDifficulty), NULL, this);
	}

	for (int i = 0; i < 3; i++) {
		grid_Difficulty->Add(Difficulty_buttons[i], 1, wxEXPAND | wxALL);
	}

	for (int i = 0; i < 81; i++) {
		Sudoku_buttons[i] = new wxButton(this, wxID_ANY, " ", wxDefaultPosition, wxSize(20, 20), 0);
	}

	for (int i = 0; i < 9; i++) {

		wxGridSizer* tmp = new wxGridSizer(3, 3, 0, 0);
		for (int x = 0; x < 9; x++) {
			tmp->Add(Sudoku_buttons[i * 9 + x], 0, wxALL | wxEXPAND, 0);
		}
		sudoku->Add(tmp, 1, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
	}
	this->SetSizer(MainSizer);

	thread* easy = new thread(&MainFrame::bufferNextGridEasy, this);
	thread* medium = new thread(&MainFrame::bufferNextGridMedium, this);
	thread* hard = new thread(&MainFrame::bufferNextGridHard, this);


}

void MainFrame::changeDifficulty(wxCommandEvent& event) {

	string pressed = wxDynamicCast(event.GetEventObject(), wxButton)->GetLabel().ToStdString();

	if ((pressed == "easy" && mode == 0) || (pressed == "medium" && mode == 1) || (pressed == "hard" && mode == 2)) {
		return;
	}

	Difficulty_buttons[mode]->SetBackgroundColour(*wxWHITE);
	Difficulty_buttons[mode]->SetForegroundColour(*wxBLACK);


	if (pressed == "easy") {
		mode = 0;
	}
	else if (pressed == "medium") {
		mode = 1;
	}
	else {
		mode = 2;
	}

	Difficulty_buttons[mode]->SetBackgroundColour(*wxBLUE);
	Difficulty_buttons[mode]->SetForegroundColour(*wxWHITE);
}

void MainFrame::bufferNextGridEasy() {
	Sudoku tmp;
	tmp.changeDifficulty(40, 44);

	while (true) {
		while (instance->easyGrid->size() < 3) {
			tmp.generateSudoku();
			instance->easyGrid->push_back(tmp);
		}
		this_thread::sleep_for(10s);
	}
}

void MainFrame::bufferNextGridMedium() {
	Sudoku tmp;
	tmp.changeDifficulty(45, 49);

	while (true) {
		while (instance->mediumGrid->size() < 3) {
			tmp.generateSudoku();
			instance->mediumGrid->push_back(tmp);
		}
		this_thread::sleep_for(10s);
	}
}
void MainFrame::bufferNextGridHard() {
	Sudoku tmp;
	tmp.changeDifficulty(50, 54);

	while (true) {
		while (instance->hardGrid->size() < 3) {
			tmp.generateSudoku();
			instance->hardGrid->push_back(tmp);
		}
		this_thread::sleep_for(10s);
	}
}



