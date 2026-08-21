#pragma once
class map
{
private:
	int rows;
	int cols;
	char maps[30][30];

public: 
	map();
	map(int r, int c);

	void initmap();
	void initPOImap();
	
	int getDimensionROW();
	int getDimensionCOL();

	void printmap(int playerX, int playerY, int* enemyX = nullptr, int* enemyY = nullptr, char* enemySymbol = nullptr, int enemyCount = 0);
	void renderEnemies(int enemyX, int enemyY);
	void setpos(int row, int col, char symbol);  //set pos only for map items
	void discovered(int discX, int discY);
};

