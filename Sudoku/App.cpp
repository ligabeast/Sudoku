#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	MainFrame* main = new MainFrame("Sudoku by Baran");
	main->SetSizeHints(800, 800);

	main->Show();
	return true;
}
