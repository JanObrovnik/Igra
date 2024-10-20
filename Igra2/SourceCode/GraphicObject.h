#pragma once
#include <wx/wx.h>



enum ProjectileType { //////////// doloci vsem svoje nastnosti v svojem struct/funkciji...
	NORMAL,
	BURST
};



struct GraphicObject {
	wxRect2DDouble rect;
	wxColour colour;
	wxString text;
	wxAffineMatrix2D transform;
};


struct ProjectileDefiner { /////////// verjetno neuporabno zaradi >6<
	ProjectileType type;
	wxPoint2DDouble velocity;
	wxPoint2DDouble acceleration;

	ProjectileDefiner(ProjectileType type, wxPoint2DDouble velocity, wxPoint2DDouble acceleration) : type(type), velocity(velocity), acceleration(acceleration) {}
};

struct Projectile {
	ProjectileType type;
	wxPoint2DDouble velocity; ///////// zamenja >6<
	wxPoint2DDouble acceleration; ///////// zamenja >6<
	wxPoint2DDouble location; ///////// zamenja >6<

	Projectile(ProjectileDefiner def, wxPoint2DDouble loc) : type(def.type), velocity(def.velocity), acceleration(def.acceleration), location(loc) {}
};



class Enemy { ///////////// v "DrawingCanvas.h" kot list

public:
	GraphicObject properties;
	ProjectileDefiner projectileDefiner;

	Enemy(GraphicObject properties, ProjectileDefiner def) : properties(properties), projectileDefiner(def) {}


};


class Pratoria { ///////////// v "DrawingCanvas.h"

private:
	int healt;

public:
	ProjectileDefiner projectileDefiner;

	Pratoria(ProjectileDefiner def) : projectileDefiner(def) {}


	void takeDamage(int damageAmount) { healt -= damageAmount; }
	void heal(int healAmount) { healt += healAmount; }
};
