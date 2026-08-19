#include "sewer.h"

sewer::sewer() : sewerMap(5, 30) {

}

void sewer::printSewerMap() {
	sewerMap.initmap();
	sewerMap.setpos(0, 3, 'X');
}