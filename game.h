#pragma once
#include "map.h"
#include "sewer.h"
#include "player.h"
#include "enemy.h"
#include "inventory.h"
#include "menu.h"
#include "bunker.h"
#include "town.h"
#include "lab.h"
#include "mutHuman.h"
#include "mutRat.h"
#include "level.h"

//names for locations to track the current map that is active
enum class Location {
    Sewer1,
    Sewer2,
    Sewer3,
    Town,
    Lab, 
    Bunker,
    MainWorld
};

class game
{
private:
    // Start date and time of our story
    int day = 19;
    int month = 3;
    int year = 2026;
    int minute = 0;
    int hour = 4;

    //initial time & inventory for restart stage
    int backupDay;
    int backupMonth;
    int backupYear;
    int backupMinute;
    int backupHour;

    std::string backupName;
    int backupHP;
    int backupLevel; 
    int backupExp;

    int backupGold;
    int backupStatPoints;
    int backupKeyFragment;
    inventory backupBag;
    int backupPosX;
    int backupPosY;

    bool gameEnd = false;
   
    //map objects
    map worldMap;
    sewer Sewer1;
    sewer Sewer2;
    sewer Sewer3;
    bunker Bunker;
    town Town;
    lab Lab;
    player player; // player object
    inventory bag; //inventory/bag object z
    menu settings;
    level level;
    //enemy enemy; // testing

    
    class player* playerPtr;   // pointer to player
    enemy* mutRats[3];  // pointer to mutant rats
    enemy* mutHumans[3];  // pointer to mutant humans

    enemy* worldEnemy = nullptr;

    Location currentMap = Location::MainWorld; //default is main world

    bool isLooted1 = false;
    bool isLooted2 = false;
    bool isLooted3 = false;
public:
    game();

    void createWorldMap();
    void Intro();
    void Run();
    void checkMapChange();
    void discoverpoi();
    void battlesequence(enemy*& currentEnemy);
    void bossbattlesequence(boss*& thescientist);

    void randomEncounter();

    void timePassMinutes(int m);
    
    void handleMovement(int dx, int dy);

    //menu
    void initialinfo();
    void restartstage();
    void restartgame(); 
    
    void handleEndings();
    void handleThirdEnding(int day, int month);

    map& activeMap();
    enemy** activeEnemy(int& totalCount);
};