#include "npc.h"
#include "weaponsmith.h"
#include "alchemist.h"
#include "player.h"
#include "itemDB.h"
#include <iostream>
#include <conio.h>
bool npc::talkedToRyan = false;

void npc::onOverlap(player& p, inventory& bag)
{
    int rv = 0;
    switch (type) {
    case Type::Jake:
        if (talkedToRyan)
            rv = dialogue->performDialogue(dialogue->getJakeStartIndex());
        else
            rv = dialogue->performDialogue(dialogue->getfJakeStartIndex());
        break;
    case Type::Ryan:
        rv = dialogue->performDialogue(dialogue->getRyanStartIndex());
        break;
    case Type::Alchemist:
        rv = dialogue->performDialogue(dialogue->getAlchemistStartIndex());
        break;
    default:
        rv = dialogue->performDialogue();
        break;
    }
    if (rv == 1) {
        std::cout << "\n'Oh... well, thanks for sparing me.'\n";
    }
    if (rv == 2) {
        std::cout << "\n'Yep! Well, good luck...'\n";
    }
    if (rv == 3) {
        std::cout << "\n'Hey, come back to me if you need any weapons. You should arm yourself up before you go out there.'\n";
        if (type == Type::Ryan)
            talkedToRyan = true;
    }
    if (rv == 4) {
        std::cout << "\nYou hesitate but back away cautiously, hoping you won't regret your decision later.\n";
    }
    if (rv == 5) {
        weaponsmith smith;
        smith.weaponsmithOpen(p, bag);
    }
    if (rv == 6) {
        alchemist alchemist;
        alchemist.alchemistOpen(p, bag);
    }
    if (rv == 7) {
        std::cout << "\n'Good luck...'\n";
    }
    if (rv == 8) {
        std::cout << "\n'I'll be around if you want to chat.'\n";
    }
    if (rv == 9) {
        // +1 Health Potion
        std::cout << "'If it makes you feel better, have this. It's a failed version of the cure. It should ease your pain. Good luck...!'\n<You gained 1 Health Potion!>";   
        consumable toAdd = itemDB::getHealthPotion();
        bag.addPotion(toAdd);
    }

    std::cout << "\nPress any key to continue..."; //to end dialogue
    (void)_getch();
    system("CLS");
}