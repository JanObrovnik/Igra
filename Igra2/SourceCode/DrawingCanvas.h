#pragma once
#include <wx/wx.h>
#include <list>
#include "GraphicObject.h"


wxDECLARE_EVENT(CANVAS_RECT_ADDED, wxCommandEvent);
wxDECLARE_EVENT(CANVAS_RECT_REMOVED, wxCommandEvent);

class DrawingCanvas : public wxWindow {

public:
	DrawingCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);
	virtual ~DrawingCanvas() {}

	void addEnemy(int health, ProjectileType type, wxPoint position, double size);
	void removeTopRect();

	int getObjectCout() { return objectList.size(); }

	void simulirajChange();

private:
	void OnPaint(wxPaintEvent& evt);
	void OnMouseDown(wxMouseEvent& evt);
	void OnMouseMove(wxMouseEvent& evt);
	void OnMouseUp(wxMouseEvent& evt);
	void OnMouseLeave(wxMouseEvent& evt);

	void finishDrag();
	void finishRotation();

	void sendRectAddedEvent(const wxString& rectTitle);
	void sendRectRemovedEvent(const wxString& rectTitle);

	std::list<GraphicObject> objectList;

	GraphicObject* draggedObj;
	bool shouldRotate;

	wxPoint2DDouble lastDragOrigin;


	Pratoria hero = Pratoria(24, NORMAL, wxPoint(200, 650), 20);
	std::list<Enemy> enemyList;
	std::list<Projectile> projectileList;

	bool simuliraj = false;
};

