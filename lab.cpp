#include "lab.h"
#include "mutRat.h"
#include "mutHuman.h"
#include "boss.h"

lab::lab() : labMap (9,20){
	labEnemyCount = 5;

	labEnemy = new enemy * [labEnemyCount];

	labEnemy[0] = new mutRat(0, 0, 0);
	labEnemy[1] = new mutRat(0, 0, 1);
	labEnemy[2] = new mutHuman(0, 0, 2);
	labEnemy[3] = new mutHuman(0, 0, 3);
	labEnemy[4] = new mutHuman(0, 0, 4);
}
lab::~lab() {

}

void lab::printlabMap() {
	labMap.initPOImap();
	labMap.setpos(0, 4, 'X');

	if (labEnemy[0] != nullptr) {
		labEnemy[0]->setPosition(6,0);
		labEnemy[0]->setSpawnState(true);
	}
	if (labEnemy[1] != nullptr) {
		labEnemy[1]->setPosition(14,0);
		labEnemy[1]->setSpawnState(true);
	}
	if (labEnemy[2] != nullptr) {
		labEnemy[2]->setPosition(6, 8);
		labEnemy[2]->setSpawnState(true);
	}
	if (labEnemy[3] != nullptr) {
		labEnemy[3]->setPosition(14,8);
		labEnemy[3]->setSpawnState(true);
	}
	if (labEnemy[4] != nullptr) {
		labEnemy[4]->setPosition(10,4);
		labEnemy[4]->setSpawnState(true);
	}
}

void lab::summonBoss() {
	TheScientist = new enemy * [1];

	TheScientist[0] = new boss(0, 0, 1);
}
