#include "sewer.h"
#include "mutRat.h"
#include "mutHuman.h"

sewer::sewer() : sewerMap(5, 30) {
	enemyCount = 5;

	sewerEnemy = new enemy * [enemyCount];

	//sewer 1
	sewerEnemy[0] = new mutRat(0, 0, 0);
	sewerEnemy[1] = new mutRat(0, 0, 1);
	sewerEnemy[2] = new mutRat(0, 0, 2);
	sewerEnemy[3] = new mutHuman(0, 0, 3);
	sewerEnemy[4] = new mutHuman(0, 0, 4);
}

sewer::~sewer() {
	for (int i = 0; i < enemyCount; i++) delete sewerEnemy[i];
	{
		delete[] sewerEnemy;
	}
}

void sewer::printSewerMap(int sewernum) {
	sewerMap.initPOImap();
	sewerMap.setpos(0, 2, 'X'); //entrance and exit

	if (sewernum == 1) {
		//------------------------------------
		//for monsters that you dont want to spawn, set spawn state to false.
		//-----------------------------------
		//first check if sewerEnemy arent dead/nullptrs. if it isnt, set its position.

		//rat positions
		if (sewerEnemy[0] != nullptr) { 
			sewerEnemy[0]->setPosition(13, 0); 
			sewerEnemy[0]->setSpawnState(true);
		}
		if (sewerEnemy[1] != nullptr) {
			sewerEnemy[1]->setPosition(23, 2); 
			sewerEnemy[1]->setSpawnState(true);
		}
		if (sewerEnemy[2] != nullptr) {
			sewerEnemy[2]->setSpawnState(false);//dont spawn a third mutrat
			sewerEnemy[2] = nullptr;
		}

		//human positions
		if (sewerEnemy[3] != nullptr) { 
			sewerEnemy[3]->setPosition(8, 4); 
			sewerEnemy[3]->setSpawnState(true);
		}
		if (sewerEnemy[4] != nullptr) { 
			sewerEnemy[4]->setSpawnState(false);//dont spawn a second muthuman
			sewerEnemy[4] = nullptr;
		}

		sewerMap.setpos(29, 0, 'C'); //chest
	}
	if (sewernum == 2) {
		//rat positions
		if (sewerEnemy[0] != nullptr) {
			sewerEnemy[0]->setPosition(8, 2);
			sewerEnemy[0]->setSpawnState(true);
		}
		if (sewerEnemy[1] != nullptr) {
			sewerEnemy[1]->setPosition(28, 1);
			sewerEnemy[1]->setSpawnState(true);
		}
		if (sewerEnemy[2] != nullptr) {
			sewerEnemy[2]->setPosition(22, 0);
			sewerEnemy[2]->setSpawnState(true);
		}
		
		//human positions
		if (sewerEnemy[3] != nullptr) {
			sewerEnemy[3]->setSpawnState(false); //dont spawn this muthuman
			sewerEnemy[3] = nullptr;
		}
		if (sewerEnemy[4] != nullptr) {
			sewerEnemy[4]->setPosition(17, 4);
			sewerEnemy[4]->setSpawnState(true);
		}

		sewerMap.setpos(29, 0, 'C'); //chest
	}
	if (sewernum == 3) {
		//rat positions
		if (sewerEnemy[0] != nullptr) {
			sewerEnemy[0]->setPosition(12, 2);
			sewerEnemy[0]->setSpawnState(true);
		}
		if (sewerEnemy[1] != nullptr) {
			sewerEnemy[1]->setPosition(26, 4);
			sewerEnemy[1]->setSpawnState(true);
		}
		if (sewerEnemy[2] != nullptr) {
			sewerEnemy[2]->setPosition(20, 3);
			sewerEnemy[2]->setSpawnState(true);
		}

		//human position
		if (sewerEnemy[3] != nullptr) {
			sewerEnemy[3]->setPosition(5, 0);
			sewerEnemy[3]->setSpawnState(true);
		}
		if (sewerEnemy[4] != nullptr) {
			sewerEnemy[4]->setPosition(16, 1);
			sewerEnemy[4]->setSpawnState(true);
		}
		
		sewerMap.setpos(29, 0, 'C'); //chest
		sewerMap.setpos(15, 4, 'J'); //Jake
	}
}