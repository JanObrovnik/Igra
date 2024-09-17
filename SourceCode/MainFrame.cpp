#include "MainFrame.h"
#include "Simulation.cpp"
#include <wx/wx.h>



Seznami* seznami = new Seznami;

wxSlider* slider;
wxSlider* sliderX;
wxSlider* sliderY;
wxGauge* healthBar;


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

	seznami->player = Hero(80, koordinate(0, 0));
	seznami->seznamZidov.push_back(Wall(koordinate(3, 0)));
	seznami->seznamZidov.push_back(Wall(koordinate(3, 1)));
	seznami->seznamVrat.push_back(Door(koordinate(0, 4)));
	seznami->seznamPortalov.push_back(Portal(koordinate(4, 0), koordinate(6, 8)));
	seznami->seznamPasti.push_back(Trap(20, koordinate(0, 2)));
	seznami->seznamPasti.push_back(Trap(20, koordinate(1, 2)));
	seznami->seznamPasti.push_back(Trap(20, koordinate(2, 2)));
	seznami->seznamPasti.push_back(Trap(20, koordinate(3, 2)));
	seznami->seznamPasti.push_back(Trap(20, koordinate(6, 9)));
	seznami->seznamZdravil.push_back(Bandage(5, koordinate(3, 3)));
	seznami->seznamKovancev.push_back(Coin(1, koordinate(1, 0)));
	seznami->seznamKovancev.push_back(Coin(5, koordinate(2, 0)));
	seznami->seznamKljucev.push_back(Key(koordinate(0, 1)));
	seznami->makeBackup();
	Movement(seznami);


	wxPanel* panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS);


	int velikost = 64;
	int razdalja = 2 + velikost;
	wxButton* test = new wxButton(panel, wxID_ANY, "Test", wxPoint(100, 0), wxDefaultSize);
	wxButton* up = new wxButton(panel, wxID_ANY, "Up", wxPoint(100, 200), wxSize(velikost, velikost));
	wxButton* right = new wxButton(panel, wxID_ANY, "Right", wxPoint(100 + razdalja, 200 + razdalja / 2), wxSize(velikost, velikost));
	wxButton* down = new wxButton(panel, wxID_ANY, "Down", wxPoint(100, 200 + razdalja), wxSize(velikost, velikost));
	wxButton* left = new wxButton(panel, wxID_ANY, "Left", wxPoint(100 - razdalja, 200 + razdalja / 2), wxSize(velikost, velikost));
	wxButton* reset = new wxButton(panel, wxID_ANY, "Reset", wxPoint(100 + 2 * razdalja + 6, 200), wxSize(velikost * 2 / 3, velikost * 2 / 3));

	slider = new wxSlider(panel, wxID_ANY, 0, 0, 100, wxPoint(100, 100), wxDefaultSize, wxSL_LABELS);
	sliderX = new wxSlider(panel, wxID_ANY, seznami->player.getLocation().x, 0, 10, wxPoint(85, 350), wxDefaultSize, wxSL_LABELS);
	sliderY = new wxSlider(panel, wxID_ANY, seznami->player.getLocation().y, 0, 10, wxPoint(85, 400), wxDefaultSize, wxSL_LABELS);

	healthBar = new wxGauge(panel, wxID_ANY, seznami->player.getMaxHp(), wxPoint(10, 200), wxSize(-1, velikost + razdalja), wxGA_VERTICAL);
	healthBar->SetValue(seznami->player.getHp());


	test->Bind(wxEVT_BUTTON, &MainFrame::OnTestClicked, this);
	up->Bind(wxEVT_BUTTON, &MainFrame::OnUpClicked, this);
	right->Bind(wxEVT_BUTTON, &MainFrame::OnRightClicked, this);
	down->Bind(wxEVT_BUTTON, &MainFrame::OnDownClicked, this);
	left->Bind(wxEVT_BUTTON, &MainFrame::OnLeftClicked, this);
	reset->Bind(wxEVT_BUTTON, &MainFrame::OnResetClicked, this);

	panel->Connect(wxEVT_PAINT, wxPaintEventHandler(MainFrame::OnPaint));

	panel->SetDoubleBuffered(true);
}


