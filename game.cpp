#include "game.h"
#include <iostream>
#include <conio.h>
#include "enemy.h"
#include "sewer.h"

#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_RIGHT 77

#define KEY_I 105
#define KEY_J 106
#define KEY_K 107
#define KEY_L 108
#define KEY_B 98
#define KEY_M 109

//MAP STUFF
//when setting the world map dimensions, the numbers go by (number of rows/y spaces, number of cols/x spaces)
game::game() : worldMap(15, 20)
{
    createWorldMap();
}

map& game::activeMap() {
    if (currentMap == Location::Bunker) {
        return Bunker.bunkerMap;
    }
    if (currentMap == Location::Sewer1) {
        return Sewer1.sewerMap;
    }
    if (currentMap == Location::Sewer2) {
        return Sewer2.sewerMap;
    }
    if (currentMap == Location::Sewer3) {
        return Sewer3.sewerMap;
    }
    if (currentMap == Location::Town) {
        return Town.townMap;
    }

    //if currentMap isnt any of the others, return worldMap as a default
    return worldMap;
}

void game::discoverpoi() //when within one tile range of the POI, reveal on worldMap
{
    if (player.getPosX() == 3 && player.getPosY() == 5 ||
        player.getPosX() == 2 && player.getPosY() == 5 ||
        player.getPosX() == 4 && player.getPosY() == 5 ||
        player.getPosX() == 3 && player.getPosY() == 4 ||
        player.getPosX() == 3 && player.getPosY() == 6) {
        worldMap.setpos(3, 5, 'S');//SEWER 1
    }
    if (player.getPosX() == 7 && player.getPosY() == 10 ||
        player.getPosX() == 6 && player.getPosY() == 10 ||
        player.getPosX() == 8 && player.getPosY() == 10 ||
        player.getPosX() == 7 && player.getPosY() == 9 ||
        player.getPosX() == 7 && player.getPosY() == 11) {
        worldMap.setpos(7, 10, 'S');//SEWER 2
    }
    if (player.getPosX() == 15 && player.getPosY() == 12 ||
        player.getPosX() == 16 && player.getPosY() == 12 ||
        player.getPosX() == 14 && player.getPosY() == 12 ||
        player.getPosX() == 15 && player.getPosY() == 11 ||
        player.getPosX() == 15 && player.getPosY() == 13) {
        worldMap.setpos(15, 12, 'S');// SEWER 3
    }
}

int enemyX[2];
int enemyY[2];

void game::createWorldMap() {
    //initiates every single map, fill with '?'
    worldMap.initmap();

    // World locations
    //set positions of POIs
    if (currentMap == Location::MainWorld) {
        worldMap.setpos(0, 7, 'B');//BUNKER
        worldMap.setpos(12, 8, 'T');//TOWN
    }
}



void game::Run()
{
    bool gameRunning = true;

    // Start of intro
    {
        std::cout << "____________________________________________________________________" << std::endl;
        std::cout << " ___   @@@@@@@@                   @@" << std::endl;
        std::cout << "/ #|  __ @@@@@                   @@@@       @@@@" << std::endl;
        std::cout << "   |  ||_/|           @@@@@@              @@@@@@@            @@@@@" << std::endl;
        std::cout << "#  |__|__ |             @@@@                                @@@@@" << std::endl;
        std::cout << "   ||  #| |" << std::endl;
        std::cout << "  #||   | |" << std::endl;
        std::cout << "   | #  | |______" << std::endl;
        std::cout << " # ||   | |  #  |                            _______  _______" << std::endl;
        std::cout << "   |/  #| |#   /   O      O      O      O    / __ |   / __ |" << std::endl;
        std::cout << "___||___|_|____|___|______|______|______|____|_||_|___|_||_|________" << std::endl;
        std::cout << std::endl;
        std::cout << "Apocalypse" << std::endl;
        std::cout << std::endl;
        std::cout << "Press Enter to continue...";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("CLS");
    }

    {
        std::cout << "Enter your name: ";
        std::string name;
        std::cin >> name;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        player.setPlayerName(name);
        std::cout << "Your name is " << player.getPlayerName() << std::endl;
        std::cout << std::endl;
        std::cout << "Press Enter to continue...";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("CLS");
    }
    // End of intro
    
    //createWorldMap();
    //player.setPosition(1, 7);

    Bunker.printbunkerMap();
    player.setPosition(1, 1);
    currentMap = Location::Bunker;

    while (gameRunning) {

        map& current = activeMap();

        std::cout << "player position(x,y): " << player.getPosX() << ", " << player.getPosY() << std::endl;
        std::cout << "press arrow keys to move character" << std::endl;

        //print map when loop starts again
        Sewer1.testEnemy[0].enemyBehaviour(player);
        Sewer1.testEnemy[0].checkForPlayer(player);
        current.printmap(player.getPosX(), player.getPosY(), Sewer1.testEnemy[0].getPosX(), Sewer1.testEnemy[0].getPosY());
        
        current.discovered(player.getPosX(), player.getPosY());

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
            //check if player has discovered a poi after moving
            discoverpoi();
            checkMapChange();
        }

        //check if quit game
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
        case KEY_B:
            system("CLS");       //hides the world map
            bag.inventoryMenu(); //opens inventory until ESC is pressed.
            system("CLS");       //clears inventory text, let map redraw
            break;
        case KEY_M:
            system("CLS");       
            settings.menuOpen(); 
            system("CLS");      
        }


    }
}

