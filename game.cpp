#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <limits> //dialogue
#include "game.h"
#include "enemy.h"
#include "boss.h"
#include "player.h"
#include "inventory.h"
#include "sewer.h"
#include "inspect.h"
#include "weaponsmith.h"
#include "alchemist.h"
#include "DialogueTree.h"
#include "npc.h"

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
#define KEY_E 101

#define ESC "\033"
#define RESET   ESC "[0m"
#define RED     ESC "[31m"
#define GREEN   ESC "[32m"
#define YELLOW  ESC  "[33m"
#define BLUE     ESC "[94m"
#define PINK ESC "[95m"

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

    std::string ratASCII = R"(
                       ,     .
                       (\,;,/)
                        (o o)\//,
                         \ /     \,
                         `+'(  (   \    )
                            //  \   |_./
 ---------------------------'~' '~----'----------------          
)";

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

    while (inbattle && player.getPlayerHealthPoints() > 0 && currentEnemy->getHealthPoints() > 0) { // while player and enemy is not dead
        //active weapon
        weapon activeWep = bag.getEquippedWeapon();
        int requiredAP = activeWep.getItemAPcost();
        //player turn
        player.setPlayerActionPoints(player.getPlayerAgility());
        bool playerturn = true;
        
        while (playerturn && player.getPlayerActionPoints() > 0 && currentEnemy->getHealthPoints() > 0) {// while player ap is not 0 and enemy is not dead
            system("CLS");

            if (enemysymbol == 'H') {
                std::cout <<RED << muthumanASCII << std::endl << RESET;
            }
            else if (enemysymbol == 'R') {
                std::cout << RED << ratASCII << std::endl << RESET;
            }

            if (currentMap != Location::MainWorld) {
                std::cout << "\t=== BATTLE ===\n\n";
            }
            else {
                std::cout << "\t=== RANDOM ENCOUNTER ===\n\n";
            }
            std::cout << GREEN << "\tPlayer HP: " << player.getPlayerHealthPoints() << " / " << player.getPlayerMaxHealthPoints() <<RESET  << YELLOW << "  |  AP: " << player.getPlayerActionPoints() << RESET << BLUE << "  |  Active Weapon: " << activeWep.getItemName() <<"\n" << RESET;
            std::cout << RED << "\tEnemy HP:  " << currentEnemy->getHealthPoints() << RESET "\n\n";

            std::cout << "\t[1] Attack (" << requiredAP << " AP)\n";
            std::cout << "\t[2] Item (Equip/Use) (1 AP)\n";
            std::cout << "\t[3] Skip Turn\n";
            std::cout << "\t[4] Run Away\n";
            int act = _getch(); //input

            if (act == '1') {
                int chance = activeWep.getweaponacc();
                int randchance = (rand() % 100) + 1;
                if (player.getPlayerActionPoints() >= requiredAP) {
                    if (randchance < chance) { // if the randomise chance is inside the weapon accuracy chance like for example 60 < 70 it hits
                        int dmg = activeWep.getweapondmg(player) + player.combatDamageBuff;
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

        //------------------------
        // enemy turn
        //------------------------
        if (enemysymbol == 'R') { //if enemy is rat
            system("CLS");
            std::cout << RED << ratASCII << "\n" << RESET;
            std::cout << "\t Enemy Turn!\n\n";

            int dodge = player.getPlayerAgilityFinal();
            int randhit = (rand() % 100) + 1;
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
            std::cout << RED << muthumanASCII << "\n" << RESET;
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
        int gold;
        if (enemysymbol == 'R') {
            expgained = 10 + player.getPlayerIntelligenceFinal();
            gold = 10;
        }
        else if (enemysymbol == 'H') {
            expgained = 20 + player.getPlayerIntelligenceFinal();
            gold = 15;
        }
        player.gainExp(expgained);
        player.loot(gold, 0); //gain gold and 0 frags
        std::cout << YELLOW << "\n\tEnemy defeated! You gained "<< expgained <<" exp and "<< gold << " gold. Press any key..." << RESET;

        //delete enemy after it dies
        delete currentEnemy;
        currentEnemy = nullptr;
        (void)_getch();
        inbattle = false;
        player.combatDamageBuff = 0; //buff wear off
        system("CLS");
    }
}

void game::bossbattlesequence(boss*& thescientist)
{
    bool inbattle = true;
    int weaknessturns = 0;
    int shieldturns = 0;
    std::string bossASCII = R"(                                                                       
                       @@@@@@                                
                  @@#*+=======**#@@                          
               @%+===========+===+=#@                        
             @*=+=*+============-+===*@                      
           @%===-++==============--====%@                    
          @#====+====================+-+@@                   
         @@====--+=========-=--======-==*@                   
         @*===+===++=============+--+=+=+%                   
         @========+===================+=+%                   
         @+=======+=================--==+%                   
         @+=-+=====+=====+*=============*@                   
         @%+*+=+=======+#=====**========#@                   
          @*+=+=======+#====++=+*=-=+*++@                    
           @+=========#+===+=.::-*=====%                     
            @*=======**====*:.:::#+#=-=%                     
            @#=====+*==+==*:....=*=%==#@@@@                  
            @*+**=++*+==##*#++*#*=*%==%=-::=%@               
             @%#-..:#=#==+----==*%%#=#*=::::::=#@@@          
               @*:...:%=+-=*%%%+#%@*=#*=-::::::::::=*%@      
    @**#@@       @%#**=+*%++#%%%#**=*++==+=--::::::::::*@    
   @%=---=+#%%#==#@@#*##::*@*%%#+=*=#=*-:=++%%*++++++-#@     
     @@@@#**+#*===+@        ##*#*%=**++:::::=# #%*+==*@      
       @+--+*#=+*+=%@      @#===*##*+-:::::::=%+#-::+@       
        @+==+**#*+%%%      @+==++#--::::::::::=*=-=+##       
         #***#++*+++-=*@  @+::::+-**=:::::::::-*+-:=@        
         %+#%%++#@#*=::+=#=+-::*@@=+:::-=-:::::=%==%         
               @ #=+-::=+:--:-#@ @***#:::--::::-%#@          
                 %*+====+-:-=@   %-+--:::::::::-#@           
                    @%*@ @##@   @==-*=:::::::::-*@           
                                #-+::::::::::::-+@           
                                *++#*::::::::::=+@           
                                 @+-:::::::-=+#@             
                                     @@@@@@%%@               
                                      @@%@%%%@               
                                      @%%@%%%@               
                                      @%%@%%@@               
                                      @%%@%%%@               
                                    @%%%%@%%%@               
                              @%%%%%@%@%@@%%%@@              
                             @@%%%%%%@@@@%%@@@@@             
                             @%%@@@%@@@ @@%%@%%%%@           
                                @@@      @@@%%%%%%@          
                                          @@@@%%%@@          
                                             @@@@   
)";
    while (inbattle && player.getPlayerHealthPoints() > 0 && thescientist->getHealthPoints() > 0) { // while player and enemy is not dead

        //active weapon
        weapon activeWep = bag.getEquippedWeapon();
        int requiredAP = activeWep.getItemAPcost();
        //player turn
        player.setPlayerActionPoints(player.getPlayerAgility());
        bool playerturn = true;

        while (playerturn && player.getPlayerActionPoints() > 0 && thescientist->getHealthPoints() > 0) {// while player ap is not 0 and enemy is not dead
            system("CLS");

            std::cout << RED << bossASCII << std::endl << RESET;
            std::cout << RED << "\t=== BOSS BATTLE ===\n\n" << RESET;
            std::cout << GREEN << "\tPlayer HP: " << player.getPlayerHealthPoints() << " / " << player.getPlayerMaxHealthPoints() << RESET << YELLOW << "  |  AP: " << player.getPlayerActionPoints() << RESET << BLUE << "  |  Active Weapon: " << activeWep.getItemName() << "\n" << RESET;
            std::cout << "\t Boss HP:  " << thescientist->getHealthPoints() << "\n\n";

            if (weaknessturns > 0) {
                std::cout << RED << "\t[STATUS]: WEAKENED (-30% Attack Power, " << weaknessturns << " turns left)\n" << RESET;
            }
            std::cout << "\t[1] Attack (" << requiredAP << " AP)\n";
            std::cout << "\t[2] Item (Equip/Use) (1 AP)\n";
            std::cout << "\t[3] Skip Turn\n";
            int act = _getch(); //input

            if (act == '1') {
                int chance = activeWep.getweaponacc();
                int randchance = (rand() % 100) + 1;
                if (player.getPlayerActionPoints() >= requiredAP) {
                    if (randchance < chance) { // if the randomise chance is inside the weapon accuracy chance like for example 60 < 70 it hits
                        int dmg = activeWep.getweapondmg(player) + player.combatDamageBuff;
                        if (shieldturns > 0 && weaknessturns > 0) { // if have both shield and weakness
                            int weakdmg = dmg * 0.7;
                            int dmgreduction = weakdmg * 0.2;
                            thescientist->setHealthPoints(thescientist->getHealthPoints() - dmgreduction);
                            player.setPlayerActionPoints(player.getPlayerActionPoints() - requiredAP);
                            std::cout << "\n\tYou dealt " << dmgreduction << " damage with your"
                                << activeWep.getItemName() << "! It did not hit as hard... (20% Damage dealt) Press any key...";
                            (void)_getch();
                        }
                        else if (weaknessturns > 0) { // weakness only
                            int weakdmg = dmg * 0.7;
                            thescientist->setHealthPoints(thescientist->getHealthPoints() - weakdmg);
                            player.setPlayerActionPoints(player.getPlayerActionPoints() - requiredAP);
                            std::cout << "\n\tYou dealt " << weakdmg << " damage with your "
                                << activeWep.getItemName() << "! (Weakened -30% Damage) Press any key...";
                            (void)_getch();
                        }
                        else if (shieldturns > 0) { // shield only
                            int dmgreduction = dmg * 0.2;
                            thescientist->setHealthPoints(thescientist->getHealthPoints() - dmgreduction);
                            player.setPlayerActionPoints(player.getPlayerActionPoints() - requiredAP);
                            std::cout << "\n\tYou dealt " << dmgreduction << " damage with your"
                                << activeWep.getItemName() << "! It did not hit as hard... (20% Damage dealt) (Weakened -30% Damage)  Press any key...";
                            (void)_getch();
                        }
                        else {
                            thescientist->setHealthPoints(thescientist->getHealthPoints() - dmg);
                            player.setPlayerActionPoints(player.getPlayerActionPoints() - requiredAP);
                            std::cout << "\n\tYou dealt " << dmg << " damage with your "
                                << activeWep.getItemName() << "! Press any key...";
                            (void)_getch();
                        }
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
        }

        if (thescientist->getHealthPoints() <= 0) break; //if the scientist dies stop loop
        system("CLS");
        std::cout << RED << bossASCII << std::endl << RESET;
        std::cout << "\t Boss Turn \n\n";

        int dodge = player.getPlayerAgilityFinal();
        int randhit = rand() % 100;
        int dodgebuff = dodge;
        int moverand = rand() % 4;
        if (!activeWep.getweaponismelee()) {
            dodgebuff += 30;
        }

        if (randhit < dodgebuff) {
            std::cout << "\tYou dodged the Boss's attack!\n";
            std::cout << "\tPress any key to start your next turn...";
            (void)_getch();
        }
        else {
            if (moverand == 0) { // poison vials
                int enemydmg = 20;
                player.setPlayerHealthPoints(player.getPlayerHealthPoints() - enemydmg); // enemy attack hp deduct
                std::cout << "\tThe Scientist threw a vial of toxins at you for " << enemydmg << " damage!\n";
            }
            else if (moverand == 1) { // tackle
                int enemydmg = 30;
                player.setPlayerHealthPoints(player.getPlayerHealthPoints() - enemydmg);
                std::cout << "\tThe Scientist threw himself at you for " << enemydmg << " damage!\n";
                std::cout << "\tYou feel sharp bone fragments piercing your skin...\n";
            }
            else if (moverand == 2) { // weakness syringe
                int enemydmg = 10;
                weaknessturns = 2;
                player.setPlayerHealthPoints(player.getPlayerHealthPoints() - enemydmg);
                std::cout << "\tThe Scientist injected you with a Weakness Syringe for " << enemydmg << " damage!\n";
                std::cout << "\tYour attack power is reduced by 30% for 2 turns!\n";
            }
            else if (moverand == 3) {
                shieldturns = 1;
                std::cout << "\tThe Scientist drank a Shield Potion!\n";
                std::cout << "\tFor the next turn, he will only take 20% of incoming damage.\n";
            }
        }
        if (weaknessturns > 0) {
            weaknessturns--;
        }
        if (shieldturns > 0) {
            shieldturns--;
        }
        std::cout << "\n\tPress any key to start your next turn...";
        (void)_getch();
    }
    if (thescientist != nullptr && thescientist->getHealthPoints() <= 0) {
        int expgained = 100000 + player.getPlayerIntelligenceFinal();
        int gold = 100000;

        player.gainExp(expgained);
        player.loot(gold, 0);

        system("CLS");
        std::cout << YELLOW << "\n\t======================================================\n" << RESET;
        std::cout << YELLOW << "\t  BOSS DEFEATED! You gained " << expgained << " exp and " << gold << " gold!\n" << RESET;
        std::cout << YELLOW << "\t======================================================\n\n" << RESET;
        std::cout << YELLOW << "\tPress any key to continue..." << RESET;
        (void)_getch();

        delete thescientist;
        thescientist = nullptr; //delete
        handleEndings();
    }
        player.combatDamageBuff = 0; 
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
    int febDays = 28;

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
                febDays = 29;
            }
            else {
                febDays = 28;
            }

            if ((month == 1 && day >= 32) || (month == 2 && day >= febDays + 1) || (month == 3 && day >= 32) || (month == 4 && day >= 31) ||
                (month == 5 && day >= 32) || (month == 6 && day >= 31) || (month == 7 && day >= 32) || (month == 8 && day >= 32) ||
                (month == 9 && day >= 31) || (month == 10 && day >= 32) || (month == 11 && day >= 31) || (month == 12 && day >= 32)) {

                while ((month == 1 && day >= 32) || (month == 2 && day >= febDays + 1) || (month == 3 && day >= 32) || (month == 4 && day >= 31) ||
                    (month == 5 && day >= 32) || (month == 6 && day >= 31) || (month == 7 && day >= 32) || (month == 8 && day >= 32) ||
                    (month == 9 && day >= 31) || (month == 10 && day >= 32) || (month == 11 && day >= 31) || (month == 12 && day >= 32)) {

                    switch (month) {
                    case 1:
                        day = day - 31;
                        break;
                    case 2:
                        day = day - febDays;
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



    std::cout << "<PROLOGUE>" << std::endl;
    std::cout << std::endl;
    std::cout << "You are a survivor of a war. During the initial outbreak of the war, you quickly took\n"
              << "shelter in a nearby bunker for safety. No one else made it. Overtime, supplies started\n"
              << "to run low. With supplies running low, you had no choice but to leave the bunker to\n"
              << "avoid dying of starvation. This is where your story begins." << std::endl;
    std::cout << std::endl;
    std::cout << "Press Enter to start creating your character...";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    system("CLS");



    std::cout << "Enter your name: ";
    std::getline(std::cin, tempName);
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
        std::cout << std::endl;
        std::cout << "Can't have stats lower than 2 and you have to use all 5 stat points." << std::endl;
        std::cout << "Enter 'Ready' when ready." << std::endl;
        std::cout << "Inputs: S+, S-, A+, A-, L+, L-, E+, E-, I+, I-" << std::endl;
        std::cin >> ccInput;
        if ((ccInput == "S+" || ccInput == "s+") && player.getStatPoints() > 0) {
            player.setPlayerStrength(player.getPlayerStrength() + 1);
            player.setStatPoints(player.getStatPoints() - 1);
            system("CLS");
        }
        else if ((ccInput == "S-" || ccInput == "s-") && player.getPlayerStrength() > 2) {
            player.setPlayerStrength(player.getPlayerStrength() - 1);
            player.setStatPoints(player.getStatPoints() + 1);
            system("CLS");
        }
        else if ((ccInput == "A+" || ccInput == "a+") && player.getStatPoints() > 0) {
            player.setPlayerAgility(player.getPlayerAgility() + 1);
            player.setStatPoints(player.getStatPoints() - 1);
            system("CLS");
        }
        else if ((ccInput == "A-" || ccInput == "a-") && player.getPlayerAgility() > 2) {
            player.setPlayerAgility(player.getPlayerAgility() - 1);
            player.setStatPoints(player.getStatPoints() + 1);
            system("CLS");
        }
        else if ((ccInput == "L+" || ccInput == "l+") && player.getStatPoints() > 0) {
            player.setPlayerLuck(player.getPlayerLuck() + 1);
            player.setStatPoints(player.getStatPoints() - 1);
            system("CLS");
        }
        else if ((ccInput == "L-" || ccInput == "l-") && player.getPlayerLuck() > 2) {
            player.setPlayerLuck(player.getPlayerLuck() - 1);
            player.setStatPoints(player.getStatPoints() + 1);
            system("CLS");
        }
        else if ((ccInput == "E+" || ccInput == "e+") && player.getStatPoints() > 0) {
            player.setPlayerEndurance(player.getPlayerEndurance() + 1);
            player.setStatPoints(player.getStatPoints() - 1);
            system("CLS");
        }
        else if ((ccInput == "E-" || ccInput == "e-") && player.getPlayerEndurance() > 2) {
            player.setPlayerEndurance(player.getPlayerEndurance() - 1);
            player.setStatPoints(player.getStatPoints() + 1);
            system("CLS");
        }
        else if ((ccInput == "I+" || ccInput == "i+") && player.getStatPoints() > 0) {
            player.setPlayerIntelligence(player.getPlayerIntelligence() + 1);
            player.setStatPoints(player.getStatPoints() - 1);
            system("CLS");
        }
        else if ((ccInput == "I-" || ccInput == "i-") && player.getPlayerIntelligence() > 2) {
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

void game::randomEncounter() {
    int randomNum = (rand() % 100) + 1;
    int chance = 50;

    if ((hour > 21) || (hour < 6)) { // night time
        chance = (29 - player.getPlayerLuck());
    }
    else { // day time
        chance = (7 - player.getPlayerLuck());
    }

    if (randomNum <= chance) {
        if (currentMap == Location::MainWorld) {
            if ((player.getPosX() != 3 && player.getPosY() != 5) || (player.getPosX() != 7 && player.getPosY() != 10) ||
                (player.getPosX() != 15 && player.getPosY() != 12) || (player.getPosX() != 0 && player.getPosY() != 7) ||
                (player.getPosX() != 12 && player.getPosY() != 8) || (player.getPosX() != 19 && player.getPosY() != 7)) {

                int roll = rand() % 2;

                if (roll == 0) {
                    worldEnemy = new mutRat(0, 0, 0);
                }
                else {
                    worldEnemy = new mutHuman(0, 0, 0); 
                }

                player.setBattleState(true);
                battlesequence(worldEnemy);
                player.setBattleState(false);

                //double check the delete to make sure
                if (worldEnemy != nullptr) {
                    delete worldEnemy;
                    worldEnemy = nullptr;
                }
            }
        }
    }
}

void game::Run()
{
    bool gameRunning = true;
    Intro(); //comment out to skip intro

    Bunker.printbunkerMap();
    player.setPosition(0, 4);
    currentMap = Location::Bunker; //starting map

    initialinfo(); //save pos at bunker

    while (gameRunning && !gameEnd) {
        map& current = activeMap();

        //define the number of enemies in total
        //total number of sewer enemies
        int enemyX[6];
        int enemyY[6];
        char enemySymbol[6];

        int bossX = -1;
        int bossY = -1;
        char bossSymbol = 'B';

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
        //controls enemy behaviour, render and battle for each room w enemies inside
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

        if (player.checkAlive() == false)
        {
            system("CLS");
            std::cout << "\t   _-----------_   \n";
            std::cout << "\t  |             |  \n";
            std::cout << "\t |   R   I   P   | \n";
            std::cout << "\t |               | \n";
            std::cout << "\t |               | \n";
            std::cout << "\t |               | \n";
            std::cout << "\t |               | \n";
            std::cout << "\t |               | \n";
            std::cout << "\t |=&==&==&==&==&=| \n";

            std::cout << "\tYou have been fatally wounded and fainted in combat. Luckily someone found you...\n";
            std::cout << "\tPress any key to continue...\n";
            (void)_getch();

            system("CLS");
            player.respawn();
            Town.printtownMap();
            player.setPosition(7, 7);
            currentMap = Location::Town;
            continue;
        }

        else if (currentMap == Location::Lab) {
            
            for (int e = 0; e < Lab.labEnemyCount; e++) {

                if (Lab.labEnemy[e] == nullptr || !Lab.labEnemy[e]->isSpawned()) {
                    continue;
                }

                enemyX[enemyCount] = Lab.labEnemy[e]->getPosX();
                enemyY[enemyCount] = Lab.labEnemy[e]->getPosY();
                enemySymbol[enemyCount] = Lab.labEnemy[e]->getSymbol();

                if (!Lab.labEnemy[e]->getEscapeState()) {
                    Lab.labEnemy[e]->enemyBehaviour(player, Lab.labMap, Lab.labEnemy, Lab.labEnemyCount, e);
                }
                Lab.labEnemy[e]->checkForPlayer(player);
                if (Lab.labEnemy[e]->getHealthPoints() > 0) {
                    if (Lab.labEnemy[e]->getEscapeState()) {
                        Lab.labEnemy[e]->setEscapeState(false);
                    }
                    else if (!player.getBattleState() && player.checkforbattle(*Lab.labEnemy[e])) {  //if enemy is close to the player trigger battle sequence for that enemy
                        player.setBattleState(true);
                        battlesequence(Lab.labEnemy[e]);
                        player.setBattleState(false);
                    }
                }
                enemyCount++;
            }

            //for the laboratory
            Lab.checkRoomClear();//check if room has been cleared every code loop
            if (Lab.TheScientist != nullptr && Lab.TheScientist->getBossActive()) {
                bossX = Lab.TheScientist->getPosX();
                bossY = Lab.TheScientist->getPosY();
                bossSymbol = Lab.TheScientist->getSymbol();

                int distX = std::abs(player.getPosX() - bossX);
                int distY = std::abs(player.getPosY() - bossY);

                player.setBattleState(true);
                bossbattlesequence(Lab.TheScientist);
                player.setBattleState(false);

                if (gameEnd) {
                    gameRunning = false;
                    system("CLS");
                    continue;
                }
            }
        }

        std::cout << "player position(x,y): " << player.getPosX() << ", " << player.getPosY() << std::endl;
        std::cout << "press arrow keys to move character" << std::endl;

        
        //print map when loop starts again

        current.printmap(player.getPosX(), player.getPosY(), enemyX, enemyY, enemySymbol ,enemyCount, bossX, bossY, bossSymbol);
        current.discovered(player.getPosX(), player.getPosY());

        int ch = _getch();

        if (ch == 0 || ch == 224) {
            ch = _getch();

            switch (ch) {
            case KEY_ARROW_UP:
                handleMovement(0, -1);
                break;
            case KEY_ARROW_DOWN:     
                handleMovement(0, 1);
                break;
            case KEY_ARROW_LEFT:
                handleMovement(-1, 0);
                break;
            case KEY_ARROW_RIGHT:
                handleMovement(1, 0);
                break;
            }
            //checks which POI player has entered/exited
            //check if player has discovered a poi after moving
            discoverpoi();
            checkMapChange();
            if (currentMap == Location::MainWorld) {
                randomEncounter();
            }
            handleThirdEnding(day, month);
        }
        //check if quit game
        else if (ch == 'q' || ch == 'Q') {
            char confirmQuit;
            system("CLS");
            std::cout << "Are you sure you want to quit? Y / N" << std::endl;
            std::cin >> confirmQuit;
            if (confirmQuit == 'Y' || confirmQuit == 'y') {
                system("CLS");
                gameRunning = false;
                std::cout << "Game closed" << std::endl;
                break;
            }
            else if (confirmQuit == 'N' || confirmQuit =='n') {
                system("CLS");
                continue;
            }
        }

        int enemiesCount = 0;
        inspect inspector;
        enemy** enemies = activeEnemy(enemiesCount);

        switch (ch) {
        case KEY_B:
            system("CLS");       //hides the world map
            bag.inventoryMenu(player); //opens inventory until ESC is pressed.
            system("CLS");       //clear text to see map again
            break;

        case KEY_E: // inspect
            system("CLS");
            inspector.inspectOpen(enemies, enemiesCount);
            system("CLS");
            break;

        case KEY_M:
            system("CLS");
            {
                if (npc::talkedToRyan) {
                    settings.setObjective(2);
                }

                if (player.getPlayerKeyFragment() >= 3) {
                    settings.setObjective(2);
                }

                int menuAction = settings.menuOpen(day, month, year, hour, minute);

                if (menuAction > 0) {
                    timePassMinutes(menuAction); // Skip time
                }
                else if (menuAction == -1) {
                    restartstage(); // Trigger stage restart
                }
                else if (menuAction == -2) {
                    restartgame(); // Trigger full restart
                }
            }
            system("CLS");
            break;
        }
        system("CLS");
    }
}

void game::checkMapChange() {
    //worldmap entry to POIs checking
    if (currentMap == Location::MainWorld) {
        settings.setObjective(1); //find 3 key frags

        if (player.getPosX() == 3 && player.getPosY() == 5) {
            currentMap = Location::Sewer1;
            Sewer1.printSewerMap(1);
            player.setPosition(1, 2);
            initialinfo(); // Moved below setPosition!
        }
        else if (player.getPosX() == 7 && player.getPosY() == 10) {
            currentMap = Location::Sewer2;
            Sewer2.printSewerMap(2);
            player.setPosition(1, 2);
            initialinfo();
        }
        else if (player.getPosX() == 15 && player.getPosY() == 12) {
            currentMap = Location::Sewer3;
            Sewer3.printSewerMap(3);
            player.setPosition(1, 2);
            initialinfo();
        }
        else if (player.getPosX() == 0 && player.getPosY() == 7) {
            currentMap = Location::Bunker;
            Bunker.printbunkerMap();
            player.setPosition(7, 4);
            initialinfo();
        }
        else if (player.getPosX() == 12 && player.getPosY() == 8) {
            currentMap = Location::Town;
            Town.printtownMap();
            player.setPosition(1, 7);
            initialinfo(); // Added to Town!
        }
        else if (player.getPosX() == 19 && player.getPosY() == 7 && player.getPlayerKeyFragment() < 3) {
            player.setPosition(18, 7);
            std::cout << "You can't enter without the 3 key fragments" << std::endl;
        }
        else if (player.getPosX() == 19 && player.getPosY() == 7 && player.getPlayerKeyFragment() >= 3) {
            currentMap = Location::Lab;
            Lab.printlabMap();
            player.setPosition(1, 4);
            initialinfo(); 
        }
    }

    //POI exit checking
    else if (currentMap == Location::Sewer1) {
        if (player.getPosX() == 0 && player.getPosY() == 2) {
            currentMap = Location::MainWorld;
            player.setPosition(2, 5);
            initialinfo(); 
        }
    }
    else if (currentMap == Location::Sewer2) {
        if (player.getPosX() == 0 && player.getPosY() == 2) {
            currentMap = Location::MainWorld;
            player.setPosition(6, 10);
            initialinfo();
        }
    }
    else if (currentMap == Location::Sewer3) {
        if (player.getPosX() == 0 && player.getPosY() == 2) {
            currentMap = Location::MainWorld;
            player.setPosition(14, 12);
            initialinfo();
        }
    }
    else if (currentMap == Location::Bunker) {
        if (player.getPosX() == 8 && player.getPosY() == 4) {
            currentMap = Location::MainWorld;
            player.setPosition(1, 7);
            initialinfo();
        }
    }
    else if (currentMap == Location::Town) {
        if (player.getPosX() == 0 && player.getPosY() == 7) {
            currentMap = Location::MainWorld;
            player.setPosition(11, 8);
            initialinfo();
        }
        if (player.getPosX() == 7 && player.getPosY() == 3) {
            std::string catASCII = R"(                           .#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  .                  
.                  .    .::#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%:::         .        
 .    .                 %@@=:::::::::::::::::::::::::::::::::::::::::::::::::::@@@.   .           . 
                     %@@=:::::::::--------------------------------------:::::::::-@@@  ..        .  
 .             .  .  %@@-:::::::::---------------------------------------:::::::::@@@    .        . 
 .  .      .         %@@-::::::-----------------=++=-----=++=---------------::::::@@@         .     
     .               %@@-:::::------------------=++=------++=---------------::::::@@@               
        .            %@@-:::-----=++=------------------------------------------:::@@@               
                .    %@@-:::-----------------------------+@@@@@#------+++------:::@@@   @@@@@@      
      .  .           %@@-:::-----------------------------+@@@@@#------+++------:::@@@   @@@@@@      
        . . .        %@@-:::--------------------------*@@#=====*@@%------------:::@@@@@@======@@@.  
   ============.  .  %@@-:::------------------==------*@@#=====+###+++---------:::@@@###======@@@.  
   @@@@@@@@@@@@..    %@@-:::-----------------=++=-----*@@#========+@@%---------:::@@@=========@@@   
   @@@======@@@@@@:  %@@-:::--------------------------*@@#===========+@@@@@@@@@@@@============@@@   
  .@@@======@@@@@@: .%@@-:::--------------------------*@@#===========+@@@@@@@@@@@@============@@@   
   @@@@@@======@@@@@@@@@-:::--------=++=--------------*@@#====================================@@@   
   +++@@@###===###@@@@@@-:::---------==----------==+***##*====================================###+++
..    @@@@@@======@@@@@@-:::--------------------=++#@@#==========================================@@@
         @@@@@@======@@@-:::--+++------------------*@@#========-  -@@@===============   @@@======@@@
         @@@@@@======@@@-:::--+++------------------*@@#========-  -@@@===============   @@@======@@@
    .       @@@@@@@@@@@@-:::-----------------------*@@#========*@@@@@@=========@@@===@@@@@@======@@@
    .       ======@@@@@@-:::---------------==------*@@#===-----=******=========***===******------@@@
              .   %@@@@@-:::--------------=++=-----*@@#===------===========================------@@@
      .              %@@-::::::--=++=--------------*@@#===------==+@@@=====+@@@======@@@===------@@@
    .                %@@-::::::--=++=--------------*@@#===------==+@@@=====+@@@======@@@===------@@@
           .         %@@-:::::::::--------------------*@@%========+@@@@@@@@@@@@@@@@@@@@@======@@@   
            .    .*##@@@%##-::::::::::::::::::::::::::-==*%%#=====+*********************===%%%---   
 .                %@@@@@@@@=:::::::::::::::::::::::::::::+@@%==============================@@@      
         .     @@@+========%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@        .
      .        @@@+========%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@         
      .        @@@+=====@@@@@@- .#@@*=====#@@+              -@@%=====+@@%  :@@@======@@@      .     
          .    @@@@@@@@@@@@=::.  #@@@@@@@@+::.            . .::=@@@@@@@@%  .::-@@@@@@:::            
  .        .   @@@@@@@@@@@@-     #@@@@@@@@=        .           -@@@@@@@@%     .@@@@@@    
           
meow (press any key to exit))";
            system("CLS");
            std::cout << PINK << catASCII << "\n" << RESET;
            (void)_getch(); 
            player.setPosition(6, 3);
            system("CLS");
            initialinfo();
        }
    }
    else if (currentMap == Location::Lab) {
        if (player.getPosX() == 0 && player.getPosY() == 4) {
            if (Lab.TheScientist != nullptr && Lab.TheScientist->getBossActive()) {
            }
            else {
                currentMap = Location::MainWorld;
                player.setPosition(18, 7);
                initialinfo();
            }
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
	if (currentMap == Location::Bunker) {
		totalCount = Bunker.BunkerEnemyCount;
		return Bunker.bunkerEnemy;
	}

    return nullptr;
}

void game::initialinfo() //for restart stage to chang info to your info when you first entered the location
{
    // Save the time
    backupDay = day; backupMonth = month; backupYear = year;
    backupHour = hour; backupMinute = minute;

    // Save the player's stats
    backupHP = player.getPlayerHealthPoints();
    backupName = player.getPlayerName();
    backupLevel = player.getPlayerLevel();
    backupExp = player.getPlayerExp();
    backupGold = player.getPlayerGold();
    backupKeyFragment = player.getPlayerKeyFragment();
    backupStatPoints = player.getStatPoints();
    backupPosX = player.getPosX();
    backupPosY = player.getPosY();
    backupBag = bag;

    backupLooted1 = isLooted1;
    backupLooted2 = isLooted2; 
    backupLooted3 = isLooted3;
}

void game::restartstage() //testing
{
    //restore time
    day = backupDay; month = backupMonth; year = backupYear;
    hour = backupHour; minute = backupMinute;

    //restore the player stats
    player.setPlayerHealthPoints(backupHP);
    player.setPlayerName(backupName);
    player.setPlayerGold(backupGold);
    player.setPlayerKeyFragment(backupKeyFragment);
    player.setStatPoints(backupStatPoints);
    player.setPlayerLevel(backupLevel);
    player.setPlayerExp(backupExp);
    bag = backupBag;

    //restore looted chests
    isLooted1 = backupLooted1;
    isLooted2 = backupLooted2;
    isLooted3 = backupLooted3;

    //set pos to back up 
    player.setPosition(backupPosX, backupPosY);

    //spawn back enemies
    if (currentMap == Location::Sewer1) {
        for (int e = 0; e < Sewer1.enemyCount; e++) {
            if (Sewer1.sewerEnemy[e] == nullptr) Sewer1.sewerEnemy[e] = (e < 3) ? (enemy*)new mutRat(0, 0, e) : (enemy*)new mutHuman(0, 0, e);
            Sewer1.sewerEnemy[e]->setHealthPoints((e < 3) ? 30 : 70);
        }
        Sewer1.printSewerMap(1);
    }
    else if (currentMap == Location::Sewer2) {
        for (int e = 0; e < Sewer2.enemyCount; e++) {
            if (Sewer2.sewerEnemy[e] == nullptr) Sewer2.sewerEnemy[e] = (e < 3) ? (enemy*)new mutRat(0, 0, e) : (enemy*)new mutHuman(0, 0, e);
            Sewer2.sewerEnemy[e]->setHealthPoints((e < 3) ? 30 : 70);
        }
        Sewer2.printSewerMap(2);
    }
    else if (currentMap == Location::Sewer3) {
        for (int e = 0; e < Sewer3.enemyCount; e++) {
            if (Sewer3.sewerEnemy[e] == nullptr) Sewer3.sewerEnemy[e] = (e < 3) ? (enemy*)new mutRat(0, 0, e) : (enemy*)new mutHuman(0, 0, e);
            Sewer3.sewerEnemy[e]->setHealthPoints((e < 3) ? 30 : 70);
        }
        Sewer3.printSewerMap(3);
    }
    else if (currentMap == Location::Bunker) {
        for (int e = 0; e < Bunker.BunkerEnemyCount; e++) {
            if (Bunker.bunkerEnemy[e] == nullptr) Bunker.bunkerEnemy[e] = new mutRat(0, 0, e);
            Bunker.bunkerEnemy[e]->setHealthPoints(30);
        }
        Bunker.printbunkerMap();
    }
    else if (currentMap == Location::Lab) {
        for (int e = 0; e < Lab.labEnemyCount; e++) {
            if (Lab.labEnemy[e] == nullptr) Lab.labEnemy[e] = (e < 2) ? (enemy*)new mutRat(0, 0, e) : (enemy*)new mutHuman(0, 0, e);
            Lab.labEnemy[e]->setHealthPoints((e < 2) ? 30 : 70);
        }
        //reset booss
        if (Lab.TheScientist != nullptr) {
            delete Lab.TheScientist;
            Lab.TheScientist = nullptr;
        }
        Lab.printlabMap();
    }
    else if (currentMap == Location::Town) {
        Town.printtownMap();
    }
    else if (currentMap == Location::MainWorld) {
       
    }

}


void game::restartgame()
{
    day = 29; month = 12; year = 2026;
    hour = 4; minute = 0;

    player.setPlayerHealthPoints(100);
    player.setPlayerLevel(0);
    player.setPlayerExp(0);
    player.setPlayerStrength(2);
    player.setPlayerAgility(2);
    player.setPlayerLuck(2);
    player.setPlayerEndurance(2);
    player.setPlayerIntelligence(10);
    player.setPlayerGold(20);
    player.setPlayerKeyFragment(0);
    player.combatDamageBuff = 0;

    //empy bag and reset chests
    bag = inventory();
    isLooted1 = false;
    isLooted2 = false;
    isLooted3 = false;

    //respawn enemies back
    for (int e = 0; e < Bunker.BunkerEnemyCount; e++) {
        if (Bunker.bunkerEnemy[e] == nullptr) Bunker.bunkerEnemy[e] = new mutRat(0, 0, e);
        Bunker.bunkerEnemy[e]->setHealthPoints(30);
    }
    for (int e = 0; e < Sewer1.enemyCount; e++) {
        if (Sewer1.sewerEnemy[e] == nullptr) Sewer1.sewerEnemy[e] = (e < 3) ? (enemy*)new mutRat(0, 0, e) : (enemy*)new mutHuman(0, 0, e);
        Sewer1.sewerEnemy[e]->setHealthPoints((e < 3) ? 30 : 70);
    }
    for (int e = 0; e < Sewer2.enemyCount; e++) {
        if (Sewer2.sewerEnemy[e] == nullptr) Sewer2.sewerEnemy[e] = (e < 3) ? (enemy*)new mutRat(0, 0, e) : (enemy*)new mutHuman(0, 0, e);
        Sewer2.sewerEnemy[e]->setHealthPoints((e < 3) ? 30 : 70);
    }
    for (int e = 0; e < Sewer3.enemyCount; e++) {
        if (Sewer3.sewerEnemy[e] == nullptr) Sewer3.sewerEnemy[e] = (e < 3) ? (enemy*)new mutRat(0, 0, e) : (enemy*)new mutHuman(0, 0, e);
        Sewer3.sewerEnemy[e]->setHealthPoints((e < 3) ? 30 : 70);
    }
    for (int e = 0; e < Lab.labEnemyCount; e++) {
        if (Lab.labEnemy[e] == nullptr) Lab.labEnemy[e] = (e < 2) ? (enemy*)new mutRat(0, 0, e) : (enemy*)new mutHuman(0, 0, e);
        Lab.labEnemy[e]->setHealthPoints((e < 2) ? 30 : 70);
    }
    //reset boss
    if (Lab.TheScientist != nullptr) {
        delete Lab.TheScientist;
        Lab.TheScientist = nullptr;
    }

    Intro();
    currentMap = Location::Bunker;
    Bunker.printbunkerMap();
    player.setPosition(0, 4);
    initialinfo();
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
            DialogueTree tree;
            npc weaponsmith(npc::Type::Ryan, &tree);
            system("CLS"); // Clean the screen before talking
            weaponsmith.onOverlap(player, bag);
            return; // dont overlap
        }

        //Alchemist ('A')
        if (destX == 7 && destY == 4) {
            DialogueTree tree;
            npc alchemist(npc::Type::Alchemist, &tree);
            system("CLS");
            alchemist.onOverlap(player, bag);
            return; // dont overlap
        }
        //Motel ('M')
        if (destX == 3 && destY == 12) {
            player.heal(30);
            std::cout << "You rested at the motel for a night. <+30 HP>" << std::endl;
            (void)_getch();
			timePassMinutes(480); // 8 hours
            return; // dont overlap
        }
    }
    if (currentMap == Location::Sewer1) {
        if (destX == 29 && destY == 0) {
			if (!isLooted1) {
				player.loot(20, 1);
				std::cout << "You found 20 gold and 1 key fragment in the chest." << std::endl;
                (void)_getch();
				isLooted1 = true;
			}
			else {
				std::cout << "The chest is empty." << std::endl;
				(void)_getch();
			}
        }
    }
    if (currentMap == Location::Sewer2) {
        if (destX == 29 && destY == 0) {
            if (!isLooted2) {
                player.loot(10, 1);
                std::cout << "You found 20 gold and 1 key fragment in the chest." << std::endl;
                (void)_getch();
                isLooted2 = true;
            }
			else {
				std::cout << "The chest is empty." << std::endl;
				(void)_getch();
			}
        }
    }
    if (currentMap == Location::Sewer3) {
        if (destX == 29 && destY == 0) {
            if (!isLooted3) {
                player.loot(10, 1);
                std::cout << "You found 20 gold and 1 key fragment in the chest." << std::endl;
                (void)_getch();
                isLooted3 = true;
            }
            else {
				std::cout << "The chest is empty." << std::endl;
				(void)_getch();
            }
        }
        // Jake ('J')
        if (destX == 15 && destY == 4) {
            DialogueTree tree;
            npc jake(npc::Type::Jake, &tree);
            system("CLS"); // Clean the screen before talking
            jake.onOverlap(player, bag);
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

void game::handleEndings() {
    system("CLS");

    std::cout << "<EPILOGUE>" << std::endl;
    std::cout << "The Scientist falls to the ground, on the verge of death. As you loom over his body, he says one final sentence." << std::endl;
    (void)_getch();
    std::cout <<"'" << player.getPlayerName() << "... it seems like I wasn't strong enough to take you down...";
    (void)_getch();
    std::cout << "but are you strong enough to hold off against..." << std::endl;
    (void)_getch();
    std::cout << "THEM?' says The Scientist, with his final breath." << std::endl;
    std::cout << std::endl;
    (void)_getch();
    std::cout << "You turn around. Right outside you hear the sounds of the mutants." << std::endl;
    (void)_getch();
    std::cout << "You listen carefully. They're getting louder, they're getting closer." << std::endl;
    (void)_getch();
    std::cout << "Realising that you don't have much time, you quickly run towards Jake's workbench" << std::endl;
    std::cout << std::endl;
    (void)_getch();
    std::cout << "You know there's only ONE way to get out of this situation alive." << std::endl;
    (void)_getch();
    system("CLS");

    if (player.getPlayerIntelligenceFinal() >= 10) { //GOOD ENDING DIALOGUE
        std::cout << "You precisely grab some bottles of chemicals." << std::endl;
        (void)_getch();
        std::cout << "Referring to Jake's unfinished research, you create a mixture of chemicals that replicate Jake's cure." << std::endl;
        (void)_getch();
        std::cout << "You start to overclock your brain, trying to solve the problem behind the cure's incompleteness.\nThen, it hits you." << std::endl;
        std::cout << std::endl;
        (void)_getch();
        std::cout << "From the nearby cupboard, you rummage through the different bottles and grab a small vial will a green liquid inside." << std::endl;
        (void)_getch();
        std::cout << "Pouring it inside your concoction, the entire mixture changes to a bright green colour, emitting a blinding glow." << std::endl;
        std::cout << std::endl;
        (void)_getch();
        std::cout << "BAM! The mutants suddenly burst through the door and sprint straight towards you. \nThen, you remember something that Jake said..." << std::endl;
        (void)_getch();
        std::cout << "'As long as the mutants are alive, he'll keep regenerating.' You realise something game changing." << std::endl;
        std::cout << std::endl;
        (void)_getch();
        std::cout << "In one swift motion, you turn around and throw the cure at the mutants with all your strength." << std::endl;
        (void)_getch();
        std::cout << "The vial shatters and spills everywhere on a Mutated Human's head. The liquid seeps in through an open wound." << std::endl;
        std::cout << std::endl;
        (void)_getch();
        std::cout << "Suddenly, the Mutants come to a halt, and their distinctive mutant features start to fade away." << std::endl;
        (void)_getch();
        std::cout << "You cautiously approach one of the hopefully cured humans." << std::endl;
        (void)_getch();
        std::cout << "'Are you good?' you ask the human. He looks up at you, and says 'What.. even happened here?'" << std::endl;
        (void)_getch();
        std::cout << "You run out of the lab. The other Mutants start to change back to their original selves as well." << std::endl;
        std::cout << std::endl;
        (void)_getch();
        std::cout << "You smile for the first time in years. A genuine one. It's finally over..." << std::endl;
        std::cout << "[GOOD ENDING]" << std::endl;
        std::cout << "Press any key to exit the game";
        (void)_getch();
        gameEnd = true;
    }
    else if (player.getPlayerIntelligenceFinal() < 10) { //BAD ENDING DIALOGUE
        std::cout << "You grab some bottles of chemicals in a panic." << std::endl;
        (void)_getch();
        std::cout << "Referring to Jake's unfinished research, you attempt to replicate the 'cure' that Jake had originally come up with." << std::endl;
        (void)_getch();
        std::cout << "You can't figure out the missing piece behind Jake's cure. You panic even more." << std::endl;
        (void)_getch();
        std::cout << "From the nearby cupboard, you grab another handful of random chemicals, hoping you can make something out of it." << std::endl;
        std::cout << std::endl;
        (void)_getch();
        std::cout << "BAM! The mutants suddenly burst through the door and sprint straight towards you." << std::endl;
        (void)_getch();
        std::cout << "Out of instinct, you throw the vial in your hand towards the Mutated Human running towards you." << std::endl;
        (void)_getch();
        std::cout << "To your horror, the Mutant seems unaffected by it. It enrages the Mutant, causing it to go in a state of fury." << std::endl;
        (void)_getch();
        std::cout << "You try to draw your weapon, but it is too late. The Mutant pounces on you, followed by other Mutants." << std::endl;
        std::cout << std::endl;
        (void)_getch();
        std::cout << "As you struggle to free yourself from the pile of Mutants, you can feel your life slowly being drained away." << std::endl;
        (void)_getch();
        std::cout << "You shut your eyes, accepting your fate." << std::endl;
        std::cout << std::endl;
        (void)_getch();
        std::cout << "The Scientist is dead. But so are you. The Mutants continue to roam, prolonging the Apocalypse." << std::endl;
        (void)_getch();
        std::cout << "Though the evil mastermind behind this is gone, the problem remains unresolved, leaving the survivors to wonder: " << std::endl;
        (void)_getch();
        std::cout << "'When will this all be over?'" << std::endl;
        std::cout << "[BAD ENDING]" << std::endl;
        std::cout << "Press any key to exit the game";
        (void)_getch();
        gameEnd = true;
    }
}

void game::handleThirdEnding(int day, int month){

    if (day == dayDeadline && month == 3) { //when it is the deadline day on march, ending 3 plays out
        //write out the third ending 
        system("CLS");
        std::cout << "<EPILOGUE>" << std::endl;

        std::cout << "It is currently " << day << " March. Oddly enough, you feel a strange aura in the world today." << std::endl;
        (void)_getch();
        std::cout << "Instincts tell you to investigate the laboratory. Sure enough, you feel as if soemthing bad is\ngoing to happen." << std::endl;
        (void)_getch();
        std::cout << "Just as you reach for the entrance door, a giant Mutant bursts out of the door." << std::endl;
        (void)_getch();
        std::cout << "The Scientist is being grabbed by it. You glance at him. He wears an evil smirk on his face." << std::endl;
        (void)_getch();
        std::cout << "The next second, he is slammed to the ground, killing him instantly." << std::endl;
        std::cout << std::endl;
        (void)_getch();
        std::cout << "And then, it turns towards you." << std::endl;
        (void)_getch();
        std::cout << "You reach for your weapon, but the immense fear in your mind is holding you back from further action." << std::endl;
        (void)_getch();
        std::cout << "The giant Mutant's veins pulses a glowing red, energy from The Scientist coursing through his veins.\n'He's stealing energy from the dead...' You say to yourself." << std::endl;
        std::cout << std::endl;
        (void)_getch();
        std::cout << "You try to draw out your weapon. Your arm is sliced off in an instant." << std::endl;
        std::cout << std::endl;
        (void)_getch();
        std::cout << "The reality hits you...";
        (void)_getch();
        std::cout << " There is nothing you can do." << std::endl;
        std::cout << std::endl;
        (void)_getch();
        std::cout << "It lets out a devastating roar, before it charges towards you. No matter how hard you tried, you couldn't free yourself." << std::endl;
        std::cout << std::endl;
        (void)_getch();
        std::cout << "Then, it went straight to town. The Alchemist, Jake, every single resident suffered the wrath of this beast." << std::endl;
        (void)_getch();
        std::cout << "You are thrown to the ground. As you glance at the remains of the town, you think about the townsfolk and how you\ncould've saved them all if you were just faster." << std::endl;
        (void)_getch();
        std::cout << "Suddenly, the Mutant focuses its stored energy. It duplicates itself multiple times. You stare helplessly as the\nmutants run from the town to rain terror on others, " << std::endl;
        (void)_getch();
        std::cout << "If there even were any survivors out there." << std::endl;
        std::cout << std::endl;
        (void)_getch();
        std::cout << "You embrace your fate. The blood of the town is in your hands." << std::endl;
        (void)_getch();
        std::cout << "Your vision narrows, your eyelids shut completely." << std::endl;
        (void)_getch();
        std::cout << "And then, there was nothing." << std::endl;
        std::cout << "[WORST ENDING]" << std::endl;
        std::cout << "Press any key to exit game" << std::endl;
        (void)_getch();
        gameEnd = true; 
    }   
}