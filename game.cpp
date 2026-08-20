#include "game.h"
#include <iostream>
#include <conio.h>
#include "enemy.h"

#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_RIGHT 77

#define KEY_I 105
#define KEY_J 106
#define KEY_K 107
#define KEY_L 108

//MAP STUFF
//when setting the world map dimensions, the numbers go by (number of rows/y spaces, number of cols/x spaces)
game::game() : worldMap(15, 20)
{
}

map& game::activeMap() {
    if (currentMap == Location::Sewer1) {
        return Sewer1.sewerMap;
    }

    //if currentMap isnt any of the others, return worldMap as a default
    return worldMap;
}

void game::createWorldMap() {
    //initiates every single map, fill with '?'
    worldMap.initmap();

    // World locations
    //set positions of POIs
    if (currentMap == Location::MainWorld) {
        worldMap.setpos(0, 7, 'B');//BUNKER
        worldMap.setpos(12, 8, 'T');//TOWN
        worldMap.setpos(18, 3, 'S');//SEWER


    }
}

void game::Run()
{
    bool gameRunning = true;
    createWorldMap();
    player.setPosition(1, 7);

    while (gameRunning) {

        map& current = activeMap();

        std::cout << "player position(x,y): " << player.getPosX() << ", " << player.getPosY() << std::endl;
        std::cout << "press arrow keys to move character" << std::endl;

        //print map when loop starts again
        current.printmap(player.getPosX(), player.getPosY());
        current.discovered(player.getPosX(), player.getPosY());

        if (currentMap == Location::Sewer1) {
            testEnemy.checkForPlayer(player);
            player.checkForEnemy(testEnemy);
        }

        int ch = _getch();

        if (ch == 0 || ch == 224) {
            ch = _getch();

            switch (ch) {
            case KEY_ARROW_UP:
                system("CLS");
                std::cout << "Up Arrow Pressed" << std::endl;
                player.move(0, -1);
                player.borderCol(0, -1, current.getDimensionCOL(), current.getDimensionROW());
                break;
            case KEY_ARROW_DOWN:
                system("CLS");
                std::cout << "Down Arrow Pressed" << std::endl;
                player.move(0, 1);
                player.borderCol(0, 1, current.getDimensionCOL(), current.getDimensionROW());
                break;
            case KEY_ARROW_LEFT:
                system("CLS");
                std::cout << "Left Arrow Pressed" << std::endl;
                player.move(-1, 0);
                player.borderCol(-1, 0, current.getDimensionCOL(), current.getDimensionROW());
                break;
            case KEY_ARROW_RIGHT:
                system("CLS");
                std::cout << "Right Arrow Pressed" << std::endl;
                player.move(1, 0);
                player.borderCol(1, 0, current.getDimensionCOL(), current.getDimensionROW());
            }
            //checks which POI player has entered/exited
            checkMapChange();
        }
        //test attack button
        else if (ch == 'a' || ch == 'A') {
            system("CLS");
            std::cout << "shot at enemy (test)" << std::endl;
            player.testAttack(testEnemy);
            continue;
        }
        else if (ch == 'q' || ch == 'Q') {
            system("CLS");
            gameRunning = false;
            break;
        }

        switch (ch) {
        case KEY_I:
            system("CLS");
            std::cout << "enemy moved up" << std::endl;
            break;
        case KEY_J:
            system("CLS");
            std::cout << "enemy moved left" << std::endl;
            break;
        case KEY_K:
            system("CLS");
            std::cout << "enemy moved down" << std::endl;
            break;
        case KEY_L:
            system("CLS");
            std::cout << "enemy moved right" << std::endl;
            break;
        }


    }
}

void game::checkMapChange() {
    //worldmap entry to POIs checking
    if (currentMap == Location::MainWorld) {
        if (player.getPosX() == 18 && player.getPosY() == 3) {
            //when player enters sewer1 from the worldmap, make current active map Sewer1.
            currentMap = Location::Sewer1;
            Sewer1.printSewerMap();

            //set entity positions
            player.setPosition(1, 2);
            testEnemy.setPosition(16, 1);

            std::cout << std::endl;
            std::cout << "Entered: SEWER ONE" << std::endl;
        }
    }
    //POI exit checking
    else if (currentMap == Location::Sewer1) {
        if (player.getPosX() == 0 && player.getPosY() == 2) {
            currentMap = Location::MainWorld;
            player.setPosition(17, 3);

            std::cout << std::endl;
            std::cout << "Entered: WORLD" << std::endl;

        }
    }
}