void MainFrame::OnTestClicked(wxCommandEvent& evt) {

	slider->SetValue(seznami->player.getHp());
}

void MainFrame::OnUpClicked(wxCommandEvent& evt) {

	seznami->player.moveNorth();
	Movement(seznami);

	sliderX->SetValue(seznami->player.getLocation().x);
	sliderY->SetValue(seznami->player.getLocation().y);
	healthBar->SetValue(seznami->player.getHp());

	Refresh();
}

void MainFrame::OnRightClicked(wxCommandEvent& evt) {

	seznami->player.moveEast();
	Movement(seznami);

	sliderX->SetValue(seznami->player.getLocation().x);
	sliderY->SetValue(seznami->player.getLocation().y);
	healthBar->SetValue(seznami->player.getHp());

	Refresh();
}

void MainFrame::OnDownClicked(wxCommandEvent& evt) {

	seznami->player.moveSouth();
	Movement(seznami);

	sliderX->SetValue(seznami->player.getLocation().x);
	sliderY->SetValue(seznami->player.getLocation().y);
	healthBar->SetValue(seznami->player.getHp());

	Refresh();
}

void MainFrame::OnLeftClicked(wxCommandEvent& evt) {

	seznami->player.moveWest();
	Movement(seznami);

	sliderX->SetValue(seznami->player.getLocation().x);
	sliderY->SetValue(seznami->player.getLocation().y);
	healthBar->SetValue(seznami->player.getHp());

	Refresh();
}

void MainFrame::OnResetClicked(wxCommandEvent& evt) {

	seznami->restore();
	Movement(seznami);

	sliderX->SetValue(seznami->player.getLocation().x);
	sliderY->SetValue(seznami->player.getLocation().y);
	healthBar->SetValue(seznami->player.getHp());

	Refresh();
}


