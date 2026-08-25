#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <limits> //dialogue
#include "game.h"
#include "enemy.h"
#include "player.h"
#include "inventory.h"
#include "sewer.h"
#include "inspect.h"
#include "weaponsmith.h"
#include "npc.h"
#include "DialogueTree.h"

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
    if (currentMap == Location::Lab) {
        return Lab.labMap;
    }

    //if currentMap isnt any of the others, return worldMap as a default
    return worldMap;
}

void game::discoverpoi() //when within one tile range of the POI, reveal on worldMap
{
    if (currentMap == Location::MainWorld) {
        if (player.getPosX() >= 2 && player.getPosX() <= 4 && //between x 2-4
            player.getPosY() >= 4 && player.getPosY() <= 6) {//between y 4-6
            worldMap.setpos(3, 5, 'S');//SEWER 1
        }
        if (player.getPosX() >= 6 && player.getPosX() <= 8 && //between x 6-8
            player.getPosY() >= 9 && player.getPosY() <= 11) {//between y 9-11
            worldMap.setpos(7, 10, 'S');//SEWER 2
        }
        if (player.getPosX() >= 14 && player.getPosX() <= 16 && //between x 14-16
            player.getPosY() >= 11 && player.getPosY() <= 13) {//between y 11-13
            worldMap.setpos(15, 12, 'S');// SEWER 3
        }
        if (player.getPosX() >= 18 && player.getPosX() <= 20 && //between x 18-20
            player.getPosY() >= 6 && player.getPosY() <= 8) {//between y 6-8
            worldMap.setpos(19, 7, 'L');// LAB
        }
    }
}

