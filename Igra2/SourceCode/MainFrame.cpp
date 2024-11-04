#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	auto buttonPanel = createButtonPanel(this);

	canvas = new DrawingCanvas(this, wxID_ANY, wxDefaultPosition, this->FromDIP(wxSize(800, 800)));
	canvas->Bind(CANVAS_RECT_ADDED, &MainFrame::OnRectAdded, this);
	canvas->Bind(CANVAS_RECT_REMOVED, &MainFrame::OnRectRemoved, this);

	rectCount = canvas->getObjectCout();

	sizer->Add(canvas, 1, wxEXPAND | wxALL, 0);
	sizer->Add(buttonPanel, 0, wxEXPAND | wxALL, 0);

	this->SetSizerAndFit(sizer);

	CreateStatusBar(1);
	SetStatusText("Ready", 0);
}

void MainFrame::OnAddButtonClicked(wxCommandEvent& evt) {

	std::uniform_int_distribution<int> sizeDistrib(10, 20);
	double polmer = sizeDistrib(randomGen);

	std::uniform_int_distribution<int> xDistrib(polmer, canvas->GetSize().GetWidth() - polmer); /////////// dat izven vidnega kota
	std::uniform_int_distribution<int> yDistrib(polmer, 200 + polmer);

	//std::uniform_real_distribution<double> angleDistrib(0., 2 * M_PI);

	//std::uniform_int_distribution<int> colourDistrib(0, 0xFFFFFF);

	//rectCount++;
	//canvas->addEnemy(sizeDistrib(randomGen), sizeDistrib(randomGen), xDistrib(randomGen), yDistrib(randomGen),
	//				angleDistrib(randomGen), wxColour(colourDistrib(randomGen)), "rect #" + std::to_string(rectCount));

	canvas->addEnemy(10, NORMAL, wxPoint(xDistrib(randomGen), yDistrib(randomGen)), polmer);
}

void MainFrame::OnRemovedButtonClicked(wxCommandEvent& evt) {

	canvas->removeTopRect();
}

void MainFrame::OnSimButtonClicked(wxCommandEvent& evt) {

	canvas->simulirajChange();
}


void MainFrame::OnRectAdded(wxCommandEvent& evt) {

	SetStatusText("Rect named " + evt.GetString() + "added.");
}

void MainFrame::OnRectRemoved(wxCommandEvent& evt) {

	SetStatusText("Rect named " + evt.GetString() + "removed.");
}

wxPanel* MainFrame::createButtonPanel(wxWindow* parent) {

	wxPanel* panel = new wxPanel(parent);
	wxButton* addRectButton = new wxButton(panel, wxID_ANY, "Add Rect");
	wxButton* removeRectButton = new wxButton(panel, wxID_ANY, "Remove Rect");
	wxButton* simButton = new wxButton(panel, wxID_ANY, "Sumilate");

	wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(addRectButton, 0, wxEXPAND | wxALL);
	sizer->Add(removeRectButton, 0, wxEXPAND | wxALL);
	sizer->Add(simButton, 0, wxEXPAND | wxALL);

	panel->SetSizer(sizer);

	addRectButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddButtonClicked, this);
	removeRectButton->Bind(wxEVT_BUTTON, &MainFrame::OnRemovedButtonClicked, this);
	simButton->Bind(wxEVT_BUTTON, &MainFrame::OnSimButtonClicked, this);

	return panel;
}