void game::checkMapChange() {
    //worldmap entry to POIs checking
    if (currentMap == Location::MainWorld) {
        if (player.getPosX() == 3 && player.getPosY() == 5) {
            //when player enters sewer1 from the worldmap, make current active map Sewer1.
            currentMap = Location::Sewer1;
            Sewer1.printSewerMap(1);
            //set entity positions
            player.setPosition(1, 2);
            std::cout << std::endl;
            std::cout << "Entered: SEWER ONE" << std::endl;
        }

        else if (player.getPosX() == 7 && player.getPosY() == 10) {
            //when player enters sewer2 from the worldmap, make current active map Sewer2.
            currentMap = Location::Sewer2;
            Sewer2.printSewerMap(2);
            //set entity positions
            player.setPosition(1, 2);
            std::cout << std::endl;
            std::cout << "Entered: SEWER TWO" << std::endl;
        }

        else if (player.getPosX() == 15 && player.getPosY() == 12) {
            //when player enters sewer3 from the worldmap, make current active map Sewer3.
            currentMap = Location::Sewer3;
            Sewer3.printSewerMap(3);
            //set entity positions
            player.setPosition(1, 2);
            std::cout << std::endl;
            std::cout << "Entered: SEWER THREE" << std::endl;
        }

        else if (player.getPosX() == 0 && player.getPosY() == 7) {
            //when player enters bunker from the worldmap, make current active map bunker.
            currentMap = Location::Bunker;
            Bunker.printbunkerMap();
            //set entity positions
            player.setPosition(1, 4 );
            std::cout << std::endl;
            std::cout << "Entered: BUNKER" << std::endl;
        }

        else if (player.getPosX() == 12 && player.getPosY() == 8) {
            //when player enters town from the worldmap, make current active map town.
            currentMap = Location::Town;
            Town.printtownMap();
            //set entity positions
            player.setPosition(1, 7);
            std::cout << std::endl;
            std::cout << "Entered: TOWN" << std::endl;
        }
        
    }

    //POI exit checking
        else if (currentMap == Location::Sewer1) {
            if (player.getPosX() == 0 && player.getPosY() == 2) {
                currentMap = Location::MainWorld;
                player.setPosition(2, 5);
                std::cout << std::endl;
                std::cout << "Entered: WORLD" << std::endl;

            }
        }
        else if (currentMap == Location::Sewer2) {
            if (player.getPosX() == 0 && player.getPosY() == 2) {
                currentMap = Location::MainWorld;
                player.setPosition(6, 10);
                std::cout << std::endl;
                std::cout << "Entered: WORLD" << std::endl;

            }
        }
        else if (currentMap == Location::Sewer3) {
            if (player.getPosX() == 0 && player.getPosY() == 2) {
                currentMap = Location::MainWorld;
                player.setPosition(14, 12);
                std::cout << std::endl;
                std::cout << "Entered: WORLD" << std::endl;
            }
        }

        else if (currentMap == Location::Bunker) {
            if (player.getPosX() == 0 && player.getPosY() == 4) {
                currentMap = Location::MainWorld;
                player.setPosition(1, 7);
                std::cout << std::endl;
                std::cout << "Entered: WORLD" << std::endl;
            }
        }

        else if (currentMap == Location::Town) {
        if (player.getPosX() == 0 && player.getPosY() == 7) {
            currentMap = Location::MainWorld;
            player.setPosition(11, 8);
            std::cout << std::endl;
            std::cout << "Entered: WORLD" << std::endl;
        }
    }
}

