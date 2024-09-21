#include "DataBase.h"
#include <vector>



std::ostream& operator<<(std::ostream& os, const koordinate& ko) {
	return os << "(" << ko.x << " " << ko.y << ")";
}

std::istream& operator>>(std::istream& is, koordinate& ko) {
	char c;
	is >> c >> ko.x >> ko.y >> c;
	return is;
}



void LevelRooms(Seznami* seznami) {
	
	seznami->clear();

	switch (seznami->level) {
	
	case 0:
		seznami->player = Hero(420, 6, 1, seznami->player.getCoins(), seznami->player.getKeys(), koordinate(0, 0));
		seznami->seznamZidov.push_back(Wall(koordinate(3, 0)));
		seznami->seznamZidov.push_back(Wall(koordinate(3, 1)));
		seznami->seznamVrat.push_back(Door(koordinate(0, 4)));
		seznami->seznamPortalov.push_back(Portal(koordinate(4, 0), koordinate(6, 8)));
		seznami->seznamPasti.push_back(Trap(20, koordinate(0, 2)));
		seznami->seznamPasti.push_back(Trap(20, koordinate(1, 2)));
		seznami->seznamPasti.push_back(Trap(20, koordinate(2, 2)));
		seznami->seznamPasti.push_back(Trap(20, koordinate(3, 2)));
		seznami->seznamPasti.push_back(Trap(200, koordinate(6, 9)));
		seznami->seznamZdravil.push_back(Bandage(50, koordinate(3, 3)));
		seznami->seznamKovancev.push_back(Coin(1, koordinate(1, 0)));
		seznami->seznamKovancev.push_back(Coin(5, koordinate(2, 0)));
		seznami->seznamKljucev.push_back(Key(koordinate(0, 1)));
		seznami->seznamKoncev.push_back(End(koordinate(9, 9)));
		seznami->seznamPosasti.push_back(Monster(20, 4, 0, 2, koordinate(9, 6)));
		seznami->seznamPosasti.push_back(Monster(20, 4, 0, 2, koordinate(9, 5)));
		seznami->seznamPosasti.push_back(Monster(20, 4, 0, 2, koordinate(1, 1)));
		break;
	
	case 1:
		seznami->player = Hero(120, 6, 1, seznami->player.getCoins(), seznami->player.getKeys(), koordinate(0, 4));
		seznami->seznamZidov.push_back(Wall(koordinate(0, 2)));
		seznami->seznamZidov.push_back(Wall(koordinate(1, 2)));
		seznami->seznamZidov.push_back(Wall(koordinate(2, 2)));
		seznami->seznamZidov.push_back(Wall(koordinate(3, 2)));
		seznami->seznamZidov.push_back(Wall(koordinate(3, 3)));
		seznami->seznamZidov.push_back(Wall(koordinate(3, 5)));
		seznami->seznamZidov.push_back(Wall(koordinate(3, 6)));
		seznami->seznamZidov.push_back(Wall(koordinate(2, 6)));
		seznami->seznamZidov.push_back(Wall(koordinate(1, 6)));
		seznami->seznamZidov.push_back(Wall(koordinate(0, 6)));
		seznami->seznamZidov.push_back(Wall(koordinate(2, 0)));
		seznami->seznamZidov.push_back(Wall(koordinate(2, 1)));
		seznami->seznamVrat.push_back(Door(koordinate(3, 4)));
		seznami->seznamPortalov.push_back(Portal(koordinate(0, 0), koordinate(2, 3)));
		seznami->seznamKovancev.push_back(Coin(5, koordinate(2, 4)));
		seznami->seznamKljucev.push_back(Key(koordinate(0, 1)));
		seznami->seznamKoncev.push_back(End(koordinate(9, 0)));
		seznami->seznamPosasti.push_back(Monster(32, 6, 2, 5, koordinate(4, 4)));
		break;

	default:
		break;
	}

	seznami->makeBackup();
	Movement(seznami);
}



