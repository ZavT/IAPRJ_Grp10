#include "bunker.h"
#include "mutRat.h"

bunker::bunker() : bunkerMap(9, 9)
{
	BunkerEnemyCount = 2;

	bunkerEnemy = new enemy * [BunkerEnemyCount];

	bunkerEnemy[0] = new mutRat(0, 0, 0);
	bunkerEnemy[1] = new mutRat(0, 0, 1);
}

bunker::~bunker() {
	for (int i = 0; i < BunkerEnemyCount; i++) delete bunkerEnemy[i];
	{
		delete[] bunkerEnemy;
	}
}

void bunker::printbunkerMap(){
	bunkerMap.initPOImap();
	bunkerMap.setpos(8, 4, 'X'); //exit for bunker
	bunkerMap.setpos(8,5 , '-');
	bunkerMap.setpos(8, 3, '-');

	bunkerEnemy[0]->setPosition(7, 0);
	bunkerEnemy[1]->setPosition(3, 7);

	bunkerEnemy[0]->setSpawnState(true);
	bunkerEnemy[1]->setSpawnState(true);
}
