#pragma once
#include <iostream>
#include <vector>


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



class Wall {

private:
	bool exist;
	koordinate point;

public:
	Wall() : exist(true), point(koordinate()) {}
	Wall(koordinate xy) : exist(true), point(xy) {}
	Wall(bool ex, koordinate xy) : exist(ex), point(xy) {}

	bool getExist() const {
		return exist;
	}
	koordinate getLocation() const {
		return point;
	}

	void effect() {
		if (exist) destroy();
		else build();
	}
	void destroy() {
		exist = false;
	}
	void build() {
		exist = true;
	}
};

class Door { /////////////////////

private:
	bool exist;
	koordinate point;

public:
	Door(koordinate xy) : exist(true), point(xy) {}
	Door(bool locked, koordinate xy) : exist(locked), point(xy) {}

	bool getLocked() const {
		return exist;
	}
	koordinate getLocation() const {
		return point;
	}

	void effect() {
		if (exist) unlock();
		else lock();
	}
	void unlock() {
		exist = false;
	}
	void lock() {
		exist = true;
	}
};

class Portal { ////////////// Pregled arrayev

private:
	bool exist;
	koordinate point0, point1;

public:
	Portal(koordinate xy0, koordinate xy1) : exist(true), point0(xy0), point1(xy1) {}
	Portal(bool open, koordinate xy0, koordinate xy1) : exist(open), point0(xy0), point1(xy1) {}

	koordinate getLocation0() const {
		return point0;
	}
	koordinate getLocation1() const {
		return point1;
	}

	void open() {
		exist = true;
	}
	void close() {
		exist = false;
	}
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

class Coin {

private:
	unsigned short value;
	koordinate point;

public:
	Coin(koordinate xy) : value(1), point(koordinate(xy)) {}
	Coin(unsigned short value, koordinate xy) : value(value), point(koordinate(xy)) {}

	unsigned short getValue() const {
		return value;
	}
	koordinate getLocation() const {
		return point;
	}
};

class Key {

private:
	koordinate point;

public:
	Key(koordinate xy) : point(xy) {}

	koordinate getLocation() const {
		return point;
	}
};



class Hero {

private:
	int hHp, maxHHp;
	int coins, keys;
	koordinate point, pastPoint;

public:
	Hero() : hHp(100), maxHHp(hHp), coins(0), keys(0), point(koordinate()), pastPoint(point) {}
	Hero(int hp) : hHp(hp), maxHHp(hHp), coins(0), keys(0), point(koordinate()), pastPoint(point) {}
	Hero(int hp, koordinate xy) : hHp(hp), maxHHp(hHp), coins(0), keys(0), point(xy), pastPoint(point) {}
	Hero(int hp, int coinsAmouth, int keysAmouth, koordinate xy) : hHp(hp), maxHHp(hHp), coins(coinsAmouth), keys(keysAmouth), point(xy), pastPoint(point) {}

	int getHp() const {
		return hHp;
	}
	int getMaxHp() const {
		return maxHHp;
	}
	koordinate getLocation() const {
		return point;
	}
	int getCoins() const {
		return coins;
	}
	int getKeys() const {
		return keys;
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
	void addCoins(int value) {
		coins += value;
	}
	void addKey() {
		keys++;
	}
	void loseKey() {
		keys--;
	}

	void moveNorth() {
		if (canMove()) {
			pastPoint = point;
			point.y--;
		}
		else cannotMoveMessage();
	}
	void moveEast() {
		if (canMove()) {
			pastPoint = point;
			point.x++;
		}
		else cannotMoveMessage();
	}
	void moveSouth() {
		if (canMove()) {
			pastPoint = point;
			point.y++;
		}
		else cannotMoveMessage();
	}
	void moveWest() {
		if (canMove()) {
			pastPoint = point;
			point.x--;
		}
		else cannotMoveMessage();
	}
	inline bool canMove() const {
		return hHp > 0;
	}
	inline void cannotMoveMessage() const {
		std::cout << "Cannot move!" << std::endl;
	}
	void moveBack() {
		point = pastPoint;
	}
	void teleport(Portal portal) {
		point = teleportLocation(portal);
	}
	inline koordinate teleportLocation(Portal portal) const {
		if (point == portal.getLocation0()) return portal.getLocation1();
		if (point == portal.getLocation1()) return portal.getLocation0();
	}

	inline bool collision(koordinate ko) const {
		return point == ko;
	}
	inline bool collision(Portal portal) const {
		return point == portal.getLocation0() || point == portal.getLocation1();
	}
};


struct Seznami {

private:
	Hero playerBackup;
	std::vector<Wall> seznamZidovBackup;
	std::vector<Door> seznamVratBackup;
	std::vector<Portal> seznamPortalovBackup;
	std::vector<Trap> seznamPastiBackup;
	std::vector<Bandage> seznamZdravilBackup;
	std::vector<Coin> seznamKovancevBackup;
	std::vector<Key> seznamKljucevBackup;

public:
	Hero player;
	std::vector<Wall> seznamZidov;
	std::vector<Door> seznamVrat;
	std::vector<Portal> seznamPortalov;
	std::vector<Trap> seznamPasti;
	std::vector<Bandage> seznamZdravil;
	std::vector<Coin> seznamKovancev;
	std::vector<Key> seznamKljucev;

	void makeBackup() {
		playerBackup = player;
		seznamZidovBackup = seznamZidov;
		seznamVratBackup = seznamVrat;
		seznamPortalovBackup = seznamPortalov;
		seznamPastiBackup = seznamPasti;
		seznamZdravilBackup = seznamZdravil;
		seznamKovancevBackup = seznamKovancev;
		seznamKljucevBackup = seznamKljucev;
	}

	void restore() {
		player = playerBackup;
		seznamZidov = seznamZidovBackup;
		seznamVrat = seznamVratBackup;
		seznamPortalov = seznamPortalovBackup;
		seznamPasti = seznamPastiBackup;
		seznamZdravil = seznamZdravilBackup;
		seznamKovancev = seznamKovancevBackup;
		seznamKljucev = seznamKljucevBackup;
	}
};