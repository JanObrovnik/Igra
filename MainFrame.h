#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);

	//void OnPaint(wxPaintEvent& evt); // Za risanje na frame
private:
	void OnTestClicked(wxCommandEvent& evt);
	void OnUpClicked(wxCommandEvent& evt);
	void OnRightClicked(wxCommandEvent& evt);
	void OnDownClicked(wxCommandEvent& evt);
	void OnLeftClicked(wxCommandEvent& evt);
};