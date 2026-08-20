#include "game.h"
#include <iostream>
#include <conio.h>
#include "enemy.h"

#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_RIGHT 77
#define KEY_A 65

//MAP STUFF
//when setting the world map dimensions, the numbers go by (number of rows/y spaces, number of cols/x spaces)
game::game() : worldMap(15, 20)
{
}

void game::createWorldMap(){
    worldMap.initmap(); //every time this fuunction is called, clear the board and fill with '?'

    // World locations
    //set positions of POIs
    if (currentMap == Location::MainWorld) {
        worldMap.setpos(0, 7, 'B');//BUNKER
        worldMap.setpos(12, 8, 'T');//TOWN
        worldMap.setpos(18, 3, 'S');//SEWER

        player.setPosition(1, 7);
        testEnemy.setPosition(16, 10);
    }

    //sewer locations
    if (currentMap == Location::Sewer1) {
        player.setPosition(1, 3);
    }
}

void game::Run()
{
    bool gameRunning = true;
   
    createWorldMap();

    while (gameRunning) {

        std::cout << "player position(x,y): " << player.getPosX() << ", " << player.getPosY() << std::endl;
        std::cout << "press arrow keys to move character" << std::endl;

        //print map when loop starts again
        worldMap.printmap(player.getPosX(), player.getPosY());
        testEnemy.checkForPlayer(player);
        player.checkForEnemy(testEnemy);
        
        int ch = _getch();
        
        if (ch == 0 || ch == 224) {
            ch = _getch(); 

            worldMap.discovered(player.getPosX(), player.getPosY());

            switch (ch) {
            case KEY_ARROW_UP:
                system("CLS");
                std::cout << "Up Arrow Pressed" << std::endl;
                player.move(0, -1);
                player.borderCol(0, -1);
                break;
            case KEY_ARROW_DOWN:
                system("CLS");
                std::cout << "Down Arrow Pressed" << std::endl;
                player.move(0, 1);
                player.borderCol(0, 1);
                break;
            case KEY_ARROW_LEFT:
                system("CLS");
                std::cout << "Left Arrow Pressed" << std::endl;
                player.move(-1, 0);
                player.borderCol(-1, 0);
                break;
            case KEY_ARROW_RIGHT:
                system("CLS");
                std::cout << "Right Arrow Pressed" << std::endl;
                player.move(1, 0);
                player.borderCol(1, 0);
                break;

            default: 
                system("CLS");
                std::cout << "invalid input!" << std::endl;
                break;
            }
        }
        else if (ch == 'a' || ch == 'A') {
            system("CLS");
            std::cout << "shot at enemy (test)" << std::endl;
            player.testAttack(testEnemy);
        }
        else if (ch == 'q' || ch == 'Q') {
            system("CLS");
            gameRunning = false;
            break;
        }
        //inventory



        //PLAYER STUFF

    }
}