void game::battlesequence(enemy*& currentEnemy)
{
    bool inbattle = true;
    char enemysymbol = currentEnemy->getSymbol();

    std::string ratASCII =
        "\n       _..----.._    _"
        "\n     .'  .--.    '-.(0)_"
        "\n'-.__.-''''-:  ,  _  ' '-."
        "\n             ''''' '''''''\n";

    std::string muthumanASCII = R"( 
          _,-""-._
        ,"        ".
       /    ,-,  ,"\
      "    /   \ | o|
      \    `--"  `-',
       `,   _.--'`'--`
         `--`---'             
           ,' '      
         ./ ,  `,    
         / /     \
        (_)))_ _,"
           _))))_,
  --------(_,-._)))-------------------------------
)";

    while (inbattle && player.getHealthPoints() > 0 && currentEnemy->getHealthPoints() > 0) { // while player and enemy is not dead
        //player turn
        player.setPlayerActionPoints(player.getPlayerAgility());
        bool playerturn = true;

        //active weapon
        weapon activeWep = bag.getEquippedWeapon();
        int requiredAP = activeWep.getItemAPcost();
        
        while (playerturn && player.getPlayerActionPoints() > 0 && currentEnemy->getHealthPoints() > 0) {// while player ap is not 0 and enemy is not dead
            system("CLS");
            if (enemysymbol == 'H') {
                std::cout << muthumanASCII << std::endl;
            }
            else if (enemysymbol == 'R') {
                std::cout << ratASCII << std::endl;
            }
            std::cout << "\t=== BATTLE ===\n\n";
            std::cout << "\tPlayer HP: " << player.getPlayerHealthPoints() << " / " << player.getPlayerMaxHealthPoints() << "  |  AP: " << player.getPlayerActionPoints() << "  |  Active Weapon: " << activeWep.getItemName() <<"\n";
            std::cout << "\tEnemy HP:  " << currentEnemy->getHealthPoints() << "\n\n";

            std::cout << "\t[1] Attack (" << requiredAP << " AP)\n";
            std::cout << "\t[2] Item (Equip/Use) (1 AP)\n";
            std::cout << "\t[3] Skip Turn\n";
            std::cout << "\t[4] Run Away\n";
            int act = _getch(); //input

            if (act == '1') {
                int chance = activeWep.getweaponacc();
                int randchance = rand() % 100;
                if (player.getPlayerActionPoints() >= requiredAP) {
                    if (randchance < chance) { // if the randomise chance is inside the weapon accuracy chance like for example 60 < 70 it hits
                        int dmg = activeWep.getweapondmg(player);
                        currentEnemy->setHealthPoints(currentEnemy->getHealthPoints() - dmg);
                        player.setPlayerActionPoints(player.getPlayerActionPoints() - requiredAP);
                        std::cout << "\n\tYou dealt " << dmg << " damage with your "
                            << activeWep.getItemName() << "! Press any key...";
                        (void)_getch();
                    }
                    else {
                        std::cout << "\n\tYou missed. Press any key...";
                        (void)_getch();
                    }
                }

            }
            else if (act == '2') {
                player.setPlayerActionPoints(player.getPlayerActionPoints() - 1); 
                bag.inventoryMenu(player);
            }
            else if (act == '3') {
                playerturn = false; // skip turn
            }
            else if (act == '4') {
                std::cout << "\n\tGot away safely! Press any key...";
                (void)_getch();
                inbattle = false; // run
                currentEnemy->setEscapeState(true); //player just escaped, so set escape state to true.
                system("CLS");
                break;
            }
        }

        //if player ran away or enemy died during the ap loop exit battle
        if (!inbattle || currentEnemy->getHealthPoints() <= 0)
        break;

        // enemy turn
        if (enemysymbol == 'R') { //if enemy is rat
            system("CLS");
            std::cout << ratASCII << "\n";
            std::cout << "\t Enemy Turn!\n\n";

            int dodge = player.getPlayerAgilityFinal();
            int randhit = rand() % 100;
            int dodgebuff = dodge;
            if (activeWep.getweaponismelee() == false) {
                dodgebuff += 30;
            }

            if (randhit < dodgebuff) {
                std::cout << "\tYou dodged the enemy's attack\n";
                std::cout << "\tPress any key to start your next turn...";
                (void)_getch();
            }
            else {
                if (rand() % 2 == 0) { // BITE //if 0 do bite
                    int enemyDmg = 10;
                    player.setPlayerHealthPoints(player.getPlayerHealthPoints() - enemyDmg); // enemy attack hp deduct
                    std::cout << "\tThe Mutant Rat bites you for " << enemyDmg << " damage!\n";
                    std::cout << "\tPress any key to start your next turn...";
                    (void)_getch();
                }
                else { // RAZOR TAIL
                    int enemyDmg = (rand() % 6) + 10; // 10-15 dmg
                    player.setPlayerHealthPoints(player.getPlayerHealthPoints() - enemyDmg); // enemy attack hp deduct
                    std::cout << "\tThe Mutant Rat swings its razor tail for " << enemyDmg << " damage!\n";
                    std::cout << "\tPress any key to start your next turn...";
                    (void)_getch();
                }
            }
        }

        if (enemysymbol == 'H') { // if enemy is mutated human
            system("CLS");
            std::cout << muthumanASCII << "\n";
            std::cout << "\t Enemy Turn!\n\n";

            int dodge = player.getPlayerAgilityFinal();
            int randhit = rand() % 100;
            int dodgebuff = dodge;

            if (activeWep.getweaponismelee() == false) {
                 dodgebuff += 30;
            }

            if (randhit < dodgebuff) {
                std::cout << "\tYou dodged the enemy's attack\n";
                std::cout << "\tPress any key to start your next turn...";
                (void)_getch();
            }
            else {
                if (rand() % 2 == 0) {
                    int enemyDmg = 20; //mutated slash
                    player.setPlayerHealthPoints(player.getPlayerHealthPoints() - enemyDmg); // enemy attack hp deduct
                    std::cout << "\tThe Mutated human slashes you for " << enemyDmg << " damage!\n";
                    std::cout << "\tPress any key to start your next turn...";
                    (void)_getch();
                }
                else {
                    int enemyDmg = 14; //punch
                    player.setPlayerHealthPoints(player.getPlayerHealthPoints() - enemyDmg); // enemy attack hp deduct
                    std::cout << "\tThe Mutated human punched you for " << enemyDmg << " damage!\n";
                    std::cout << "\tPress any key to start your next turn...";
                    (void)_getch();
                }
            }
        }
    }

    if (currentEnemy->getHealthPoints() <= 0) { // enemy dies
        int expgained;
        if (enemysymbol == 'R') {
            expgained = 10;
        }
        else if (enemysymbol == 'H') {
            expgained = 20;
        }
        player.gainExp(expgained);
        std::cout << "\n\tEnemy defeated! You gained "<< expgained <<" exp. Press any key...";

        delete currentEnemy;
        currentEnemy = nullptr;
        (void)_getch();
        inbattle = false;
        system("CLS");
    }
}

void game::createWorldMap() {
    //initiates every single map, fill with '?'
    worldMap.initmap();

    // World locations
    //set positions of POIs
    if (currentMap == Location::MainWorld) {
        worldMap.setpos(0, 7, 'B');//BUNKER
        worldMap.setpos(12, 8, 'T');//TOWN
        //worldMap.setpos(19, 7, 'L'); // LAB
    }
}

void game::timePassMinutes(int m) {
    int janDays = 28;

    if (minute < 10 && hour < 10)
        std::cout << day << '/' << month << '/' << year << ' ' << '0' << hour << '0' << minute << std::endl;
    else if (minute < 10)
        std::cout << day << '/' << month << '/' << year << ' ' << hour << '0' << minute << std::endl;
    else if (hour < 10)
        std::cout << day << '/' << month << '/' << year << ' ' << '0' << hour << minute << std::endl;
    else
        std::cout << day << '/' << month << '/' << year << ' ' << hour << minute << std::endl;

    minute = minute + m;

    if (minute >= 60) {
        while (minute >= 60) {
            minute = minute - 60;
            hour = hour + 1;
        }

        if (hour >= 24) {
            while (hour >= 24) {
                hour = hour - 24;
                day = day + 1;
            }

            if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
                janDays = 29;
            }
            else {
                janDays = 28;
            }

            if ((month == 1 && day >= 32) || (month == 2 && day >= janDays + 1) || (month == 3 && day >= 32) || (month == 4 && day >= 31) ||
                (month == 5 && day >= 32) || (month == 6 && day >= 31) || (month == 7 && day >= 32) || (month == 8 && day >= 32) ||
                (month == 9 && day >= 31) || (month == 10 && day >= 32) || (month == 11 && day >= 31) || (month == 12 && day >= 32)) {

                while ((month == 1 && day >= 32) || (month == 2 && day >= janDays + 1) || (month == 3 && day >= 32) || (month == 4 && day >= 31) ||
                    (month == 5 && day >= 32) || (month == 6 && day >= 31) || (month == 7 && day >= 32) || (month == 8 && day >= 32) ||
                    (month == 9 && day >= 31) || (month == 10 && day >= 32) || (month == 11 && day >= 31) || (month == 12 && day >= 32)) {

                    switch (month) {
                    case 1:
                        day = day - 31;
                        break;
                    case 2:
                        day = day - janDays;
                        break;
                    case 3:
                        day = day - 31;
                        break;
                    case 4:
                        day = day - 30;
                        break;
                    case 5:
                        day = day - 31;
                        break;
                    case 6:
                        day = day - 30;
                        break;
                    case 7:
                        day = day - 31;
                        break;
                    case 8:
                        day = day - 31;
                        break;
                    case 9:
                        day = day - 30;
                        break;
                    case 10:
                        day = day - 31;
                        break;
                    case 11:
                        day = day - 30;
                        break;
                    case 12:
                        day = day - 31;
                        break;
                    }
                    month = month + 1;
                    if (month >= 13) {
                        while (month >= 13) {
                            month = month - 12;
                            year = year + 1;
                        }
                    }
                }
            }
        }
    }
}

void game::Intro()
{
    player.setStatPoints(5);
    bool characterCreation = true;
    std::string ccInput;
    std::string tempName;

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
    std::cout << "<APOCALYPSE>" << std::endl;
    std::cout << std::endl;
    std::cout << "Press Enter to continue...";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    system("CLS");



    std::cout << "CONTEXT" << std::endl;
    std::cout << std::endl;
    std::cout << "You are a survivor of a war. During the initial outbreak of the war, you quickly took\n"
              << "shelter in a nearby bunker for safety. No one else made it. Overtime, supplies started\n"
              << "to run low. With supplies running low, you had no choice but to leave the bunker to\n"
              << "avoid dying of starvation. This is where your story begins." << std::endl;
    std::cout << std::endl;
    std::cout << "Press Enter to start creating your character";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    system("CLS");



    std::cout << "Enter your name: ";
    std::cin >> tempName;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    player.setPlayerName(tempName);
    std::cout << "Your name is " << player.getPlayerName() << "." << std::endl;
    std::cout << std::endl;
    std::cout << "Press Enter to continue...";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    system("CLS");


    while (characterCreation)
    {
        std::cout << "STAT POINTS: " << player.getStatPoints() << std::endl;
        std::cout << std::endl;
        std::cout << "Name: " << player.getPlayerName() << std::endl;
        std::cout << std::endl;
        std::cout << "Strength: " << player.getPlayerStrength() << std::endl;
        std::cout << "Agility: " << player.getPlayerAgility() << std::endl;
        std::cout << "Luck: " << player.getPlayerLuck() << std::endl;
        std::cout << "Endurance: " << player.getPlayerEndurance() << std::endl;
        std::cout << "Intelligence: " << player.getPlayerIntelligence() << std::endl;
        std::cout << "Inputs: S+, S-, A+, A-, L+, L-, E+, E-, I+, I-\nEnter 'Ready' when ready." << std::endl;
        std::cout << "Can't have stats lower than 2 and you have to use all 5 stat points." << std::endl;
        std::cin >> ccInput;
        if (ccInput == "S+" && player.getStatPoints() > 0) {
            player.setPlayerStrength(player.getPlayerStrength() + 1);
            player.setStatPoints(player.getStatPoints() - 1);
            system("CLS");
        }
        else if (ccInput == "S-" && player.getPlayerStrength() > 2) {
            player.setPlayerStrength(player.getPlayerStrength() - 1);
            player.setStatPoints(player.getStatPoints() + 1);
            system("CLS");
        }
        else if (ccInput == "A+" && player.getStatPoints() > 0) {
            player.setPlayerAgility(player.getPlayerAgility() + 1);
            player.setStatPoints(player.getStatPoints() - 1);
            system("CLS");
        }
        else if (ccInput == "A-" && player.getPlayerAgility() > 2) {
            player.setPlayerAgility(player.getPlayerAgility() - 1);
            player.setStatPoints(player.getStatPoints() + 1);
            system("CLS");
        }
        else if (ccInput == "L+" && player.getStatPoints() > 0) {
            player.setPlayerLuck(player.getPlayerLuck() + 1);
            player.setStatPoints(player.getStatPoints() - 1);
            system("CLS");
        }
        else if (ccInput == "L-" && player.getPlayerLuck() > 2) {
            player.setPlayerLuck(player.getPlayerLuck() - 1);
            player.setStatPoints(player.getStatPoints() + 1);
            system("CLS");
        }
        else if (ccInput == "E+" && player.getStatPoints() > 0) {
            player.setPlayerEndurance(player.getPlayerEndurance() + 1);
            player.setStatPoints(player.getStatPoints() - 1);
            system("CLS");
        }
        else if (ccInput == "E-" && player.getPlayerEndurance() > 2) {
            player.setPlayerEndurance(player.getPlayerEndurance() - 1);
            player.setStatPoints(player.getStatPoints() + 1);
            system("CLS");
        }
        else if (ccInput == "I+" && player.getStatPoints() > 0) {
            player.setPlayerIntelligence(player.getPlayerIntelligence() + 1);
            player.setStatPoints(player.getStatPoints() - 1);
            system("CLS");
        }
        else if (ccInput == "I-" && player.getPlayerIntelligence() > 2) {
            player.setPlayerIntelligence(player.getPlayerIntelligence() - 1);
            player.setStatPoints(player.getStatPoints() + 1);
            system("CLS");
        }
        else if ((ccInput == "Ready" || ccInput == "ready") && player.getStatPoints() != 0) { 
            system("CLS");
            std::cout << "Use up remaining stat points" << std::endl;
            std::cout << std::endl;
        }
        else if ((ccInput == "Ready" || ccInput == "ready") && player.getStatPoints() == 0) {
            characterCreation = false;
            system("CLS");
        }

        else {
            system("CLS");
            std::cout << "Invalid Input" << std::endl;
            std::cout << std::endl;
        }
    }
}

void game::randomEncounterChance(int chance) {
    int randomNum = (rand() % 100) + 1;

    if (randomNum <= chance) {
        // random encounter code
    }
}

void game::Run()
{
    bool gameRunning = true;
    //Intro(); //comment out to skip intro

    Bunker.printbunkerMap();
    player.setPosition(1, 1);
    currentMap = Location::Bunker;

    while (gameRunning) {

        map& current = activeMap();

        //define the number of enemies in total
        int enemyX[6];
        int enemyY[6];
        char enemySymbol[6];
        int enemyCount = 0;

        //every start of the loop, change the time depending on current location
        if (currentMap == Location::MainWorld) {
            int randomTimeOW = (rand() % 9) + 52;
            timePassMinutes(randomTimeOW);
        }
        else {
            int randomTimePOI = (rand() % 2) + 1;
            timePassMinutes(randomTimePOI);
        }
                
        if (currentMap == Location::Sewer1) {
            for (int e = 0; e < Sewer1.enemyCount; e++) {

                if (Sewer1.sewerEnemy[e] == nullptr || !Sewer1.sewerEnemy[e]->isSpawned()) {
                    continue;
                }
    
                enemyX[enemyCount] = Sewer1.sewerEnemy[e]->getPosX();
                enemyY[enemyCount] = Sewer1.sewerEnemy[e]->getPosY();
                enemySymbol[enemyCount] = Sewer1.sewerEnemy[e]->getSymbol();
                
                if (!Sewer1.sewerEnemy[e]->getEscapeState()) {
                    Sewer1.sewerEnemy[e]->enemyBehaviour(player, Sewer1.sewerMap, Sewer1.sewerEnemy, Sewer1.enemyCount, e);
                }
                Sewer1.sewerEnemy[e]->checkForPlayer(player);
                if (Sewer1.sewerEnemy[e]->getHealthPoints() > 0) {
                    if (Sewer1.sewerEnemy[e]->getEscapeState()) {
                        Sewer1.sewerEnemy[e]->setEscapeState(false);
                    }
                    else if (!player.getBattleState() && player.checkforbattle(*Sewer1.sewerEnemy[e])) {  //if enemy is close to the player trigger battle sequence for that enemy
                        player.setBattleState(true);
                        battlesequence(Sewer1.sewerEnemy[e]);
                        player.setBattleState(false);
                    }
                }
                enemyCount++;
            }
        } else if (currentMap == Location::Sewer2) {
            for (int e = 0; e < Sewer2.enemyCount; e++) {

                if (Sewer2.sewerEnemy[e] == nullptr || !Sewer2.sewerEnemy[e]->isSpawned()) {
                    continue;
                }

                enemyX[enemyCount] = Sewer2.sewerEnemy[e]->getPosX();
                enemyY[enemyCount] = Sewer2.sewerEnemy[e]->getPosY();
                enemySymbol[enemyCount] = Sewer2.sewerEnemy[e]->getSymbol();

                if (!Sewer2.sewerEnemy[e]->getEscapeState()) {
                    Sewer2.sewerEnemy[e]->enemyBehaviour(player, Sewer2.sewerMap, Sewer2.sewerEnemy, Sewer2.enemyCount, e);
                }
                Sewer2.sewerEnemy[e]->checkForPlayer(player);
                if (Sewer2.sewerEnemy[e]->getHealthPoints() > 0) {
                    if (Sewer2.sewerEnemy[e]->getEscapeState()) {
                        Sewer2.sewerEnemy[e]->setEscapeState(false);
                    }
                    else if (!player.getBattleState() && player.checkforbattle(*Sewer2.sewerEnemy[e])) { //if enemy is close to the player trigger battle sequence for that enemy
                        player.setBattleState(true);
                        battlesequence(Sewer2.sewerEnemy[e]);
                        player.setBattleState(false);
                        
                    }
                }
                enemyCount++;
            }
        } else if (currentMap == Location::Sewer3) {
            for (int e = 0; e < Sewer3.enemyCount; e++) {

                if (Sewer3.sewerEnemy[e] == nullptr || !Sewer3.sewerEnemy[e]->isSpawned()) {
                    continue;   
                }
            
                enemyX[enemyCount] = Sewer3.sewerEnemy[e]->getPosX();
                enemyY[enemyCount] = Sewer3.sewerEnemy[e]->getPosY();
                enemySymbol[enemyCount] = Sewer3.sewerEnemy[e]->getSymbol();

                if (!Sewer3.sewerEnemy[e]->getEscapeState()) {
                    Sewer3.sewerEnemy[e]->enemyBehaviour(player, Sewer3.sewerMap, Sewer3.sewerEnemy, Sewer3.enemyCount, e);
                }
                Sewer3.sewerEnemy[e]->checkForPlayer(player);
                if (Sewer3.sewerEnemy[e]->getHealthPoints() > 0) {
                    if (Sewer3.sewerEnemy[e]->getEscapeState()) {
                        Sewer3.sewerEnemy[e]->setEscapeState(false);
                    }
                    else if (!player.getBattleState() && player.checkforbattle(*Sewer3.sewerEnemy[e])) { //if enemy is close to the player trigger battle sequence for that enemy
                        player.setBattleState(true);
                        battlesequence(Sewer3.sewerEnemy[e]);
                        player.setBattleState(false);
                    }
                }
                enemyCount++;
            }
        }
        else if (currentMap == Location::Bunker) {
            for (int e = 0; e < Bunker.BunkerEnemyCount; e++) {

                if (Bunker.bunkerEnemy[e] == nullptr || !Bunker.bunkerEnemy[e]->isSpawned()) {
                    continue;
                }

                enemyX[enemyCount] = Bunker.bunkerEnemy[e]->getPosX();
                enemyY[enemyCount] = Bunker.bunkerEnemy[e]->getPosY();
                enemySymbol[enemyCount] = Bunker.bunkerEnemy[e]->getSymbol();

                if (!Bunker.bunkerEnemy[e]->getEscapeState()) {
                    Bunker.bunkerEnemy[e]->enemyBehaviour(player, Bunker.bunkerMap, Bunker.bunkerEnemy, Bunker.BunkerEnemyCount, e);
                }
                Bunker.bunkerEnemy[e]->checkForPlayer(player);
                if (Bunker.bunkerEnemy[e]->getHealthPoints() > 0) {
                    if (Bunker.bunkerEnemy[e]->getEscapeState()) {
                        Bunker.bunkerEnemy[e]->setEscapeState(false);
                    }
                    else if (!player.getBattleState() && player.checkforbattle(*Bunker.bunkerEnemy[e])) {  //if enemy is close to the player trigger battle sequence for that enemy
                        player.setBattleState(true);
                        battlesequence(Bunker.bunkerEnemy[e]);
                        player.setBattleState(false);
                    }
                }
                enemyCount++;
            }
        }

        std::cout << "player position(x,y): " << player.getPosX() << ", " << player.getPosY() << std::endl;
        std::cout << "press arrow keys to move character" << std::endl;
        
        //print map when loop starts again

        current.printmap(player.getPosX(), player.getPosY(), enemyX, enemyY, enemySymbol ,enemyCount);
        current.discovered(player.getPosX(), player.getPosY());

        int ch = _getch();

        if (ch == 0 || ch == 224) {
            ch = _getch();

            switch (ch) {
            case KEY_ARROW_UP:
                system("CLS");
                handleMovement(0, -1);
                break;
            case KEY_ARROW_DOWN:
                system("CLS");
                handleMovement(0, 1);
                break;
            case KEY_ARROW_LEFT:
                system("CLS");
                handleMovement(-1, 0);
                break;
            case KEY_ARROW_RIGHT:
                system("CLS");
                handleMovement(1, 0);
                break;
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
        case KEY_B:
            system("CLS");       //hides the world map
            bag.inventoryMenu(player); //opens inventory until ESC is pressed.
            system("CLS");       //clear text to see map again
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
            //set player position
            player.setPosition(1, 2);
            std::cout << "Entered: SEWER ONE" << std::endl;
            std::cout << std::endl;

        }

        else if (player.getPosX() == 7 && player.getPosY() == 10) {
            //when player enters sewer2 from the worldmap, make current active map Sewer2.
            currentMap = Location::Sewer2;
            Sewer2.printSewerMap(2);
            //set player position
            player.setPosition(1, 2);
            std::cout << "Entered: SEWER TWO" << std::endl;
            std::cout << std::endl;

        }

        else if (player.getPosX() == 15 && player.getPosY() == 12) {
            //when player enters sewer3 from the worldmap, make current active map Sewer3.
            currentMap = Location::Sewer3;
            Sewer3.printSewerMap(3);
            //set player position
            player.setPosition(1, 2);
            std::cout << "Entered: SEWER THREE" << std::endl;
            std::cout << std::endl;

        }

        else if (player.getPosX() == 0 && player.getPosY() == 7) {
            //when player enters bunker from the worldmap, make current active map bunker.
            currentMap = Location::Bunker;
            Bunker.printbunkerMap();
            //set entity positions
            player.setPosition(7, 4);
            std::cout << "Entered: BUNKER" << std::endl;
            std::cout << std::endl;

        }

        else if (player.getPosX() == 12 && player.getPosY() == 8) {
            //when player enters town from the worldmap, make current active map town.
            currentMap = Location::Town;
            Town.printtownMap();
            //set entity positions
            player.setPosition(1, 7);
            std::cout << "Entered: TOWN" << std::endl;
            std::cout << std::endl;

        }

        else if (player.getPosX() == 19 && player.getPosY() == 7) {
            currentMap = Location::Lab;
            Lab.printlabMap();
            //set entity positions
            player.setPosition(1, 4);
            std::cout << "Entered: LAB" << std::endl;
            std::cout << std::endl;
        }
    }

    //POI exit checking
    else if (currentMap == Location::Sewer1) {
        if (player.getPosX() == 0 && player.getPosY() == 2) {
            currentMap = Location::MainWorld;
            player.setPosition(2, 5);
            std::cout << "Entered: WORLD" << std::endl;
            std::cout << std::endl;
        }
    }
    else if (currentMap == Location::Sewer2) {
        if (player.getPosX() == 0 && player.getPosY() == 2) {
            currentMap = Location::MainWorld;
            player.setPosition(6, 10);
            std::cout << "Entered: WORLD" << std::endl;
            std::cout << std::endl;
        }
    }
    else if (currentMap == Location::Sewer3) {
        if (player.getPosX() == 0 && player.getPosY() == 2) {
            currentMap = Location::MainWorld;
            player.setPosition(14, 12);
            std::cout << "Entered: WORLD" << std::endl;
            std::cout << std::endl;
        }
    }

    else if (currentMap == Location::Bunker) {
        if (player.getPosX() == 8 && player.getPosY() == 4) {
            currentMap = Location::MainWorld;
            player.setPosition(1, 7);
            std::cout << "Entered: WORLD" << std::endl;
            std::cout << std::endl;
        }
    }
    else if (currentMap == Location::Town) {
        if (player.getPosX() == 0 && player.getPosY() == 7) {
            currentMap = Location::MainWorld;
            player.setPosition(11, 8);
            std::cout << "Entered: WORLD" << std::endl;
            std::cout << std::endl;
        }
    }

    else if (currentMap == Location::Lab) {
        if (player.getPosX() == 0 && player.getPosY() == 4) {
            currentMap = Location::MainWorld;
            player.setPosition(18, 7);
            std::cout << "Entered: WORLD" << std::endl;
            std::cout << std::endl;
        }
    }
}

enemy** game::activeEnemy(int& totalCount) {
    if (currentMap == Location::Sewer1) {
        totalCount = Sewer1.enemyCount;
        return Sewer1.sewerEnemy;
    }
    if (currentMap == Location::Sewer2) {
        totalCount = Sewer2.enemyCount;
        return Sewer2.sewerEnemy;
    }
    if (currentMap == Location::Sewer3) {
        totalCount = Sewer3.enemyCount;
        return Sewer3.sewerEnemy;
    }

    totalCount = 0;
    return nullptr;
}

void game::handleMovement(int dx, int dy) {
    int enemyCount = 0;
    enemy** enemies = activeEnemy(enemyCount);
    map& current = activeMap();

    int destX = player.getPosX() + dx;
    int destY = player.getPosY() + dy;

    if (currentMap == Location::Town) {

        //Weaponsmith ('W')
        if (destX == 7 && destY == 10) {
            weaponsmith smith;
            smith.weaponsmithOpen(player, bag);
            return; // dont overlap
        }

        //Alchemist ('A')
        if (destX == 7 && destY == 4) {
            DialogueTree tree;
            npc alchemist(npc::Type::Alchemist, &tree);
            system("CLS"); // Clean the screen before talking
            alchemist.onOverlap();
            return; // dont overlap
        }
    }

    int hitIndex = (enemies != nullptr) ? player.checkEnemyCol(destX, destY, enemies, enemyCount) : -1;

    if (hitIndex != -1) {
        std::cout << "start battle!" << std::endl;
    }
    else {
        player.move(dx, dy);
        player.borderCol(dx, dy, current.getDimensionCOL(), current.getDimensionROW());
    }
}

