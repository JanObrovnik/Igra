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


	wxPanel* panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS);

	int velikost = 64;
	int razdalja = 2 + velikost;
	wxButton* test = new wxButton(panel, wxID_ANY, "Test", wxPoint(100, 0), wxDefaultSize);
	wxButton* up = new wxButton(panel, wxID_ANY, "Up", wxPoint(100, 200), wxSize(velikost, velikost));
	wxButton* right = new wxButton(panel, wxID_ANY, "Right", wxPoint(100 + razdalja, 200 + razdalja / 2), wxSize(velikost, velikost));
	wxButton* down = new wxButton(panel, wxID_ANY, "Down", wxPoint(100, 200 + razdalja), wxSize(velikost, velikost));
	wxButton* left = new wxButton(panel, wxID_ANY, "Left", wxPoint(100 - razdalja, 200 + razdalja / 2), wxSize(velikost, velikost));

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
}

void MainFrame::OnRightClicked(wxCommandEvent& evt) {

	seznami->player.moveEast();
	Movement(seznami);

	sliderX->SetValue(seznami->player.getLocation().x);
	sliderY->SetValue(seznami->player.getLocation().y);
	healthBar->SetValue(seznami->player.getHp());
}

void MainFrame::OnDownClicked(wxCommandEvent& evt) {

	seznami->player.moveSouth();
	Movement(seznami);

	sliderX->SetValue(seznami->player.getLocation().x);
	sliderY->SetValue(seznami->player.getLocation().y);
	healthBar->SetValue(seznami->player.getHp());
}

void MainFrame::OnLeftClicked(wxCommandEvent& evt) {

	seznami->player.moveWest();
	Movement(seznami);

	sliderX->SetValue(seznami->player.getLocation().x);
	sliderY->SetValue(seznami->player.getLocation().y);
	healthBar->SetValue(seznami->player.getHp());
}