void Movement(Seznami* seznami) {

	if (IllegalMove(seznami)) {
		seznami->player.moveBack();

		return;
	}


	for (int i = 0; i < seznami->seznamZidov.size(); i++) {
		if (seznami->player.collision(seznami->seznamZidov[i].getLocation()) && seznami->seznamZidov[i].getExist()) {
			seznami->player.moveBack();

			return; // Prekine funkcijo 'Movement()'
			//break; // Prekine samo zanko 'for()'
		}
	}
	for (int i = 0; i < seznami->seznamVrat.size(); i++) {
		if (seznami->player.collision(seznami->seznamVrat[i].getLocation()) && seznami->seznamVrat[i].getLocked()) {
			if (seznami->player.getKeys() > 0) {
				seznami->seznamVrat[i].unlock();
				seznami->player.loseKey();
			}
			else {
				seznami->player.moveBack();
			}

			return;
			//break;
		}
	}
	for (int i = 0; i < seznami->seznamPortalov.size(); i++) {
		if (seznami->player.collision(seznami->seznamPortalov[i])) {
			seznami->player.teleport(seznami->seznamPortalov[i]);

			return;
			//break;
		}
	}
	for (int i = 0; i < seznami->seznamPasti.size(); i++) {
		if (seznami->player.collision(seznami->seznamPasti[i].getLocation())) {
			seznami->player.takeDamage(seznami->seznamPasti[i].getHardness());
			seznami->seznamPasti.erase(seznami->seznamPasti.begin() + i);

			return;
			//break;
		}
	}
	for (int i = 0; i < seznami->seznamZdravil.size(); i++) {
		if (seznami->player.collision(seznami->seznamZdravil[i].getLocation())) {
			seznami->player.heal(seznami->seznamZdravil[i].getHeal());
			seznami->seznamZdravil.erase(seznami->seznamZdravil.begin() + i);

			return;
			//break;
		}
	}
	for (int i = 0; i < seznami->seznamKovancev.size(); i++) {
		if (seznami->player.collision(seznami->seznamKovancev[i].getLocation())) {
			seznami->player.addCoins(seznami->seznamKovancev[i].getValue());
			seznami->seznamKovancev.erase(seznami->seznamKovancev.begin() + i);

			return;
			//break;
		}
	}
	for (int i = 0; i < seznami->seznamKljucev.size(); i++) {
		if (seznami->player.collision(seznami->seznamKljucev[i].getLocation())) {
			seznami->player.addKey();
			seznami->seznamKljucev.erase(seznami->seznamKljucev.begin() + i);

			return;
			//break;
		}
	}
	for (int i = 0; i < seznami->seznamKljucev.size(); i++) {
		if (seznami->player.collision(seznami->seznamKljucev[i].getLocation())) {
			seznami->player.addKey();
			seznami->seznamKljucev.erase(seznami->seznamKljucev.begin() + i);

			return;
			//break;
		}
	}
	for (int i = 0; i < seznami->seznamKoncev.size(); i++) {
		if (seznami->player.collision(seznami->seznamKoncev[i].getLocation())) {
			seznami->level++;
			LevelRooms(seznami);

			return;
			//break;
		}
	}
	for (int i = 0; i < seznami->seznamPosasti.size(); i++) {
		if (seznami->player.collision(seznami->seznamPosasti[i].getLocation())) {
			seznami->player.combat(seznami->seznamPosasti[i].getAttack());
			seznami->seznamPosasti[i].combat(seznami->player.getAttack());
			if (seznami->seznamPosasti[i].isDead()) {
				seznami->player.addCoins(seznami->seznamPosasti[i].getCoins());
				seznami->seznamPosasti.erase(seznami->seznamPosasti.begin() + i);
			}
			else {
				seznami->player.moveBack();
			}

			return;
			//break;
		}
	}
}

bool IllegalMove(Seznami* seznami) {

	return seznami->player.getLocation().x < seznami->workArea.minX ||
		   seznami->player.getLocation().x > seznami->workArea.maxX ||
		   seznami->player.getLocation().y < seznami->workArea.minY ||
		   seznami->player.getLocation().y > seznami->workArea.maxY;
}


