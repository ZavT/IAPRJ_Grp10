#include "sewer.h"

sewer::sewer() : sewerMap(5, 30) {

}

void sewer::printSewerMap() {
	sewerMap.initPOImap();
	sewerMap.setpos(0, 2, 'X');

	//create enemies n stuff here
}