#include "DataBase.h"
#include <iostream>
#include <vector>



static void Movemen(Hero* player, std::vector<Wall>* seznamZidov, std::vector<Trap>* seznamPasti, std::vector<Bandage>* seznamZdravil) {


	for (int i = 0; i < 0; i++); /////////////// dodatek zanke za portal
	for (int i = 0; i < seznamZidov->size(); i++) {
		//std::cout << "seznam Zidov " << i << std::endl;
		if (player->collision((*seznamZidov)[i].getLocation()) && (*seznamZidov)[i].getExist()) {
			player->moveBack();
			
			return; // Prekine funkcijo 'Movement()'
			//break; // Prekine samo zanko 'for()'
		}
	}
	for (int i = 0; i < seznamPasti->size(); i++) {
		//std::cout << "seznam Pasti " << i << std::endl;
		if (player->collision((*seznamPasti)[i].getLocation())) {
			player->takeDamage((*seznamPasti)[i].getHardness());
			seznamPasti->erase(seznamPasti->begin() + i);
			
			return;
			//break;
		}
	}
	for (int i = 0; i < seznamZdravil->size(); i++) {
		//std::cout << "seznam Zdravil " << i << std::endl;
		if (player->collision((*seznamZdravil)[i].getLocation())) {
			player->heal((*seznamZdravil)[i].getHeal());
			seznamZdravil->erase(seznamZdravil->begin() + i);
			
			return;
			//break;
		}
	}
}


int main() {

	Hero player(60, koordinate());

	std::vector<Wall> seznamZidov;
	seznamZidov.push_back(Wall(koordinate(3, 0)));
	seznamZidov.push_back(Wall(koordinate(3, 1)));
	std::vector<Wall> seznamZidovBackup = seznamZidov;

	std::vector<Trap> seznamPasti;
	seznamPasti.push_back(Trap(20, koordinate(1, 2)));
	seznamPasti.push_back(Trap(20, koordinate(2, 2)));
	seznamPasti.push_back(Trap(20, koordinate(3, 2)));
	seznamPasti.push_back(Trap(20, koordinate(6, 9)));
	std::vector<Trap> seznamPastiBackup = seznamPasti;

	std::vector<Bandage> seznamZdravil;
	seznamZdravil.push_back(Bandage(5, koordinate(3, 3)));
	std::vector<Bandage> seznamZdravilBackup = seznamZdravil;




	Movemen(&player, &seznamZidov, &seznamPasti, &seznamZdravil);
	std::cout << "Hp: " << player.getHp() << "; " << player.getLocation() << std::endl;
	std::cout << std::endl;

	while (true) {

		char c;
		std::cin >> c;

		if (c == 'b') break;
		else if (c == 'r') {
			player = Hero(60, koordinate());
			seznamZidov = seznamZidovBackup;
			seznamPasti = seznamPastiBackup;
			seznamZdravil = seznamZdravilBackup;
		}
		else if (c == 'w') player.moveNorth();
		else if (c == 'd') player.moveEast();
		else if (c == 's') player.moveSouth();
		else if (c == 'a') player.moveWest();


		Movemen(&player, &seznamZidov, &seznamPasti, &seznamZdravil);
		std::cout << "Hp: " << player.getHp() << "; " << player.getLocation() << std::endl;
		std::cout << std::endl;
	}
}
