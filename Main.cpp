#include "DataBase.h"
#include <iostream>
#include <vector>


void Movemen(Hero* player, std::vector<Trap>* seznamZidov, std::vector<Bandage>* seznamZdravil) {

	for (int i = 0; i < seznamZidov->size(); i++) {
		if (player->getLocation() == (*seznamZidov)[i].getLocation()) {
			player->takeDamage((*seznamZidov)[i].getHardness());
			seznamZidov->erase(seznamZidov->begin() + i);
			break;
		}
	}
	for (int i = 0; i < seznamZdravil->size(); i++) {
		if (player->getLocation() == (*seznamZdravil)[i].getLocation()) {
			player->heal((*seznamZdravil)[i].getHeal());
			seznamZdravil->erase(seznamZdravil->begin() + i);
			break;
		}
	}
}


int main() {

	Hero player(60, koordinate());

	std::vector<Trap> seznamZidov;
	seznamZidov.push_back(Trap(20, koordinate(1, 2)));
	seznamZidov.push_back(Trap(20, koordinate(2, 2)));
	seznamZidov.push_back(Trap(20, koordinate(3, 2)));
	seznamZidov.push_back(Trap(20, koordinate(6, 9)));

	std::vector<Bandage> seznamZdravil;
	seznamZdravil.push_back(Bandage(5, koordinate(3, 3)));


	while (true) {

		Movemen(&player, &seznamZidov, &seznamZdravil);
		std::cout << "Hp: " << player.getHp() << "; " << player.getLocation() << std::endl;
		std::cout << std::endl;

		char c;
		std::cin >> c;

		if (c == 'b') break;
		else if (c == 'r') player = Hero(60, koordinate());

		else if (c == 'w') player.moveNorth();
		else if (c == 'd') player.moveEast();
		else if (c == 's') player.moveSouth();
		else if (c == 'a') player.moveWest();
	}
}