void Shrani(Seznami* seznami, std::string pot) {

	std::ofstream shrani;
	shrani.open(pot, std::ios::out);

	if (shrani.is_open()) {

		shrani << "IgraV0.1" << std::endl;
		shrani << __DATE__ << ", " << __TIME__ << std::endl << std::endl;

		shrani << "Hero: ";
		shrani << 1 << std::endl;
		shrani << seznami->player.getHp() << ", ";
		shrani << seznami->player.getMaxHp() << ", ";
		shrani << seznami->player.getAttack() << ", ";
		shrani << seznami->player.getDefence() << ", ";
		shrani << seznami->player.getCoins() << ", ";
		shrani << seznami->player.getKeys() << ", ";
		shrani << seznami->player.getLocation() << ", " << std::endl;
		shrani << std::endl;

		shrani << "Wall: ";
		shrani << seznami->seznamZidov.size() << std::endl;
		for (int i = 0; i < seznami->seznamZidov.size(); i++) {
			shrani << seznami->seznamZidov[i].getExist() << ", ";
			shrani << seznami->seznamZidov[i].getLocation() << ", " << std::endl;
		}
		shrani << std::endl;

		shrani << "Door: ";
		shrani << seznami->seznamVrat.size() << std::endl;
		for (int i = 0; i < seznami->seznamVrat.size(); i++) {
			shrani << seznami->seznamVrat[i].getLocked() << ", ";
			shrani << seznami->seznamVrat[i].getLocation() << ", " << std::endl;
		}
		shrani << std::endl;

		shrani << "Portal: ";
		shrani << seznami->seznamPortalov.size() << std::endl;
		for (int i = 0; i < seznami->seznamPortalov.size(); i++) {
			shrani << seznami->seznamPortalov[i].getExist() << ", ";
			shrani << seznami->seznamPortalov[i].getLocation0() << ", ";
			shrani << seznami->seznamPortalov[i].getLocation1() << ", " << std::endl;
		}
		shrani << std::endl;

		shrani << "Trap: ";
		shrani << seznami->seznamPasti.size() << std::endl;
		for (int i = 0; i < seznami->seznamPasti.size(); i++) {
			shrani << seznami->seznamPasti[i].getHardness() << ", ";
			shrani << seznami->seznamPasti[i].getLocation() << ", " << std::endl;
		}
		shrani << std::endl;

		shrani << "Bandage: ";
		shrani << seznami->seznamZdravil.size() << std::endl;
		for (int i = 0; i < seznami->seznamZdravil.size(); i++) {
			shrani << seznami->seznamZdravil[i].getHeal() << ", ";
			shrani << seznami->seznamZdravil[i].getLocation() << ", " << std::endl;
		}
		shrani << std::endl;

		shrani << "Coin: ";
		shrani << seznami->seznamKovancev.size() << std::endl;
		for (int i = 0; i < seznami->seznamKovancev.size(); i++) {
			shrani << seznami->seznamKovancev[i].getValue() << ", ";
			shrani << seznami->seznamKovancev[i].getLocation() << ", " << std::endl;
		}
		shrani << std::endl;

		shrani << "Key: ";
		shrani << seznami->seznamKljucev.size() << std::endl;
		for (int i = 0; i < seznami->seznamKljucev.size(); i++) {
			shrani << seznami->seznamKljucev[i].getLocation() << ", " << std::endl;
		}
		shrani << std::endl;

		shrani << "Monster: ";
		shrani << seznami->seznamPosasti.size() << std::endl;
		for (int i = 0; i < seznami->seznamPosasti.size(); i++) {
			shrani << seznami->seznamPosasti[i].getHp() << ", ";
			shrani << seznami->seznamPosasti[i].getMaxHp() << ", ";
			shrani << seznami->seznamPosasti[i].getAttack() << ", ";
			shrani << seznami->seznamPosasti[i].getDefence() << ", ";
			shrani << seznami->seznamPosasti[i].getCoins() << ", ";
			shrani << seznami->seznamPosasti[i].getLocation() << ", " << std::endl;
		}
		shrani << std::endl;
	}
}

