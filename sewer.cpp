#include "sewer.h"

sewer::sewer() : sewerMap(5, 30) {
	//for (int i = 0; i < 3; i++) {
	//	sewerActive[i] = false;
	//}
}

void sewer::printSewerMap(int sewernum) {
	sewerMap.initPOImap();
	sewerMap.setpos(0, 2, 'X'); //entrance and exit

	//delete below code when enemies are properly added
	if (sewernum == 1) {
		sewerMap.setpos(10, 1, 'R'); // TESTING PLEASE DELETE AFTER
		sewerMap.setpos(20, 3, 'R');	// TESTING PLEASE DELETE AFTER
		testEnemy[0].setPosition(10, 1);
	//	testEnemy[1].setPosition(20, 3);
	}
	else if (sewernum == 2) {
		sewerMap.setpos(8, 2, 'R'); // TESTING PLEASE DELETE AFTER
		sewerMap.setpos(25, 1, 'R'); // TESTING PLEASE DELETE AFTER
		testEnemy[0].setPosition(8, 2);
		testEnemy[1].setPosition(25, 1);
	}
	else if (sewernum == 3) {
		sewerMap.setpos(12, 1, 'R'); // TESTING PLEASE DELETE AFTER
		sewerMap.setpos(22, 3, 'R');// TESTING PLEASE DELETE AFTER
		testEnemy[0].setPosition(12, 2);
		testEnemy[1].setPosition(22, 4);
	}

	//create enemies n stuff here
}