void MainFrame::OnPaint(wxPaintEvent& evt) {

	wxPaintDC dc(this);
	wxSize size = this->GetSize();
	wxPoint mousePos = this->ScreenToClient(wxGetMousePosition());


	//- Velikost ozadja
	const int tileNumber = 10;
	const int tileSize = 64;
	int area = tileNumber * tileSize;


	//- Izris ozadja
	dc.DrawRectangle(wxPoint(300, 0), wxSize(area, area));
	for (int i = 1; i < tileNumber; i++) {

		dc.DrawLine(wxPoint(300 + i * tileSize, 0), wxPoint(300 + i * tileSize, area));
		dc.DrawLine(wxPoint(300, i * tileSize), wxPoint(300 + area, i * tileSize));
	}


	//- Izris objektov
	for (int i = 0; i < seznami->seznamZidov.size(); i++) { // Wall
		if (seznami->seznamZidov[i].getExist()) dc.SetBrush(wxBrush(wxColour(150, 75, 0), wxBRUSHSTYLE_SOLID));
		else dc.SetBrush(wxBrush(wxColour(211, 181, 130), wxBRUSHSTYLE_SOLID));
		wxPoint wallPoint(seznami->seznamZidov[i].getLocation().x, seznami->seznamZidov[i].getLocation().y);
		dc.DrawRectangle(wxPoint(300, 0) + wallPoint * tileSize + wxPoint(tileSize, tileSize) / 4, wxSize(tileSize, tileSize) / 2);
	}

	for (int i = 0; i < seznami->seznamVrat.size(); i++) { // Door
		if (seznami->seznamVrat[i].getLocked()) dc.SetBrush(wxBrush(wxColour(0, 0, 0), wxBRUSHSTYLE_LAST_HATCH));
		else dc.SetBrush(wxBrush(wxColour(255, 255, 255), wxBRUSHSTYLE_SOLID));
		wxPoint wallPoint(seznami->seznamVrat[i].getLocation().x, seznami->seznamVrat[i].getLocation().y);
		dc.DrawRectangle(wxPoint(300, 0) + wallPoint * tileSize + wxPoint(tileSize, tileSize) / 4, wxSize(tileSize, tileSize) / 2);
	}

	dc.SetBrush(wxBrush(wxColour(255, 0, 153), wxBRUSHSTYLE_SOLID)); // Portal
	for (int i = 0; i < seznami->seznamPortalov.size(); i++) {
		if (seznami->seznamPortalov[i].getExist()) {
			wxPoint portalPoint0(seznami->seznamPortalov[i].getLocation0().x, seznami->seznamPortalov[i].getLocation0().y);
			dc.DrawRectangle(wxPoint(300, 0) + portalPoint0 * tileSize + wxPoint(tileSize, tileSize) / 4, wxSize(tileSize, tileSize) / 2);
			wxPoint portalPoint1(seznami->seznamPortalov[i].getLocation1().x, seznami->seznamPortalov[i].getLocation1().y);
			dc.DrawRectangle(wxPoint(300, 0) + portalPoint1 * tileSize + wxPoint(tileSize, tileSize) / 4, wxSize(tileSize, tileSize) / 2);
		}
	}

	dc.SetBrush(wxBrush(wxColour(153, 0, 0), wxBRUSHSTYLE_SOLID)); // Trap
	for (int i = 0; i < seznami->seznamPasti.size(); i++) {
		wxPoint wallPoint(seznami->seznamPasti[i].getLocation().x, seznami->seznamPasti[i].getLocation().y);
		dc.DrawRectangle(wxPoint(300, 0) + wallPoint * tileSize + wxPoint(tileSize, tileSize) / 4, wxSize(tileSize, tileSize) / 2);
	}

	dc.SetBrush(wxBrush(wxColour(0, 153, 0), wxBRUSHSTYLE_SOLID)); // Bandage
	for (int i = 0; i < seznami->seznamZdravil.size(); i++) {
		wxPoint wallPoint(seznami->seznamZdravil[i].getLocation().x, seznami->seznamZdravil[i].getLocation().y);
		dc.DrawRectangle(wxPoint(300, 0) + wallPoint * tileSize + wxPoint(tileSize, tileSize) / 4, wxSize(tileSize, tileSize) / 2);
	}

	dc.SetBrush(wxBrush(wxColour(153, 153, 0), wxBRUSHSTYLE_SOLID)); // Coin
	for (int i = 0; i < seznami->seznamKovancev.size(); i++) {
		wxPoint wallPoint(seznami->seznamKovancev[i].getLocation().x, seznami->seznamKovancev[i].getLocation().y);
		dc.DrawRectangle(wxPoint(300, 0) + wallPoint * tileSize + wxPoint(tileSize, tileSize) / 4, wxSize(tileSize, tileSize) / 2);
	}

	dc.SetBrush(wxBrush(wxColour(153, 153, 153), wxBRUSHSTYLE_SOLID)); // Key
	for (int i = 0; i < seznami->seznamKljucev.size(); i++) {
		wxPoint wallPoint(seznami->seznamKljucev[i].getLocation().x, seznami->seznamKljucev[i].getLocation().y);
		dc.DrawRectangle(wxPoint(300, 0) + wallPoint * tileSize + wxPoint(tileSize, tileSize) / 4, wxSize(tileSize, tileSize) / 2);
	}

	dc.SetBrush(wxBrush(wxColour(153, 0, 102), wxBRUSHSTYLE_SOLID)); // Hero
	wxPoint playerPoint(seznami->player.getLocation().x, seznami->player.getLocation().y);
	dc.DrawRectangle(wxPoint(300, 0) + playerPoint * tileSize + wxPoint(tileSize, tileSize) / 4, wxSize(tileSize, tileSize) / 2);


	//- Izpis vrednosti
	//////////////////////
}
