#include "map.h"
#define ESC "\033"
#define RESET   ESC "[0m"
#define BLUE    ESC "[34m"
#define GREEN    ESC "[92m"
#define CYAN    ESC "[96m"
#define RED    ESC "[91m"
#define BRIGHT_MAGENTA ESC "[95m"
#define BRIGHT_YELLOW  ESC "[93m"
#define BG_RED     ESC "[41m"
#define BOLD      ESC "[1m"
#include <iostream>

//testing github desktop
map::map() {

}
map::map(int r, int c){
	rows = r; //y value
	cols = c; //x value
}

int map::getDimensionROW() {
	return rows;
}
int map::getDimensionCOL() {
	return cols;
}

void map::initmap(){
	for (int i = 0; i < rows; i++) {
		for (int x = 0; x < cols; x++) {
			maps[i][x] = '?';
		}
	}
}

void map::initPOImap() {
	for (int i = 0; i < rows; i++) {
		for (int x = 0; x < cols; x++) {
			maps[i][x] = ' ';
		}
	}
}

void map::setpos(int setX, int setY, char symbol){
	maps[setY][setX] = symbol;
}

void map::printmap(int playerX, int playerY, int enemyX, int enemyY) {
	std::cout << "           ";
	for (int x = 0; x < cols; x++) {
		std::cout << "+ ";
	}
	std::cout << std::endl;
	for (int i = 0; i < rows; i++) {
		std::cout << "         + "; // spaces before the row & side border
		for (int x = 0; x < cols; x++) {
			if (x == playerX && i == playerY) {
				std::cout << BOLD << GREEN << 'P' << RESET << " ";
				continue;
			}


				if (x == enemyX && i == enemyY) {
					std::cout << BOLD << RED << 'E' << RESET << " ";
					continue;
				}
			
			//give color to given symbols
			if (maps[i][x] == 'B') {
				std::cout << BOLD << CYAN << maps[i][x] << RESET << " ";
			}
			else if (maps[i][x] == 'S') {
				std::cout << BOLD << RED << maps[i][x] << RESET << " ";
			}
			else if (maps[i][x] == 'T') {
				std::cout << BOLD << BLUE << maps[i][x] << RESET << " ";
			}
			else if (maps[i][x] == 'X') {
				std::cout << BOLD << RED << maps[i][x] << RESET << " ";
			}
			else if (maps[i][x] == 'A') {
				std::cout << BOLD << BRIGHT_MAGENTA << maps[i][x] << RESET << " ";
			}
			else if (maps[i][x] == 'W') {
				std::cout << BOLD << BRIGHT_YELLOW << maps[i][x] << RESET << " ";
			}
			else if (maps[i][x] == 'L') {
				std::cout << BOLD << BG_RED << maps[i][x] << RESET << " ";
			}

			//if its not any of the above symbols then print it out normally and add spacing
			else {
				std::cout << maps[i][x] << " "; //adds space between dots
			}

		}
		//after each row is finished printing, print the right side of the border, then go next line
		std::cout << "+" << std::endl;
	}
	std::cout << "           ";
	for (int x = 0; x < cols; x++) {
		std::cout << "+ ";
	}
	std::cout << std::endl;
}

//note: this is supposed to turn '?' grid spaces into ' ' after the player has been on the tile before.
//needs some kinda fixing because using ts function will leave a trail of the player behind which is not good
void map::discovered(int discX, int discY) {
	if (maps[discY][discX] == '?') {
		maps[discY][discX] = ' ';
	}
}
	