#include "DataBase.h"
#include <vector>



static void Movement(Seznami* seznami) {

	

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
}
