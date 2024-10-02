#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {

	MainFrame* mainFrame = new MainFrame("Ucenje"); // ustvarimo frame z imenom

	mainFrame->SetClientSize(480, 320); // velikost aplikacije
	mainFrame->Center(); // centriramo na sredi ekrana

	mainFrame->Show(true); // prikažemo frame

	return true;
}
