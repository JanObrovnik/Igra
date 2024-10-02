#include "DrawingCanvas.h"
#include <wx/graphics.h>
#include <wx/dcbuffer.h>


wxDEFINE_EVENT(CANVAS_RECT_ADDED, wxCommandEvent);
wxDEFINE_EVENT(CANVAS_RECT_REMOVED, wxCommandEvent);

DrawingCanvas::DrawingCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size) : wxWindow(parent, id ,pos, size) {

	this->SetBackgroundStyle(wxBG_STYLE_PAINT);

	this->Bind(wxEVT_PAINT, &DrawingCanvas::OnPaint, this);
	this->Bind(wxEVT_LEFT_DOWN, &DrawingCanvas::OnMouseDown, this);
	this->Bind(wxEVT_MOTION, &DrawingCanvas::OnMouseMove, this);
	this->Bind(wxEVT_LEFT_UP, &DrawingCanvas::OnMouseUp, this);
	this->Bind(wxEVT_LEAVE_WINDOW, &DrawingCanvas::OnMouseLeave, this);

	addRect(100, 80, 210, 140, 0, *wxRED, "#1");
	addRect(130, 110, 280, 210, M_PI / 3., *wxBLUE, "#2");
	addRect(110, 110, 300, 120, -M_PI / 4., wxColour(255, 0, 255, 127), "#3");

	this->draggedObj = nullptr;
	this->shouldRotate = false;
}

void DrawingCanvas::addRect(int width, int hight, int centerX, int centerY, double angle, wxColour colour, const std::string& text) { // raje pos pred size

	GraphicObject obj{
		{-width / 2.,
		-hight / 2.,
		static_cast<double>(width),
		static_cast<double>(hight)},
		colour,
		text,
		{}};

	obj.transform.Translate(static_cast<double>(centerX), 
							static_cast<double>(centerY));
	obj.transform.Rotate(angle);

	this->objectList.push_back(obj);

	sendRectAddedEvent(text);
	Refresh();
}

void DrawingCanvas::removeTopRect() {

	if (!this->objectList.empty() && draggedObj == nullptr) {

		auto text = this->objectList.back().text;
		this->objectList.pop_back();

		sendRectAddedEvent(text);
		Refresh();
	}
}


void DrawingCanvas::OnPaint(wxPaintEvent& evt) {

	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

	// rocno risanje
	/*if (gc) {

		wxSize rectSize = this->FromDIP(wxSize(100, 80)); // 'this->FromDIP()' da se ne scale-a
		wxPoint rectOrigin = wxPoint(-rectSize.x / 2, -rectSize.y / 2);

		wxAffineMatrix2D transform;
		transform.Translate(100, 130);
		transform.Rotate(M_PI / 3.); // rotiramo okoli (0,0)
		transform.Scale(3, 3); // scale-a trenutno rotacijo v x in y
		gc->SetTransform(gc->CreateMatrix(transform)); // gre v obratnem vrsten redu

		gc->SetBrush(*wxRED_BRUSH);
		gc->DrawRectangle(rectOrigin.x, rectOrigin.y, rectSize.x, rectSize.y);

		gc->SetFont(*wxNORMAL_FONT, *wxWHITE);
		wxString text = "test";

		double textWidth, textHight;
		gc->GetTextExtent(text, &textWidth, &textHight);

		gc->DrawText("Text", rectOrigin.x + rectSize.x / 2 - textWidth / 2, rectOrigin.y + rectSize.y / 2 - textHight / 2);

		delete gc;
	}*/


	// risanje iz seznama
	if (gc) {
		for (const auto& object : objectList) {

			gc->SetTransform(gc->CreateMatrix(object.transform)); // gre v obratnem vrsten redu

			gc->SetBrush(wxBrush(object.colour));
			gc->DrawRectangle(object.rect.m_x, object.rect.m_y, object.rect.m_width, object.rect.m_height);

			gc->SetFont(*wxNORMAL_FONT, *wxWHITE);

			double textWidth, textHight;
			gc->GetTextExtent(object.text, &textWidth, &textHight);

			gc->DrawText(object.text, object.rect.m_x + object.rect.m_width / 2 - textWidth / 2, object.rect.m_y + object.rect.m_height / 2 - textHight / 2);
		}

		delete gc;
	}
}

void DrawingCanvas::OnMouseDown(wxMouseEvent& evt) {

	auto clickedObjectIter = std::find_if(objectList.rbegin(), objectList.rend(),
		[evt](const GraphicObject& o) {
			wxPoint2DDouble clickPos = evt.GetPosition();
			auto inv = o.transform;
			inv.Invert();
			clickPos = inv.TransformPoint(clickPos);
			return o.rect.Contains(clickPos);
		});

	if (clickedObjectIter != objectList.rend()) {

		auto forwardIt = std::prev(clickedObjectIter.base());

		objectList.push_back(*forwardIt);
		objectList.erase(forwardIt);

		draggedObj = &(*std::prev(objectList.end()));

		lastDragOrigin = evt.GetPosition();
		shouldRotate = wxGetKeyState(WXK_ALT); // Preverimo tipkovnico

		Refresh();
	}
}

void DrawingCanvas::OnMouseMove(wxMouseEvent& evt) {

	if (draggedObj != nullptr) {

		if (shouldRotate) {

			double absoluteYDiff = evt.GetPosition().y - lastDragOrigin.m_y;
			draggedObj->transform.Rotate(absoluteYDiff / 100. * M_PI);
		}
		else {

			auto dragVector = evt.GetPosition() - lastDragOrigin;

			auto inv = draggedObj->transform;
			inv.Invert();
			dragVector = inv.TransformDistance(dragVector);

			draggedObj->transform.Translate(dragVector.m_x, dragVector.m_y);
		}

		lastDragOrigin = evt.GetPosition();
		Refresh();
	}
}

void DrawingCanvas::OnMouseUp(wxMouseEvent& evt) {

	finishDrag();
	finishRotation();
}

void DrawingCanvas::OnMouseLeave(wxMouseEvent& evt) {

	finishDrag();
	finishRotation();
}

void DrawingCanvas::finishDrag() {

	draggedObj = nullptr;
}

void DrawingCanvas::finishRotation() {

	shouldRotate = false;
}

void DrawingCanvas::sendRectAddedEvent(const wxString& rectTitle) {

	wxCommandEvent event(CANVAS_RECT_ADDED, GetId());
	event.SetEventObject(this);
	event.SetString(rectTitle);

	ProcessWindowEvent(event);
}

void DrawingCanvas::sendRectRemovedEvent(const wxString& rectTitle) {

	wxCommandEvent event(CANVAS_RECT_REMOVED, GetId());
	event.SetEventObject(this);
	event.SetString(rectTitle);

	ProcessWindowEvent(event);
}
