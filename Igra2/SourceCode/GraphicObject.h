#pragma once
#include <wx/wx.h>
#include <random>


enum ProjectileOrigin {
	PLAYER,
	ENEMY
};

enum ProjectileType { //////////// doloci vsem svoje nastnosti v svojem struct/funkciji...
	NORMAL,
	BURST
};

enum LocationOrigin {
	LEFT,
	RIGHT
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

protected:
	int health;
	ProjectileType projectileType;
	ProjectileOrigin origin;

public:
	wxPoint position; // za okroglega
	double size; // za okroglega

	bool collision(wxPoint projectile);

	void takeDamage(int damageAmount) { health -= damageAmount; if (health < 0) health = 0; }
	void heal(int healAmount) { health += healAmount; }

	int getHealth() const { return health; }
	ProjectileType getProjectileType() const { return projectileType; }
	ProjectileOrigin getOrigin() const { return origin; }

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

	void move(double time);

	void setSide(LocationOrigin side) { this->side = side; }

private:

	std::mt19937 randomGen;
	LocationOrigin side = LEFT;
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
