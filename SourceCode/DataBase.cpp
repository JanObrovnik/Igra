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