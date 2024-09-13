#pragma once
#include <iostream>

class koordinate {

public:
	int x, y;

	koordinate() : x(0), y(0) {}
	koordinate(int xx, int yy) : x(xx), y(yy) {}

	void write() const {
		std::cout << "x: " << x << " | y: " << y << std::endl;
	}

	double abs() {
		return sqrt(x * x + y * y);
	}
};


std::ostream& operator<<(std::ostream& os, const koordinate& ko);


inline bool operator==(const koordinate& ko1, const koordinate& ko2) {
	return ko1.x == ko2.x && ko1.y == ko2.y;
}

inline bool operator!=(const koordinate& ko1, const koordinate& ko2) {
	return !(ko1 == ko2);
}

inline bool operator<(koordinate& ko1, koordinate& ko2) {
	return ko1.abs() < ko2.abs();
}

inline bool operator>(koordinate& ko1, koordinate& ko2) {
	return ko1.abs() > ko2.abs();
}


inline koordinate operator+(const koordinate& ko1, const koordinate& ko2) {
	return koordinate(ko1.x + ko2.x, ko1.y + ko2.y);
}

inline koordinate operator+(const koordinate& ko1, const int dod) {
	return koordinate(ko1.x + dod, ko1.y + dod);
}

inline koordinate operator-(const koordinate& ko1, const koordinate& ko2) {
	return koordinate(ko1.x - ko2.x, ko1.y - ko2.y);
}

inline koordinate operator-(const koordinate& ko1, const int dod) {
	return koordinate(ko1.x - dod, ko1.y - dod);
}

inline koordinate operator*(const koordinate& ko1, const koordinate& ko2) {
	return koordinate(ko1.x * ko2.x, ko1.y * ko2.y);
}

inline koordinate operator*(const koordinate& ko1, const int dod) {
	return koordinate(ko1.x * dod, ko1.y * dod);
}

inline koordinate operator/(const koordinate& ko1, const koordinate& ko2) {
	return koordinate(ko1.x / ko2.x, ko1.y / ko2.y);
}

inline koordinate operator/(const koordinate& ko1, const int dod) {
	return koordinate(ko1.x / dod, ko1.y / dod);
}



class Wall { //////////////////

private:
};

class Trap {

private:
	unsigned short hardnessLevel;
	koordinate point;

public:
	Trap() : hardnessLevel(0), point(koordinate()) {}
	Trap(koordinate xy) : hardnessLevel(0), point(xy) {}
	Trap(unsigned short hardness, koordinate xy) : hardnessLevel(hardness), point(xy) {}

	unsigned short getHardness() const {
		return hardnessLevel;
	}
	koordinate getLocation() const {
		return point;
	}

	void destroy() {
		hardnessLevel = 0;
	}
};

class Bandage {

private:
	unsigned short healLevel;
	koordinate point;

public:
	Bandage() : healLevel(0), point(koordinate()) {}
	Bandage(koordinate xy) : healLevel(0), point(xy) {}
	Bandage(unsigned short hardness, koordinate xy) : healLevel(hardness), point(xy) {}

	unsigned short getHeal() const {
		return healLevel;
	}
	koordinate getLocation() const {
		return point;
	}

	void destroy() {
		healLevel = 0;
	}
};



class Hero {

private:
	int hHp, maxHHp;
	koordinate point, pastPoint; /////////////// dodatek spomina za wall

public:
	Hero() : hHp(100), maxHHp(hHp), point(koordinate()), pastPoint(point) {}
	Hero(int hp) : hHp(hp), maxHHp(hHp), point(koordinate()), pastPoint(point) {}
	Hero(int hp, koordinate xy) : hHp(hp), maxHHp(hHp), point(xy), pastPoint(point) {}

	int getHp() const {
		return hHp;
	}
	int getMaxHp() const {
		return maxHHp;
	}
	koordinate getLocation() const {
		return point;
	}

	void heal(unsigned int amount) {
		hHp += amount;
		if (hHp > maxHHp) hHp = maxHHp;
	}
	void fullHeal() {
		hHp = maxHHp;
	}
	void takeDamage(unsigned int amount) {
		hHp -= amount;
		if (hHp < 0) hHp = 0;
	}

	void moveNorth() {
		if (canMove()) point.y--;
		else cannotMoveMessage();
	}
	void moveEast() {
		if (canMove()) point.x++;
		else cannotMoveMessage();
	}
	void moveSouth() {
		if (canMove()) point.y++;
		else cannotMoveMessage();
	}
	void moveWest() {
		if (canMove()) point.x--;
		else cannotMoveMessage();
	}
	inline bool canMove() const {
		return hHp > 0;
	}
	inline void cannotMoveMessage() const {
		std::cout << "Cannot move!" << std::endl;
	}
};