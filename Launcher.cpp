// file to launch program
// not many thing changes, except Title
// Edit MainFrame.h instead
#include "MainFrame.h"

/*
class Launcher : public wxApp {...};
*/

// where program begins
bool Launcher::OnInit()
{
	MainFrame* window = new MainFrame("Title");
	window->SetClientSize(1024, 600);
	window->Center();
	window->Show();

	return true;
}

// WinMain(...) is here
wxIMPLEMENT_APP(Launcher);