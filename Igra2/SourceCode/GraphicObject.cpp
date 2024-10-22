#include "GraphicObject.h"



void Projectile::setProperties(ProjectileType type, ProjectileOrigin origin) { // isto za Enemy

	position = positionOrigin;

	switch (type) {

	case NORMAL:
		damage = 1;
		health = 1;
		velocity = wxPoint(0, 1);
		acceleration = wxPoint(0, 0);
		size = 4;
		bounds = 500;
		break;
	
	case BURST:
		damage = 3;
		health = 5;
		velocity = wxPoint(0, 2);
		acceleration = wxPoint(.1, .1); // decimalne ne delajo
		size = 4;
		bounds = 500;
		break;
	
	
	default:
		damage = 1;
		health = 1;
		velocity = wxPoint(0, 1);
		acceleration = wxPoint(0, 0);
		size = 4;
		bounds = 500;
		break;
	}

	if (origin == PLAYER) {
		velocity = velocity * -1;
		acceleration = acceleration * -1;
	}
}


void Projectile::move(double time) {

	position += velocity * time;
	velocity += acceleration * time;
}

bool Projectile::outOfBounds() {

	wxPoint relative = positionOrigin - position;
	return sqrt(pow(relative.x,2) + pow(relative.y,2)) > bounds;
}

void Projectile::takeDamage(int damageAmount) {

	health -= damageAmount; 
	if (health < 0) health = 0;
}



bool Entety::collision(wxPoint projectile) {
	
	wxPoint relative = position - projectile;
	return sqrt(pow(relative.x, 2) + pow(relative.y, 2)) < size;
}

void Enemy::move(double time) {

	std::uniform_int_distribution<int> movement(-1, 1);

	if (side == LEFT) movement = std::uniform_int_distribution<int>(0, 5);
	else if (side == RIGHT) movement = std::uniform_int_distribution<int>(-5, 0);

	position.x += movement(randomGen) * time;
}
