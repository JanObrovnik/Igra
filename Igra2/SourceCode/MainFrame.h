#pragma once
#include <wx/wx.h>
#include <random>
#include "DrawingCanvas.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);

private:
	void OnAddButtonClicked(wxCommandEvent& evt);
	void OnRemovedButtonClicked(wxCommandEvent& evt);

	void OnRectAdded(wxCommandEvent& evt);
	void OnRectRemoved(wxCommandEvent& evt);

	wxPanel* createButtonPanel(wxWindow* parent);

	DrawingCanvas* canvas;

	int rectCount = 0;
	std::mt19937 randomGen;
};