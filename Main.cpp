#include "DataBase.h"
#include <iostream>
#include <vector>


void Movemen(Hero* player, std::vector<Wall>* seznamZidov, std::vector<Bandage>* seznamZdravil) {

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

	Hero player(60, koordinate(2, 2));
	std::cout << "Hp: " << player.getHp() << std::endl;


	std::vector<Wall> seznamZidov;
	seznamZidov.push_back(Wall(20, koordinate(1, 2)));
	seznamZidov.push_back(Wall(20, koordinate(2, 2)));
	seznamZidov.push_back(Wall(20, koordinate(3, 2)));
	seznamZidov.push_back(Wall(20, koordinate(6, 9)));

	std::vector<Bandage> seznamZdravil;
	seznamZdravil.push_back(Bandage(5, koordinate(3, 3)));


	Movemen(&player, &seznamZidov, &seznamZdravil);
	std::cout << "Hp: " << player.getHp() << std::endl;
	player.moveEast();
	
	Movemen(&player, &seznamZidov, &seznamZdravil);
	std::cout << "Hp: " << player.getHp() << std::endl;
	player.moveSouth();

	Movemen(&player, &seznamZidov, &seznamZdravil);
	std::cout << "Hp: " << player.getHp() << std::endl;
}
