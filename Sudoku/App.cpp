#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	MainFrame* main = new MainFrame("Sudoku by Baran");
	main->SetWindowStyle(main->GetWindowStyle() | wxSTAY_ON_TOP);
	main->SetMinSize(wxSize(1800, 1000));

	main->Show();
	return true;
}
