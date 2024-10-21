#pragma once
#include <wx/wx.h>



enum ProjectileOrigin {
	PLAYER,
	ENEMY
};

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


class Projectile {

public:
	ProjectileType type;
	ProjectileOrigin origin;
	int health, damage;
	wxPoint velocity;
	wxPoint acceleration;
	wxPoint position;
	const wxPoint positionOrigin;
	double size;
	double bounds;

	Projectile(ProjectileType type, ProjectileOrigin origin, wxPoint pos) : type(type), origin(origin), positionOrigin(pos) { setProperties(type, origin); }

	void move(double time);
	bool outOfBounds();

	void takeDamage(int damageAmount);

private:
	void setProperties(ProjectileType type, ProjectileOrigin origin);
};



class Entety {

public:
	int health;
	ProjectileType projectileType;
	ProjectileOrigin origin;
	wxPoint position; // za okroglega
	double size; // za okroglega


	bool collision(wxPoint projectile);

	void takeDamage(int damageAmount) { health -= damageAmount; if (health < 0) health = 0; }
	void heal(int healAmount) { health += healAmount; }

	int getHealth() const { return health; }

	void setPosition(wxPoint position) { this->position = position; }
};


class Enemy : public Entety{ ///////////// v "DrawingCanvas.h" kot list

public:
	Enemy(int health, ProjectileType type, wxPoint position, double size) {
		this->health = health;
		this->projectileType = type;
		this->origin = ENEMY;
		this->position = position;
		this->size = size;
	}
};

class Pratoria : public Entety { ///////////// v "DrawingCanvas.h"

public:
	Pratoria(int health, ProjectileType type, wxPoint position, double size) {
		this->health = health;
		this->projectileType = type;
		this->origin = PLAYER;
		this->position = position;
		this->size = size;
	}
};