void Nalozi(Seznami* seznami, std::string pot) {

	std::ifstream nalozi;
	nalozi.open(pot, std::ios::in);

	if (nalozi.is_open()) {

		seznami->clear();

		std::string bes;
		char c;
		int st, pon;
		koordinate xy;

		nalozi >> bes;
		if (bes != "IgraV0.1") wxLogStatus("Wrong file");
		nalozi >> bes >> bes >> bes >> bes;

		nalozi >> bes >> pon;
		if (bes != "Hero:") wxLogStatus("No Hero found");
		nalozi >> st >> c; seznami->player.setHp(st);
		nalozi >> st >> c; seznami->player.setMaxHp(st);
		nalozi >> st >> c; seznami->player.setAttack(st);
		nalozi >> st >> c; seznami->player.setDefence(st);
		nalozi >> st >> c; seznami->player.setCoins(st);
		nalozi >> st >> c; seznami->player.setKeys(st);
		nalozi >> xy >> c; seznami->player.setLocation(xy);

		nalozi >> bes >> pon;
		if (bes != "Wall:") wxLogStatus("No Wall found");
		for (int i = 0; i < pon; i++) {
			seznami->seznamZidov.push_back(Wall());
			nalozi >> st >> c; seznami->seznamZidov[i].setExist(st);
			nalozi >> xy >> c; seznami->seznamZidov[i].setLocation(xy);
		}

		nalozi >> bes >> pon;
		if (bes != "Door:") wxLogStatus("No Door found");
		for (int i = 0; i < pon; i++) {
			seznami->seznamVrat.push_back(Door());
			nalozi >> st >> c; seznami->seznamVrat[i].setLocked(st);
			nalozi >> xy >> c; seznami->seznamVrat[i].setLocation(xy);
		}

		nalozi >> bes >> pon;
		if (bes != "Portal:") wxLogStatus("No Portal found");
		for (int i = 0; i < pon; i++) {
			seznami->seznamPortalov.push_back(Portal());
			nalozi >> st >> c; seznami->seznamPortalov[i].setExist(st);
			nalozi >> xy >> c; seznami->seznamPortalov[i].setLocation0(xy);
			nalozi >> xy >> c; seznami->seznamPortalov[i].setLocation1(xy);
		}

		nalozi >> bes >> pon;
		if (bes != "Trap:") wxLogStatus("No Trap found");
		for (int i = 0; i < pon; i++) {
			seznami->seznamPasti.push_back(Trap());
			nalozi >> st >> c; seznami->seznamPasti[i].setHardness(st);
			nalozi >> xy >> c; seznami->seznamPasti[i].setLocation(xy);
		}

		nalozi >> bes >> pon;
		if (bes != "Bandage:") wxLogStatus("No Bandage found");
		for (int i = 0; i < pon; i++) {
			seznami->seznamZdravil.push_back(Bandage());
			nalozi >> st >> c; seznami->seznamZdravil[i].setHeal(st);
			nalozi >> xy >> c; seznami->seznamZdravil[i].setLocation(xy);
		}

		nalozi >> bes >> pon;
		if (bes != "Coin:") wxLogStatus("No Coin found");
		for (int i = 0; i < pon; i++) {
			seznami->seznamKovancev.push_back(Coin());
			nalozi >> st >> c; seznami->seznamKovancev[i].setValue(st);
			nalozi >> xy >> c; seznami->seznamKovancev[i].setLocation(xy);
		}

		nalozi >> bes >> pon;
		if (bes != "Key:") wxLogStatus("No Key found");
		for (int i = 0; i < pon; i++) {
			seznami->seznamKljucev.push_back(Key());
			nalozi >> xy >> c; seznami->seznamKljucev[i].setLocation(xy);
		}

		nalozi >> bes >> pon;
		if (bes != "Monster:") wxLogStatus("No Monster found");
		for (int i = 0; i < pon; i++) {
			seznami->seznamPosasti.push_back(Monster());
			nalozi >> st >> c; seznami->seznamPosasti[i].setHp(st);
			nalozi >> st >> c; seznami->seznamPosasti[i].setMaxHp(st);
			nalozi >> st >> c; seznami->seznamPosasti[i].setAttack(st);
			nalozi >> st >> c; seznami->seznamPosasti[i].setDefence(st);
			nalozi >> st >> c; seznami->seznamPosasti[i].setCoins(st);
			nalozi >> xy >> c; seznami->seznamPosasti[i].setLocation(xy);
		}

		seznami->makeBackup();
	}
}