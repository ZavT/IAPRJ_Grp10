#include "sewer.h"

sewer::sewer() : sewerMap(5, 30) {

}

void sewer::printSewerMap(int sewernum) {
	sewerMap.initPOImap();
	sewerMap.setpos(0, 2, 'X'); //entrance and exit

	if (sewernum == 1) {
		sewerMap.setpos(10, 1, 'R'); // TESTING PLEASE DELETE AFTER
		sewerMap.setpos(20, 3, 'R');	// TESTING PLEASE DELETE AFTER
	}
	else if (sewernum == 2) {
		sewerMap.setpos(8, 2, 'R'); // TESTING PLEASE DELETE AFTER
		sewerMap.setpos(25, 1, 'R'); // TESTING PLEASE DELETE AFTER
	}
	else if (sewernum == 3) {
		sewerMap.setpos(12, 1, 'R'); // TESTING PLEASE DELETE AFTER
		sewerMap.setpos(22, 3, 'R');// TESTING PLEASE DELETE AFTER
	}

	//create enemies n stuff here
}