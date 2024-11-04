#include "DrawingCanvas.h"
#include <wx/graphics.h>
#include <wx/dcbuffer.h>


wxDEFINE_EVENT(CANVAS_RECT_ADDED, wxCommandEvent);
wxDEFINE_EVENT(CANVAS_RECT_REMOVED, wxCommandEvent);

DrawingCanvas::DrawingCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size) : wxWindow(parent, id ,pos, size) {

	this->SetBackgroundStyle(wxBG_STYLE_PAINT);
	this->SetBackgroundColour(wxColour(30, 30, 30));

	this->Bind(wxEVT_PAINT, &DrawingCanvas::OnPaint, this);
	this->Bind(wxEVT_LEFT_DOWN, &DrawingCanvas::OnMouseDown, this);
	this->Bind(wxEVT_MOTION, &DrawingCanvas::OnMouseMove, this);
	this->Bind(wxEVT_LEFT_UP, &DrawingCanvas::OnMouseUp, this);
	this->Bind(wxEVT_LEAVE_WINDOW, &DrawingCanvas::OnMouseLeave, this);

	//addEnemy(100, 80, 210, 140, 0, *wxRED, "#1");
	//addEnemy(130, 110, 280, 210, M_PI / 3., *wxBLUE, "#2");
	//addEnemy(110, 110, 300, 120, -M_PI / 4., wxColour(255, 0, 255, 127), "#3");

	enemyList.push_back(Enemy(3, NORMAL, wxPoint(50, 250), 12));
	enemyList.push_back(Enemy(3, NORMAL, wxPoint(100, 250), 8));
	enemyList.push_back(Enemy(3, NORMAL, wxPoint(200, 200), 16));


	this->draggedObj = nullptr;
	this->shouldRotate = false;
}

void DrawingCanvas::addEnemy(int health, ProjectileType type, wxPoint position, double size) {

	//GraphicObject obj{
	//	{-width / 2.,
	//	-hight / 2.,
	//	static_cast<double>(width),
	//	static_cast<double>(hight)},
	//	colour,
	//	text,
	//	{}};
	//
	//obj.transform.Translate(static_cast<double>(centerX), 
	//						static_cast<double>(centerY));
	//obj.transform.Rotate(angle);
	//
	//this->objectList.push_back(obj);


	Enemy enemy{
		health,
		NORMAL,
		position,
		size
	};
	
	enemyList.push_back(enemy);


	//sendRectAddedEvent("New enemy");
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

void DrawingCanvas::simulirajChange() {

	if (simuliraj) simuliraj = false;
	else simuliraj = true;

	while (simuliraj) {

		wxYield();
		Refresh();
	}
}


void DrawingCanvas::OnPaint(wxPaintEvent& evt) {

	std::for_each(projectileList.begin(), projectileList.end(), [](Projectile& projectile) {projectile.move(1); });
	projectileList.remove_if([](Projectile projectile) {return projectile.outOfBounds(); });

	std::for_each(enemyList.begin(), enemyList.end(), [](Enemy& enemy) {enemy.move(1); });

	std::for_each(enemyList.begin(), enemyList.end(), [&](Enemy& enemy) {
		std::for_each(projectileList.begin(), projectileList.end(), [&](Projectile& projectile) {
			if (enemy.collision(projectile.position)) {
				enemy.takeDamage(projectile.damage);
				projectile.takeDamage(projectile.damage);
			}
		});
	});

	projectileList.remove_if([](Projectile projectile) {return projectile.health == 0; });
	enemyList.remove_if([](Enemy enemy) {return enemy.getHealth() == 0; });
	
	std::for_each(enemyList.begin(), enemyList.end(), [](Enemy& enemy) {if (enemy.position.x < 40) enemy.setSide(LEFT); else if (enemy.position.x > 760) enemy.setSide(RIGHT); });


	
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	

	dc.SetBrush(*wxWHITE);
	for (const auto& projectile : projectileList) {
		dc.DrawCircle(projectile.position, projectile.size);
	}

	dc.SetBrush(*wxRED);
	for (const auto& enemy : enemyList) {
		dc.DrawCircle(enemy.position, enemy.size);
	}

	dc.SetBrush(*wxBLUE);
	dc.DrawCircle(hero.position, hero.size);


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

	else {
		projectileList.push_back(Projectile(hero.getProjectileType(), hero.getOrigin(), hero.position));
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

	else {
	
		hero.setPosition(wxPoint(evt.GetPosition().x, hero.position.y));
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
