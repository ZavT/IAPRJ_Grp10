#include "sewer.h"
#include "mutRat.h"
#include "mutHuman.h"

sewer::sewer() : sewerMap(5, 30) {
	enemyCount = 2;

	testEnemy = new enemy * [enemyCount];

	//sewer 1
	testEnemy[0] = new mutRat();
	testEnemy[1] = new mutHuman();
}

sewer::~sewer() {
	for (int i = 0; i < enemyCount; i++) delete testEnemy[i];
	{
		delete[] testEnemy;
	}
}

void sewer::printSewerMap(int sewernum) {
	sewerMap.initPOImap();
	sewerMap.setpos(0, 2, 'X'); //entrance and exit

	if (sewernum == 1) {
		testEnemy[0]->setPosition(10, 1);
		testEnemy[1]->setPosition(20, 3);
	}
	if (sewernum == 2) {
		testEnemy[0]->setPosition(8, 2);
		testEnemy[1]->setPosition(25, 1);
	}
	if (sewernum == 3) {
		testEnemy[0]->setPosition(12, 2);
		testEnemy[1]->setPosition(22, 4);
	}
}