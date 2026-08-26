#include "randEnc.h"
#include "mutRat.h"
#include "mutHuman.h"

randEnc::randEnc() : randEncMap(15, 15) {
	enemyCount = 6;

	randEncEnemy = new enemy * [enemyCount];

	randEncEnemy[0] = new mutRat(0, 0, 0);
	randEncEnemy[1] = new mutRat(0, 0, 1);
	randEncEnemy[2] = new mutRat(0, 0, 2);
	randEncEnemy[3] = new mutHuman(0, 0, 3);
	randEncEnemy[4] = new mutHuman(0, 0, 4);
	randEncEnemy[5] = new mutHuman(0, 0, 5);
}

randEnc::~randEnc() {
	for (int i = 0; i < enemyCount; i++) delete randEncEnemy[i];
	{
		delete[] randEncEnemy;
	}
}

void randEnc::printRandEncMap(int randencnum) {
	randEncMap.initPOImap();
	//randEncMap.setpos(0, 2, 'X'); //entrance and exit

	if (randencnum == 1) {
		//------------------------------------
		//for monsters that you dont want to spawn, set spawn state to false.
		//-----------------------------------
		//first check if sewerEnemy arent dead/nullptrs. if it isnt, set its position.

		if (randEncEnemy[0] != nullptr) {
			randEncEnemy[0]->setPosition(11, 1);
			randEncEnemy[0]->setSpawnState(true);
		}
		if (randEncEnemy[1] != nullptr) {
			randEncEnemy[1]->setPosition(5, 5);
			randEncEnemy[1]->setSpawnState(true);
		}
		if (randEncEnemy[2] != nullptr) {
			randEncEnemy[2]->setSpawnState(false);
		}
		if (randEncEnemy[3] != nullptr) {
			randEncEnemy[3]->setPosition(6, -7);
			randEncEnemy[3]->setSpawnState(true);
		}
		if (randEncEnemy[4] != nullptr) {
			randEncEnemy[4]->setPosition(-14, -1);
			randEncEnemy[4]->setSpawnState(true);
		}
		if (randEncEnemy[5] != nullptr) {
			randEncEnemy[5]->setSpawnState(false);
		}
	}
}