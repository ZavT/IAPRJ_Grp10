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
		//for monsters that you dont wanna spawn, set them to 9999999, 9999999
		//-----------------------------------

		//rat positions
		sewerEnemy[0]->setPosition(10, 0);
		sewerEnemy[1]->setPosition(14, 2);
		sewerEnemy[2]->setPosition(9999999, 99999999);

		//human positions
		sewerEnemy[3]->setPosition(8, 4);
		sewerEnemy[4]->setPosition(99999999, 999999999);
	}
	if (sewernum == 2) {
		//rat positions
		sewerEnemy[0]->setPosition(8, 2);
		sewerEnemy[1]->setPosition(25, 1);
		sewerEnemy[2]->setPosition(22, 0);
		
		//human positions
		sewerEnemy[3]->setPosition(99999999999, 99999999);
		sewerEnemy[4]->setPosition(17, 4);
	}
	if (sewernum == 3) {
		//rat positions
		sewerEnemy[0]->setPosition(12, 2);
		sewerEnemy[1]->setPosition(22, 4);
		sewerEnemy[2]->setPosition(20, 3);

		//human position
		sewerEnemy[3]->setPosition(5, 0);
		sewerEnemy[4]->setPosition(16, 1);
	}
}