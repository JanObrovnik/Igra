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
std::istream& operator>>(std::istream& is, koordinate& ko);


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

	void setExist(bool ex) {
		exist = ex;
	}
	void setLocation(koordinate xy) {
		point = xy;
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

class Door {

private:
	bool locked;
	koordinate point;

public:
	Door() : locked(false), point(koordinate()) {}
	Door(koordinate xy) : locked(true), point(xy) {}
	Door(bool locked, koordinate xy) : locked(locked), point(xy) {}

	bool getLocked() const {
		return locked;
	}
	koordinate getLocation() const {
		return point;
	}

	void setLocked(bool isLocked) {
		locked = isLocked;
	}
	void setLocation(koordinate xy) {
		point = xy;
	}

	void effect() {
		if (locked) unlock();
		else lock();
	}
	void unlock() {
		locked = false;
	}
	void lock() {
		locked = true;
	}
};

class Portal { ////////////// Pregled arrayev

private:
	bool exist;
	koordinate point0, point1;

public:
	Portal() : exist(false), point0(koordinate()), point1(koordinate()) {}
	Portal(koordinate xy0, koordinate xy1) : exist(true), point0(xy0), point1(xy1) {}
	Portal(bool open, koordinate xy0, koordinate xy1) : exist(open), point0(xy0), point1(xy1) {}

	bool getExist() const {
		return exist;
	}
	koordinate getLocation0() const {
		return point0;
	}
	koordinate getLocation1() const {
		return point1;
	}

	void setExist(bool ex) {
		exist = ex;
	}
	void setLocation0(koordinate xy) {
		point0 = xy;
	}
	void setLocation1(koordinate xy) {
		point1 = xy;
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

	void setHardness(unsigned short hardness) {
		hardnessLevel = hardness;
	}
	void setLocation(koordinate xy) {
		point = xy;
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

	void setHeal(unsigned short heal) {
		healLevel = heal;
	}
	void setLocation(koordinate xy) {
		point = xy;
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
	Coin() : value(1), point(koordinate()) {}
	Coin(koordinate xy) : value(1), point(koordinate(xy)) {}
	Coin(unsigned short value, koordinate xy) : value(value), point(koordinate(xy)) {}

	unsigned short getValue() const {
		return value;
	}
	koordinate getLocation() const {
		return point;
	}

	void setValue(unsigned short valueAmount) {
		value = valueAmount;
	}
	void setLocation(koordinate xy) {
		point = xy;
	}
};

class Key {

private:
	koordinate point;

public:
	Key() : point(koordinate()) {}
	Key(koordinate xy) : point(xy) {}

	koordinate getLocation() const {
		return point;
	}

	void setLocation(koordinate xy) {
		point = xy;
	}
};



class Hero {

private:
	int hHp, maxHHp;
	int attack, defence;
	int coins, keys;
	koordinate point, pastPoint;

public:
	Hero() : hHp(100), maxHHp(hHp), attack(6), defence(1), coins(0), keys(0), point(koordinate()), pastPoint(point) {}
	Hero(int hp) : hHp(hp), maxHHp(hHp), attack(6), defence(1), coins(0), keys(0), point(koordinate()), pastPoint(point) {}
	Hero(int hp, int initAttack, int initDefence, koordinate xy) : hHp(hp), maxHHp(hHp), attack(initAttack), defence(initDefence), coins(0), keys(0), point(xy), pastPoint(point) {}
	Hero(int hp, int initAttack, int initDefence, int coinsAmouth, int keysAmouth, koordinate xy) : hHp(hp), maxHHp(hHp), attack(initAttack), defence(initDefence), coins(coinsAmouth), keys(keysAmouth), point(xy), pastPoint(point) {}

	int getHp() const {
		return hHp;
	}
	int getMaxHp() const {
		return maxHHp;
	}
	int getAttack() const{
		return attack;
	}
	int getDefence() const {
		return defence;
	}
	int getCoins() const {
		return coins;
	}
	int getKeys() const {
		return keys;
	}
	koordinate getLocation() const {
		return point;
	}

	void setHp(int hp) {
		hHp = hp;
	}
	void setMaxHp(int maxHp) {
		maxHHp = maxHp;
	}
	void setAttack(int attackValue) {
		attack = attackValue;
	}
	void setDefence(int defenceValue) {
		defence = defenceValue;
	}
	void setCoins(int coinsAmount) {
		coins = coinsAmount;
	}
	void setKeys(int keysAmount) {
		keys = keysAmount;
	}
	void setLocation(koordinate xy) {
		point = xy;
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
	void combat(int incomingAttack) {
		int damage = incomingAttack - defence;
		if (damage < 1) hHp--;
		else hHp -= damage;
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

class Monster {

private:
	int mHp, maxmHp, attack, defence;
	int coins;
	koordinate point;

public:
	Monster() : mHp(20), maxmHp(mHp), attack(4), defence(0), coins(1), point(koordinate()) {}
	Monster(int hp, koordinate xy) : mHp(hp), maxmHp(mHp), attack(4), defence(0), coins(1), point(xy) {}
	Monster(int hp, int attack, int defence, int coins, koordinate xy) : mHp(hp), maxmHp(mHp), attack(attack), defence(defence), coins(coins), point(xy) {}

	int getHp() const {
		return mHp;
	}
	int getMaxHp() const {
		return maxmHp;
	}
	int getAttack() const {
		return attack;
	}
	int getDefence() const {
		return defence;
	}
	int getCoins() const {
		return coins;
	}
	koordinate getLocation() const {
		return point;
	}

	void setHp(int hp) {
		mHp = hp;
	}
	void setMaxHp(int maxHp) {
		maxmHp = maxHp;
	}
	void setAttack(int attackValue) {
		attack = attackValue;
	}
	void setDefence(int defenceValue) {
		defence = defenceValue;
	}
	void setCoins(int coinsAmount) {
		coins = coinsAmount;
	}
	void setLocation(koordinate xy) {
		point = xy;
	}

	void combat(int incomingAttack) {
		int damage = incomingAttack - defence;
		if (damage < 1) mHp--;
		else mHp -= damage;
		if (mHp < 0) mHp = 0;
	}
	bool isDead() const {
		return mHp <= 0;
	}
};



struct WorkArea {
	int minX = 0;
	int maxX = 9;
	int minY = 0;
	int maxY = 9;
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
	std::vector<Monster> seznamPosastiBackup;

public:
	Hero player;
	std::vector<Wall> seznamZidov;
	std::vector<Door> seznamVrat;
	std::vector<Portal> seznamPortalov;
	std::vector<Trap> seznamPasti;
	std::vector<Bandage> seznamZdravil;
	std::vector<Coin> seznamKovancev;
	std::vector<Key> seznamKljucev;
	std::vector<Monster> seznamPosasti;
	WorkArea workArea;

	void makeBackup() {
		playerBackup = player;
		seznamZidovBackup = seznamZidov;
		seznamVratBackup = seznamVrat;
		seznamPortalovBackup = seznamPortalov;
		seznamPastiBackup = seznamPasti;
		seznamZdravilBackup = seznamZdravil;
		seznamKovancevBackup = seznamKovancev;
		seznamKljucevBackup = seznamKljucev;
		seznamPosastiBackup = seznamPosasti;
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
		seznamPosasti = seznamPosastiBackup;
	}

	void clear() {
		player = Hero();
		seznamZidov.clear();
		seznamZidovBackup.clear();
		seznamVrat.clear();
		seznamVratBackup.clear();
		seznamPortalov.clear();
		seznamPortalovBackup.clear();
		seznamPasti.clear();
		seznamPastiBackup.clear();
		seznamZdravil.clear();
		seznamZdravilBackup.clear();
		seznamKovancev.clear();
		seznamKovancevBackup.clear();
		seznamKljucev.clear();
		seznamKljucevBackup.clear();
		seznamPosasti.clear();
		seznamPosastiBackup.clear();
	}
};



void Movement(Seznami* seznami);

bool IllegalMove(Seznami* seznami);
