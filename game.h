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
#include "randEnc.h"

//names for locations to track the current map that is active
enum class Location {
    Sewer1,
    Sewer2,
    Sewer3,
    Town,
    Lab, 
    Bunker,
    RandEnc,
    MainWorld
};

class game
{
private:
    // Start date and time of our story
    int day = 29;
    int month = 12;
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

    int backupGold;
    int backupStatPoints;
    int backupKeyFragment;
    inventory backupBag;
   
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
    randEnc randEnc;
    //enemy enemy; // testing

    
    class player* playerPtr;   // pointer to player
    enemy* mutRats[3];  // pointer to mutant rats
    enemy* mutHumans[3];  // pointer to mutant humans

    Location currentMap = Location::MainWorld; //default is main world

    entity* sewerGrid[15][5];
public:
    game();

    void createWorldMap();
    void Intro();
    void Run();
    void checkMapChange();
    void discoverpoi();
    void battlesequence(enemy*& currentEnemy);
    void bossbattlesequence(boss*& thescientist);

    int randEncChanceNum();
    void randomEncounterChance(int chance);

    void timePassMinutes(int m);

    entity* getEntityAt(int x, int y) const;
    void destroyEntity(entity* e);
    
    void handleMovement(int dx, int dy);
    void destroyEntity(entity* e); 

    //menu
    void initialinfo();
    void restartstage();
    void restartgame(); 
    
    void handleEndings();
    
    map& activeMap();
    enemy** activeEnemy(int& totalCount);
};