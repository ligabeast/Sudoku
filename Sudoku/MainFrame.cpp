#include "MainFrame.h"
#include <queue>
#include <thread>
#include <chrono>

using namespace std;

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	instance = new Sudoku();
	mode = 0; // easy
	Time = new wxStaticText(this, wxID_ANY, "Timer");
	start = std::clock();
	timer = new bool;

	wxFont font;
	font.SetPointSize(10);
	font.SetWeight(wxFONTWEIGHT_BOLD);
	font.Scale(1.5);


	wxBoxSizer* MainSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* LeftSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* RightSizer = new wxBoxSizer(wxVERTICAL);

	MainSizer->Add(LeftSizer, 2, wxEXPAND, 10);
	MainSizer->Add(RightSizer, 1, wxEXPAND, 10);

	wxGridSizer* rightSideGrid = new wxGridSizer(5, 1, 5, 5);

	RightSizer->Add(rightSideGrid, 0, wxALIGN_CENTER);

	wxGridSizer* timerGrind = new wxGridSizer(1, 2, 5, 5);
	wxStaticText* label_timer = new wxStaticText(this, wxID_ANY, "Timer");
	label_timer->SetLabel("Time: ");
	label_timer->SetFont(font);

	timerGrind->Add(label_timer, 1, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
	timerGrind->Add(Time, 1, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

	rightSideGrid->Add(timerGrind, 1, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT | wxTOP | wxALIGN_BOTTOM, 5);

	wxGridSizer* EmptyCellGrind = new wxGridSizer(1, 2, 5, 5);

	wxStaticText* label_Quantity = new wxStaticText(this, wxID_ANY, "Quantity of empty Cells: ");
	label_Quantity->SetFont(font);
	Quantity = new wxStaticText(this, wxID_ANY, "X");
	Quantity->SetFont(font);

	EmptyCellGrind->Add(label_Quantity, 1, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
	EmptyCellGrind->Add(Quantity, 1, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

	rightSideGrid->Add(EmptyCellGrind, 1, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);

	wxButton** input_buttons = new wxButton * [10];

	wxGridSizer* input = new wxGridSizer(4, 3, 5, 5);

	for (int i = 0; i < 9; i++) {
		input_buttons[i] = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(100, 100), 0);
		input_buttons[i]->SetFont(font);
		input_buttons[i]->SetLabel(to_string(i+1));
		input_buttons[i]->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::input), NULL, this);
		input->Add(input_buttons[i], 1, wxALL | wxEXPAND | wxRIGHT | wxLEFT, 5);
	}
	input_buttons[9] = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(100, 100), 0);
	input_buttons[9]->SetFont(font);
	input_buttons[9]->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::deleteCell), NULL, this);
	input->Add(new wxStaticText(), 1, wxALL | wxEXPAND, 5);
	input->Add(input_buttons[9], 1, wxALL | wxEXPAND, 5);


	rightSideGrid->Add(input, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);

	wxGridSizer* rightside_button = new wxGridSizer(1, 2, 5, 5);
	wxButton* regenerate = new wxButton(this, wxID_ANY, "Generate new", wxDefaultPosition, wxSize(100, 100), 0);
	regenerate->SetFont(font);
	regenerate->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::generate), NULL, this);
	wxButton* solve = new wxButton(this, wxID_ANY, "Solve", wxDefaultPosition, wxSize(200, 30), 0);
	solve->SetFont(font);
	solve->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::solve), NULL, this);

	rightside_button->Add(regenerate, 1, wxEXPAND | wxLEFT | wxTOP, 50);
	rightside_button->Add(solve, 1, wxEXPAND | wxRIGHT | wxTOP, 50);

	rightSideGrid->Add(rightside_button, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);

	Time->SetFont(font);

	this->SetSizerAndFit(MainSizer);
	this->SetInitialSize(wxSize(1000, 600));

	Difficulty_buttons = new wxButton * [3];
	Sudoku_buttons = new wxButton * [81];

	wxGridSizer* grid_Difficulty = new wxGridSizer(1, 4, 5, 5);
	wxGridSizer* sudoku = new wxGridSizer(3, 3, 0, 0);

	LeftSizer->Add(grid_Difficulty, 0, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 50);
	LeftSizer->Add(sudoku, 1, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 50);


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
		Sudoku_buttons[i] = new wxButton(this, wxID_ANY, "", wxDefaultPosition, wxSize(20, 20), 0);
		Sudoku_buttons[i]->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::selectField), NULL, this);
		Sudoku_buttons[i]->SetFont(font);
	}


	wxGridSizer* tmp = new wxGridSizer(3, 3, 0, 0);
	tmp->Add(Sudoku_buttons[0], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[1], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[2], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[9], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[10], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[11], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[18], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[19], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[20], 0, wxALL | wxEXPAND, 0);
	sudoku->Add(tmp, 1, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
	tmp = new wxGridSizer(3, 3, 0, 0);
	tmp->Add(Sudoku_buttons[3], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[4], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[5], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[12], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[13], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[14], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[21], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[22], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[23], 0, wxALL | wxEXPAND, 0);
	sudoku->Add(tmp, 1, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
	tmp = new wxGridSizer(3, 3, 0, 0);
	tmp->Add(Sudoku_buttons[6], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[7], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[8], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[15], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[16], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[17], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[24], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[25], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[26], 0, wxALL | wxEXPAND, 0);
	sudoku->Add(tmp, 1, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
	tmp = new wxGridSizer(3, 3, 0, 0);
	tmp->Add(Sudoku_buttons[27], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[28], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[29], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[36], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[37], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[38], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[45], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[46], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[47], 0, wxALL | wxEXPAND, 0);
	sudoku->Add(tmp, 1, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
	tmp = new wxGridSizer(3, 3, 0, 0);
	tmp->Add(Sudoku_buttons[30], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[31], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[32], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[39], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[40], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[41], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[48], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[49], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[50], 0, wxALL | wxEXPAND, 0);
	sudoku->Add(tmp, 1, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
	tmp = new wxGridSizer(3, 3, 0, 0);
	tmp->Add(Sudoku_buttons[33], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[34], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[35], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[42], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[43], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[44], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[51], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[52], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[53], 0, wxALL | wxEXPAND, 0);
	sudoku->Add(tmp, 1, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
	tmp = new wxGridSizer(3, 3, 0, 0);
	tmp->Add(Sudoku_buttons[54], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[55], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[56], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[63], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[64], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[65], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[72], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[73], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[74], 0, wxALL | wxEXPAND, 0);
	sudoku->Add(tmp, 1, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
	tmp = new wxGridSizer(3, 3, 0, 0);
	tmp->Add(Sudoku_buttons[57], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[58], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[59], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[66], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[67], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[68], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[75], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[76], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[77], 0, wxALL | wxEXPAND, 0);
	sudoku->Add(tmp, 1, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
	tmp = new wxGridSizer(3, 3, 0, 0);
	tmp->Add(Sudoku_buttons[60], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[61], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[62], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[69], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[70], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[71], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[78], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[79], 0, wxALL | wxEXPAND, 0);
	tmp->Add(Sudoku_buttons[80], 0, wxALL | wxEXPAND, 0);
	sudoku->Add(tmp, 1, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);

	this->SetSizer(MainSizer);



	thread* next = new thread(&MainFrame::bufferNextGrid, this);

	loadSudokuField();
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

	selected = Sudoku_buttons[0];
	loadSudokuField();
}

void MainFrame::updateValue(int row, int col, int val) {
	Sudoku_buttons[row * 9 + col]->SetLabel(to_string(val));
}

void MainFrame::input(wxCommandEvent& event) {

	string pressed = wxDynamicCast(event.GetEventObject(), wxButton)->GetLabel().ToStdString();

	if (selected) {
		if (selected->GetLabel().ToStdString().empty()) {
			Quantity->SetLabel(to_string(stoi(string(Quantity->GetLabel())) - 1));
		}
		selected->SetLabel(pressed);
	}

}

void MainFrame::selectField(wxCommandEvent& event) {
	wxButton* ptr = wxDynamicCast(event.GetEventObject(), wxButton);
	if (ptr->GetForegroundColour() == *wxRED) {
		selected = ptr;
	}
	else {
		selected = nullptr;
	}

}

void MainFrame::deleteCell(wxCommandEvent& event) {
	if (selected->GetForegroundColour() == *wxRED) {
		selected->SetLabel("");
		Quantity->SetLabel(to_string(stoi(string(Quantity->GetLabel())) + 1));
	}

}

void MainFrame::loadSudokuField() {
	*timer = true;
	thread* timer_thread = new thread(&MainFrame::update_Timer, this);
	instance->setSudoku(mode);
	start = std::clock();

	for (int i = 0; i < 81; i++) {
		int r = (i / 9);
		int c = (i % 9);
		if (instance->getValue(r, c) == 0) {
			Sudoku_buttons[i]->SetForegroundColour(*wxRED);
			Sudoku_buttons[i]->SetLabel("");
		}
		else {
			Sudoku_buttons[i]->SetLabel(std::to_string(instance->getValue(r, c)));
			Sudoku_buttons[i]->SetForegroundColour(*wxBLACK);
		}
	}
	Quantity->SetLabel(to_string(instance->sumBlankCells()));
}

void MainFrame::update_Timer() {

	while (*timer) {
		std::clock_t now = std::clock();
		Time->SetLabel(to_string(int((now - start) / ((double)CLOCKS_PER_SEC * 60)))+":"+to_string(int((now - start) / ((double)CLOCKS_PER_SEC)) % 60));
		this_thread::sleep_for(100ms);
	}
}

void MainFrame::generate(wxCommandEvent& event) {
	loadSudokuField();
}

void MainFrame::solve(wxCommandEvent& event) {
	instance->solveSudoku(0,0);
	*timer = false;
	print();
}

void MainFrame::print() {
	for (int i = 0; i < 81; i++) {
		int r = (i / 9);
		int c = (i % 9);
		Sudoku_buttons[i]->SetLabel(std::to_string(instance->getValue(r, c)));
		Sudoku_buttons[i]->SetForegroundColour(*wxBLACK);
	}
}

void MainFrame::bufferNextGrid() {
	Sudoku tmp;

	while (true) {
		tmp.changeDifficulty(40, 44);
		while (instance->easyGrid->size() < 4) {
			tmp.generateSudoku();
			instance->easyGrid->push_back(tmp);
			this_thread::sleep_for(1s);
		}
		tmp.changeDifficulty(45, 50);
		while (instance->mediumGrid->size() < 4) {
			tmp.generateSudoku();
			instance->mediumGrid->push_back(tmp);
			this_thread::sleep_for(1s);
		}
		tmp.changeDifficulty(50, 54);
		while (instance->hardGrid->size() < 4) {
			tmp.generateSudoku();
			instance->hardGrid->push_back(tmp);
			this_thread::sleep_for(1s);
		}
		this_thread::sleep_for(500ms);
	}
}



